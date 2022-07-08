#pragma once
#include <stdint.h>

class TraceCompress {
public:
    TraceCompress();
    void decompress(struct Trace &k, const uint8_t *buf, int *len);

    int popDynInt(const uint8_t *buf, float *val, uint8_t flag, uint32_t base, uint16_t prec);
};


