#include "TraceCompress.h"
#include "Trace.h"
#include <assert.h>
#include <ctype.h>
#include <string.h>

//#pragma pack(push, 1)
typedef struct {
    uint8_t f_lastClose:2;  // b-> 0
    uint8_t f_open:2;  // b-> lastClose
    uint8_t f_high:2;  // b-> lastClose
    uint8_t f_low:2;  // b-> lastClose

    uint8_t f_close:2;  // b-> lastClose
    uint8_t f_volume:2;  // b-> 0
    uint8_t f_bp1:2;  // b-> close
    uint8_t f_bp2:2;  // b-> close

    uint8_t f_bp3:2;  // b-> close
    uint8_t f_bp4:2;  // b-> close
    uint8_t f_bp5:2;  // b-> close
    uint8_t f_bv1:2;  // b-> 0

    uint8_t f_bv2:2;  // b-> bv1
    uint8_t f_bv3:2;  // b-> bv1
    uint8_t f_bv4:2;  // b-> bv1
    uint8_t f_bv5:2;  // b-> bv1

    uint8_t f_sp1:2;  // b-> close
    uint8_t f_sp2:2;  // b-> close
    uint8_t f_sp3:2;  // b-> close
    uint8_t f_sp4:2;  // b-> close

    uint8_t f_sp5:2;  // b-> close
    uint8_t f_sv1:2;  // b-> bv1 [special!!]
    uint8_t f_sv2:2;  // b-> bv1
    uint8_t f_sv3:2;  // b-> bv1

    uint8_t f_sv4:2;  // b-> bv1
    uint8_t f_sv5:2;  // b-> bv1
    uint8_t f_neipan:2;  // b-> volume
    uint8_t f_limitUp:2;  // b-> lastClose

    uint8_t f_limitDown:2;  // b-> lastClose
    uint8_t f_position:2;  // 期货持仓 b-> 0
    uint8_t f_avPrice:2;   // 期货的结算价（平均价） b-> 0
    uint8_t f_temp2:2;  // b-> close
} DataFlags;
//#pragma pack(pop)

TraceCompress::TraceCompress()
{
}

static void hexdump(void *ptr, int buflen)
{
    unsigned char *buf = (unsigned char*)ptr;
    int i, j;
    for (i = 0; i < buflen; i += 16) {
        printf("%06x: ", i);
        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                printf("%02x ", buf[i + j]);
            else
                printf("   ");
        printf(" ");
        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                printf("%c", isprint(buf[i + j]) ? buf[i + j] : '.');
        printf("\n");
    }
}

const uint16_t precision = 100;
//const uint16_t precision_vol = 100;
const uint16_t precision_vol = 1;

#define p2i(PRICE) \
    ((uint32_t)((PRICE) * precision + 0.5))

#define v2i(PRICE) \
    ((uint32_t)((PRICE) * precision_vol + 0.5))

