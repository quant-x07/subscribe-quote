#pragma once
#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)
struct Trace      //实时数据发送格式
{
    uint16_t    size;               //结构大小
    uint32_t    time;               //成交时间
    union {
        struct {
            uint16_t    market;
            char        stockId[10];    //市场代码 + 股票代码, 以'\0'结尾
        };
        char            stkLabel[12];   //市场代码 + 股票代码, 以'\0'结尾
    };
    float    lastClose;     //昨天收盘
    float    open;          //今日开盘
    float    high;          //今日最高
    float    low;           //今日最低
    float    close;         //最新价格
    float    volume;        //总成交量
    float    amount;        //总成交金额

    float    bp1;           //买入价一
    float    bp2;           //买入价二
    float    bp3;           //买入价三
    float    bp4;           //买入价四
    float    bp5;           //买入价五

    float    bv1;           //买入量一
    float    bv2;           //买入量二
    float    bv3;           //买入量三
    float    bv4;           //买入量四
    float    bv5;           //买入量五

    float    sp1;           //卖出价一
    float    sp2;           //卖出价二
    float    sp3;           //卖出价三
    float    sp4;           //卖出价四
    float    sp5;           //卖出价五

    float    sv1;           //卖出量一
    float    sv2;           //卖出量二
    float    sv3;           //卖出量三
    float    sv4;           //卖出量四
    float    sv5;           //卖出量五

    uint32_t traceCount;    //分笔数
    float    neipan;        //内盘，负值
    float    limitUp;       //涨跌价
    float    limitDown;     //跌停价
    float    position;      //期货持仓
    float    avPrice;       // 期货的结算价（平均价）
    float    temp2;         //
};
#pragma pack(pop)

inline void dumpTrace(struct Trace*s, bool simple)
{
    if (simple) {
        printf("%d %s %f\n", s->time, s->stkLabel, s->lastClose);
    } else {
        printf("%d %s %f\n", s->time, s->stkLabel, s->lastClose);
        printf("o:%f h:%f l:%f c:%f v:%f a:%f\n", s->open, s->high, s->low, s->close, s->volume, s->amount);
        printf("bp1:%f bp2:%f bp3:%f bp4:%f bp5:%f\n",
                s->bp1, s->bp2, s->bp3, s->bp4, s->bp5);
        printf("bv1:%f bv2:%f bv3:%f bv4:%f bv5:%f\n",
                s->bv1, s->bv2, s->bv3, s->bv4, s->bv5);
        printf("cnt:%d neipan:%f limitUp:%f limitDown:%f position: %f avPrice:%f temp2: %f\n",
                s->traceCount, s->neipan, s->limitUp, s->limitDown, s->position, s->avPrice, s->temp2);
    }
}
