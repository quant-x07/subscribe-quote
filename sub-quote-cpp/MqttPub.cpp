#include "MqttPub.h"
#include "Trace.h"
#include "TraceCompress.h"
#include <vector>
#include <map>

#define ENABLE_ZLIB

#ifdef ENABLE_ZLIB
#include <zlib.h>
#endif

std::mutex g_display_mutex;

void ThreadProc(void* lpParameter)
{
    std::thread::id this_id = std::this_thread::get_id();
    g_display_mutex.lock();
    std::cout << "ThreadProc tid " << this_id << "\n";
    g_display_mutex.unlock();
    MqttPub *pub = (MqttPub*)lpParameter;
    pub->loop();
}

//static
MqttPub* MqttPub::instance()
{
    static MqttPub pub;
    return &pub;
}

#ifdef ENABLE_ZLIB
static bool decompressZlib(const uint8_t* data, size_t dataSz, std::vector<uint8_t> &outData)
{
    outData.resize(dataSz * 7);
    size_t decompressSz = outData.size();
    int ret = Z_BUF_ERROR;

    while (Z_BUF_ERROR == (ret = uncompress(&outData.at(0), &decompressSz, data, dataSz))) {
        decompressSz = outData.size() * 2;
        outData.resize(decompressSz);
    }

    if (ret == Z_OK) {
        outData.resize(decompressSz);
        return true;
    } else {
        outData.clear();
        fprintf(stderr, "zlib decompress error %d\n", ret);
        return false;
    }
}
#endif

// static
void MqttPub::on_message(struct mosquitto *, void *, const struct mosquitto_message *msg)
{
#if 0
    std::thread::id this_id = std::this_thread::get_id();
    g_display_mutex.lock();
    std::cout << "on_message tid " << this_id << "\n";
    g_display_mutex.unlock();
    printf("on_message. topic:%s, len: %d\n", msg->topic, msg->payloadlen);
#endif

#if 0
    FILE* fp = fopen("payload.dat", "wb");
    fwrite(msg->payload, msg->payloadlen, 1, fp);
    fclose(fp);
#endif

#ifdef ENABLE_ZLIB
    std::vector<uint8_t> data;
    if (!decompressZlib((const uint8_t*)msg->payload, msg->payloadlen, data)) {
        return;
    }
    uint8_t *p = &data.at(0);
    uint8_t *pEnd = p + data.size();
#else
    uint8_t *p = (uint8_t*)msg->payload;
    uint8_t *pEnd = p + msg->payloadlen;
#endif

    TraceCompress compress;
    struct Trace trace;
    int len;
    while (p < pEnd) {
        compress.decompress(trace, p, &len);
        dumpTrace(&trace, false);
        p += len;
    }
}