void TraceCompress::compress(const struct Trace &k, uint8_t *buf, int *len)
{
    memset(buf, 0, 256);
    int offset = 0;
    uint8_t f;

    // ### time
    *(uint32_t*)(buf+offset) = k.time;
    offset += sizeof(uint32_t);

    // ### stkLabel
    memcpy(buf+offset, k.stkLabel, sizeof(Trace::stkLabel));
    offset += sizeof(Trace::stkLabel);

    // ### dataFlags
    DataFlags &dataFlags = *(DataFlags*)(buf+offset);
    offset += sizeof(DataFlags);

    // price bases
    uint32_t base_0 = 0;
    uint32_t base_lastClose = p2i(k.lastClose);
    uint32_t base_close = p2i(k.close);
    uint32_t base_bv1 = v2i(k.bv1);

    // for neipan compress
    uint32_t base_volume = (uint32_t)(k.volume * precision_vol + 0.5);

#define PUSH_PRICE(FIELD, BASE) \
    offset += pushDynInt(buf + offset, p2i(k.FIELD) - BASE, k.FIELD, &f); dataFlags.f_##FIELD = f

#define PUSH_VOLUME(FIELD, BASE) \
    offset += pushDynInt(buf + offset, v2i(k.FIELD) - BASE, k.FIELD, &f); dataFlags.f_##FIELD = f

    // ### lastClose
    PUSH_PRICE(lastClose, base_0);
    // ### open
    PUSH_PRICE(open, base_lastClose);
    // ### high
    PUSH_PRICE(high, base_lastClose);
    // ### low
    PUSH_PRICE(low, base_lastClose);
    // ### close
    PUSH_PRICE(close, base_lastClose);
    // ### volume
    PUSH_VOLUME(volume, base_0);
    // ### amount
    *(float*)(buf+offset) = k.amount; offset += sizeof(float);

    // bp1;           //买入价一
    PUSH_PRICE(bp1, base_close);
    // bp2;           //买入价二
    PUSH_PRICE(bp2, base_close);
    // bp3;           //买入价三
    PUSH_PRICE(bp3, base_close);
    // bp4;                 //买入价四
    PUSH_PRICE(bp4, base_close);
    // bp5;                 //买入价五
    PUSH_PRICE(bp5, base_close);

    // bv1;           //买入量一
    PUSH_VOLUME(bv1, base_0);
    // bv2;           //买入量二
    PUSH_VOLUME(bv2, base_bv1);
    // bv3;           //买入量三
    PUSH_VOLUME(bv3, base_bv1);
    // bv4;                 //买入量四
    PUSH_VOLUME(bv4, base_bv1);
    // bv5;                 //买入量五
    PUSH_VOLUME(bv5, base_bv1);

    // sp1;           //卖出价一
    PUSH_PRICE(sp1, base_close);
    // sp2;           //卖出价二
    PUSH_PRICE(sp2, base_close);
    // sp3;           //卖出价三
    PUSH_PRICE(sp3, base_close);
    // sp4;                 //卖出价四
    PUSH_PRICE(sp4, base_close);
    // sp5;                 //卖出价五
    PUSH_PRICE(sp5, base_close);

    // sv1;           //卖出量一
    PUSH_VOLUME(sv1, base_bv1);
    // sv2;           //卖出量二
    PUSH_VOLUME(sv2, base_bv1);
    // sv3;           //卖出量三
    PUSH_VOLUME(sv3, base_bv1);
    // sv4;                 //卖出量四
    PUSH_VOLUME(sv4, base_bv1);
    // sv5;                 //卖出量五
    PUSH_VOLUME(sv5, base_bv1);

    // traceCount;             //分笔数
    *(uint32_t*)(buf+offset) = k.traceCount; offset += sizeof(uint32_t);
    // neipan;                //内盘，负值
    PUSH_VOLUME(neipan, base_volume);
    // limitUp;               //涨跌价
    PUSH_PRICE(limitUp, base_lastClose);
    // limitDown;             //跌停价
    PUSH_PRICE(limitDown, base_lastClose);
    // position;              //期货持仓
    PUSH_VOLUME(position, base_0);
    // avPrice;               // 期货的结算价（平均价）
    PUSH_PRICE(avPrice, base_0);
    // temp2;                 //
    PUSH_PRICE(temp2, base_close);

    *len = offset;
    hexdump(buf, offset);
#undef PUSH_PRICE
#undef PUSH_VOLUME
}

int TraceCompress::pushDynInt(uint8_t *buf, int delta, float orig, uint8_t *f)
{
    if (delta == 0) {
        *f = 0x00;
        return 0;
    } else if (delta >= -128 && delta <= 127) {
        // push as int8
        *(int8_t*)(buf) = (int8_t)delta;
        *f = 0x01;
        return 1;
    }
    else if (delta >= -32768 && delta <= 32767) {
        // push as int16
        *(int16_t*)(buf) = (int16_t)delta;
        *f = 0x02;
        return 2;
    }
    else {
        // push orig as float
        *(float*)(buf) = orig;
        *f = 0x03;
        return 4;
    }
}

