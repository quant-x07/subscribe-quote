from Trace import Trace
from DataFlags import DataFlags
import math
import struct

precision = 100
#precision_vol = 100
precision_vol = 1

# int
def p2i(self, price):
    ret = math.floor(price * precision + 0.5)
    return int(ret)

# int
def v2i(self, price):
    ret = math.floor(price * precision_vol + 0.5)
    return int(ret)

class TraceCompress(object):
    def __init__(self):
        self.tmpOffset = 0
        self.buf = b''

    # float
    def readFloatFromC(self, buf, offset):
        return struct.unpack('<f', buf[offset:offset+4])[0]

    # int
    def readIntLe(self, buf, offset):
        return struct.unpack('<i', buf[offset:offset+4])[0]

    # short
    def readInt16Le(self, buf, offset):
        return struct.unpack('<h', buf[offset:offset+2])[0]

    # boolean
    def isAtEnd(self):
        return self.tmpOffset >= len(self.buf)

    def initBuf(self, bufIn):
        self.buf = bufIn
        self.tmpOffset = 0

    # Trace
    def decompress(self):
        k = Trace()

        ### time
        ### stkLabel
        k.time, k.stkLabel = struct.unpack('<I12s', self.buf[self.tmpOffset:self.tmpOffset+4+12])
        k.stkLabel = k.stkLabel.rstrip(b'\x00').decode('utf8')
        self.tmpOffset += 4 + 12

        dataFlagsBytes = self.buf[self.tmpOffset:self.tmpOffset+8]
        f = DataFlags(dataFlagsBytes)
        self.tmpOffset += 8

        # price bases
        base_0 = 0

        ### lastClose
        k.lastClose = self.popDynInt(f.lastClose, base_0, precision)
        # int
        base_lastClose = p2i(k.lastClose)
        ### open
        k.open = self.popDynInt(f.open, base_lastClose, precision)
        ### high
        k.high = self.popDynInt(f.high, base_lastClose, precision)
        ### low
        k.low = self.popDynInt(f.low, base_lastClose, precision)
        ### close
        k.close = self.popDynInt(f.close, base_lastClose, precision)
        # int
        base_close = p2i(k.close)

        ### volume
        k.volume = self.popDynInt(f.volume, base_0, precision_vol)
        # for neipan compress
        # int
        base_volume = v2i(k.volume)

        ### amount
        k.amount = self.readFloatFromC(self.buf, self.tmpOffset)
        self.tmpOffset += 4

        ### bp1
        k.bp1 = self.popDynInt(f.bp1, base_close, precision)
        ### bp2
        k.bp2 = self.popDynInt(f.bp2, base_close, precision)
        ### bp3
        k.bp3 = self.popDynInt(f.bp3, base_close, precision)
        ### bp4
        k.bp4 = self.popDynInt(f.bp4, base_close, precision)
        ### bp5
        k.bp5 = self.popDynInt(f.bp5, base_close, precision)

        ### bv1
        k.bv1 = self.popDynInt(f.bv1, base_0, precision_vol)
        # int
        base_bv1 = v2i(k.bv1)
        ### bv2
        k.bv2 = self.popDynInt(f.bv2, base_bv1, precision_vol)
        ### bv3
        k.bv3 = self.popDynInt(f.bv3, base_bv1, precision_vol)
        ### bv4
        k.bv4 = self.popDynInt(f.bv4, base_bv1, precision_vol)
        ### bv5
        k.bv5 = self.popDynInt(f.bv5, base_bv1, precision_vol)

        ### sp1
        k.sp1 = self.popDynInt(f.sp1, base_close, precision)
        ### sp2
        k.sp2 = self.popDynInt(f.sp2, base_close, precision)
        ### sp3
        k.sp3 = self.popDynInt(f.sp3, base_close, precision)
        ### sp4
        k.sp4 = self.popDynInt(f.sp4, base_close, precision)
        ### sp5
        k.sp5 = self.popDynInt(f.sp5, base_close, precision)

        ### sv1
        k.sv1 = self.popDynInt(f.sv1, base_bv1, precision_vol)
        ### sv2
        k.sv2 = self.popDynInt(f.sv2, base_bv1, precision_vol)
        ### sv3
        k.sv3 = self.popDynInt(f.sv3, base_bv1, precision_vol)
        ### sv4
        k.sv4 = self.popDynInt(f.sv4, base_bv1, precision_vol)
        ### sv5
        k.sv5 = self.popDynInt(f.sv5, base_bv1, precision_vol)

        ### traceCount
        k.traceCount = self.readIntLe(self.buf, self.tmpOffset)
        self.tmpOffset += 4

        ### neipan
        k.neipan = self.popDynInt(f.neipan, base_volume, precision_vol)
        ### limitUp
        k.limitUp = self.popDynInt(f.limitUp, base_lastClose, precision)
        ### limitDown
        k.limitDown = self.popDynInt(f.limitDown, base_lastClose, precision)
        ### position
        k.position = self.popDynInt(f.position, base_0, precision_vol)
        ### avPrice
        k.avPrice = self.popDynInt(f.avPrice, base_0, precision)
        ### temp2
        k.temp2 = self.popDynInt(f.temp2, base_close, precision)

        return k

    # float
    def popDynInt(self, flag, base, prec):
        if flag == 0x00:
            return base / prec
        elif flag == 0x01:
            # push as int8
            delta = self.buf[self.tmpOffset]
            self.tmpOffset += 1
            return (delta + base) / prec
        elif flag == 0x02:
            # push as int16
            delta = self.readInt16Le(self.buf, self.tmpOffset)
            self.tmpOffset += 2
            return (delta + base) / prec
        else:
            # push orig as float
            # float
            orig = self.readFloatFromC(self.buf, self.tmpOffset)
            self.tmpOffset += 4
            return orig
