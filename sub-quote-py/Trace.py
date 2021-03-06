# 实时数据发送格式
class Trace(object):
    def __init__(self):
        # uint16_t
        self.size = 0   # 结构大小
        # uint32_t
        self.time = 0   # 成交时间
        # char[12]
        self.stkLabel = ''  # 市场代码 + 股票代码, 以'\0'结尾
        # float
        self.lastClose = 0.0     # 昨天收盘
        # float
        self.open = 0.0          # 今日开盘
        #float
        self.high = 0.0               # 今日最高
        #float
        self.low = 0.0                # 今日最低
        #float
        self.close = 0.0              # 最新价格
        #float
        self.volume = 0.0             # 总成交量
        #float
        self.amount = 0.0             # 总成交金额

        #float
        self.bp1 = 0.0           # 买入价一
        #float
        self.bp2 = 0.0           # 买入价二
        #float
        self.bp3 = 0.0           # 买入价三
        #float
        self.bp4 = 0.0           # 买入价四
        #float
        self.bp5 = 0.0           # 买入价五

        #float
        self.bv1 = 0.0           # 买入量一
        #float
        self.bv2 = 0.0           # 买入量二
        #float
        self.bv3 = 0.0           # 买入量三
        #float
        self.bv4 = 0.0           # 买入量四
        #float
        self.bv5 = 0.0           # 买入量五

        #float
        self.sp1 = 0.0           # 卖出价一
        #float
        self.sp2 = 0.0           # 卖出价二
        #float
        self.sp3 = 0.0           # 卖出价三
        #float
        self.sp4 = 0.0           # 卖出价四
        #float
        self.sp5 = 0.0           # 卖出价五

        #float
        self.sv1 = 0.0           # 卖出量一
        #float
        self.sv2 = 0.0           # 卖出量二
        #float
        self.sv3 = 0.0           # 卖出量三
        #float
        self.sv4 = 0.0           # 卖出量四
        #float
        self.sv5 = 0.0           # 卖出量五

        #uint32_t
        self.traceCount = 0      # 分笔数
        #float
        self.neipan = 0.0        # 内盘，负值
        #float
        self.limitUp = 0.0       # 涨跌价
        #float
        self.limitDown = 0.0     # 跌停价
        #float
        self.position = 0.0      # 期货持仓
        #float
        self.avPrice = 0.0       # 期货的结算价（平均价）
        #float
        self.temp2 = 0.0

    # String
    def getMarket(self):
        return stkLabel[0:2]

    # String
    def getStockId(self):
        return stkLabel[2:]

    def dump(self, simple):
        if simple:
            print("%d %s %f" % (self.time, self.stkLabel, self.lastClose))
        else:
            print("%d %s %f" % (self.time, self.stkLabel, self.lastClose))
            print("o:%f h:%f l:%f c:%f v:%f a:%f" % (self.open, self.high, self.low, self.close, self.volume, self.amount))
            print("bp1:%f bp2:%f bp3:%f bp4:%f bp5:%f" % (self.bp1, self.bp2, self.bp3, self.bp4, self.bp5))
            print("bv1:%f bv2:%f bv3:%f bv4:%f bv5:%f" % (self.bv1, self.bv2, self.bv3, self.bv4, self.bv5))
            print("cnt:%d neipan:%f limitUp:%f limitDown:%f position: %f avPrice:%f temp2: %f" %
                    (self.traceCount, self.neipan, self.limitUp, self.limitDown, self.position, self.avPrice, self.temp2))