int TraceCompress::popDynInt(const uint8_t *buf, float *val, uint8_t flag, uint32_t base, uint16_t prec)
{
    if (flag == 0x00) {
        *val = float(base) / prec;
        return 0;
    } else if (flag == 0x01) {
        // push as int8
        *val = float(*(int8_t*)(buf) + base) / prec;
        return 1;
    }
    else if (flag == 0x02) {
        // push as int16
        *val = float(*(int16_t*)(buf) + base) / prec;
        return 2;
    }
    else {
        // push orig as float
        *val = *(float*)(buf);
        return 4;
    }
}

void TraceCompress::decompress(struct Trace &k, const uint8_t *buf, int *len)
{
    int offset = 0;
    k.size = sizeof(Trace);
    // ### time
    k.time = *(uint32_t*)(buf+offset);
    offset += sizeof(uint32_t);
    // ### stkLabel
    memcpy(k.stkLabel, buf+offset, sizeof(Trace::stkLabel));
    offset += sizeof(Trace::stkLabel);
    DataFlags *dataFlags = (DataFlags*)(buf+offset);
    offset += sizeof(DataFlags);
    // price bases
    uint32_t base_0 = 0;

#define POP_PRICE(FIELD, BASE) \
    offset += popDynInt(buf+offset, &k.FIELD, dataFlags->f_##FIELD, BASE, precision)

#define POP_VOLUME(FIELD, BASE) \
    offset += popDynInt(buf+offset, &k.FIELD, dataFlags->f_##FIELD, BASE, precision_vol)

    // ### lastClose
    POP_PRICE(lastClose, base_0);
    uint32_t base_lastClose = p2i(k.lastClose);
    // ### open
    POP_PRICE(open, base_lastClose);
    // ### high
    POP_PRICE(high, base_lastClose);
    // ### low
    POP_PRICE(low, base_lastClose);
    // ### close
    POP_PRICE(close, base_lastClose);
    uint32_t base_close = p2i(k.close);

    // ### volume
    POP_VOLUME(volume, base_0);
    // for neipan compress
    uint32_t base_volume = (uint32_t)(k.volume * precision_vol + 0.5);

    // ### amount
    k.amount = *(float*)(buf+offset);
    offset += sizeof(float);
    // ### bp1
    POP_PRICE(bp1, base_close);
    // ### bp2
    POP_PRICE(bp2, base_close);
    // ### bp3
    POP_PRICE(bp3, base_close);
    // ### bp4
    POP_PRICE(bp4, base_close);
    // ### bp5
    POP_PRICE(bp5, base_close);

    // ### bv1
    POP_VOLUME(bv1, base_0);
    uint32_t base_bv1 = v2i(k.bv1);
    // ### bv2
    POP_VOLUME(bv2, base_bv1);
    // ### bv3
    POP_VOLUME(bv3, base_bv1);
    // ### bv4
    POP_VOLUME(bv4, base_bv1);
    // ### bv5
    POP_VOLUME(bv5, base_bv1);

    // ### sp1
    POP_PRICE(sp1, base_close);
    // ### sp2
    POP_PRICE(sp2, base_close);
    // ### sp3
    POP_PRICE(sp3, base_close);
    // ### sp4
    POP_PRICE(sp4, base_close);
    // ### sp5
    POP_PRICE(sp5, base_close);

    // ### sv1
    POP_VOLUME(sv1, base_bv1);
    // ### sv2
    POP_VOLUME(sv2, base_bv1);
    // ### sv3
    POP_VOLUME(sv3, base_bv1);
    // ### sv4
    POP_VOLUME(sv4, base_bv1);
    // ### sv5
    POP_VOLUME(sv5, base_bv1);

    // ### traceCount
    k.traceCount = *(uint32_t*)(buf+offset);
    offset += sizeof(uint32_t);

    // ### neipan
    POP_VOLUME(neipan, base_volume);
    // ### limitUp
    POP_PRICE(limitUp, base_lastClose);
    // ### limitDown
    POP_PRICE(limitDown, base_lastClose);
    // ### position
    POP_VOLUME(position, base_0);
    // ### avPrice
    POP_PRICE(avPrice, base_0);
    // ### temp2
    POP_PRICE(temp2, base_close);

    *len = offset;
#undef POP_PRICE
#undef POP_VOLUME
}

