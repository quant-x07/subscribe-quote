#pragma once
#include <stdint.h>

class TraceCompress {
public:
    TraceCompress();
    void compress(const struct Trace &k, uint8_t *buf, int *len);
    void decompress(struct Trace &k, const uint8_t *buf, int *len);

    int pushDynInt(uint8_t *buf, int delta, float orig, uint8_t *f);
    int popDynInt(const uint8_t *buf, float *val, uint8_t flag, uint32_t base, uint16_t prec);
};


