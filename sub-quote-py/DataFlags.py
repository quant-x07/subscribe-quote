import struct

class DataFlags(object):
    f_lastClose = 0  # b-> 0
    f_open = 2  # b-> lastClose
    f_high = 4  # b-> lastClose
    f_low = 6  # b-> lastClose

    f_close = 0  # b-> lastClose
    f_volume = 2  # b-> 0
    f_bp1 = 4  # b-> close
    f_bp2 = 6  # b-> close

    f_bp3 = 0  # b-> close
    f_bp4 = 2  # b-> close
    f_bp5 = 4  # b-> close
    f_bv1 = 6  # b-> 0

    f_bv2 = 0  # b-> bv1
    f_bv3 = 2  # b-> bv1
    f_bv4 = 4  # b-> bv1
    f_bv5 = 6  # b-> bv1

    f_sp1 = 0  # b-> close
    f_sp2 = 2  # b-> close
    f_sp3 = 4  # b-> close
    f_sp4 = 6  # b-> close

    f_sp5 = 0  # b-> close
    f_sv1 = 2  # b-> bv1 [special!!]
    f_sv2 = 4  # b-> bv1
    f_sv3 = 6  # b-> bv1

    f_sv4 = 0  # b-> bv1
    f_sv5 = 2  # b-> bv1
    f_neipan = 4  # b-> volume
    f_limitUp = 6  # b-> lastClose

    f_limitDown = 0  # b-> lastClose
    f_position = 2  # 期货持仓 b-> 0
    f_avPrice = 4   # 期货的结算价（平均价） b-> 0
    f_temp2 = 6  # b-> close

    def __init__(self, b):
        u0, u1, u2, u3, u4, u5, u6, u7 = struct.unpack('<BBBBBBBB', b)

        self.lastClose = (u0 >> self.f_lastClose) & 0b11 # b-> 0
        self.open = (u0 >> self.f_open) & 0b11  # b-> lastClose
        self.high = (u0 >> self.f_high) & 0b11  # b-> lastClose
        self.low = (u0 >> self.f_low) & 0b11  # b-> lastClose

        self.close = (u1 >> self.f_close) & 0b11  # b-> lastClose
        self.volume = (u1 >> self.f_volume) & 0b11  # b-> 0
        self.bp1 = (u1 >> self.f_bp1) & 0b11  # b-> close
        self.bp2 = (u1 >> self.f_bp2) & 0b11  # b-> close

        self.bp3 = (u2 >> self.f_bp3) & 0b11  # b-> close
        self.bp4 = (u2 >> self.f_bp4) & 0b11  # b-> close
        self.bp5 = (u2 >> self.f_bp5) & 0b11  # b-> close
        self.bv1 = (u2 >> self.f_bv1) & 0b11  # b-> 0

        self.bv2 = (u3 >> self.f_bv2) & 0b11  # b-> bv1
        self.bv3 = (u3 >> self.f_bv3) & 0b11  # b-> bv1
        self.bv4 = (u3 >> self.f_bv4) & 0b11  # b-> bv1
        self.bv5 = (u3 >> self.f_bv5) & 0b11  # b-> bv1

        self.sp1 = (u4 >> self.f_sp1) & 0b11  # b-> close
        self.sp2 = (u4 >> self.f_sp2) & 0b11  # b-> close
        self.sp3 = (u4 >> self.f_sp3) & 0b11  # b-> close
        self.sp4 = (u4 >> self.f_sp4) & 0b11  # b-> close

        self.sp5 = (u5 >> self.f_sp5) & 0b11  # b-> close
        self.sv1 = (u5 >> self.f_sv1) & 0b11  # b-> bv1 [special!!]
        self.sv2 = (u5 >> self.f_sv2) & 0b11  # b-> bv1
        self.sv3 = (u5 >> self.f_sv3) & 0b11  # b-> bv1

        self.sv4 = (u6 >> self.f_sv4) & 0b11  # b-> bv1
        self.sv5 = (u6 >> self.f_sv5) & 0b11  # b-> bv1
        self.neipan = (u6 >> self.f_neipan) & 0b11  # b-> volume
        self.limitUp = (u6 >> self.f_limitUp) & 0b11  # b-> lastClose

        self.limitDown = (u7 >> self.f_limitDown) & 0b11  # b-> lastClose
        self.position = (u7 >> self.f_position) & 0b11  # 期货持仓 b-> 0
        self.avPrice = (u7 >> self.f_avPrice) & 0b11   # 期货的结算价（平均价） b-> 0
        self.temp2 = (u7 >> self.f_temp2) & 0b11  # b-> close
