package top.x07.tstClient;

//实时数据发送格式
public class Trace {
	public int time; // 成交时间
	public String stkLabel; // 市场代码 + 股票代码, length <= 12
	public float lastClose; // 昨天收盘
	public float open; // 今日开盘
	public float high; // 今日最高
	public float low; // 今日最低
	public float close; // 最新价格
	public float volume; // 总成交量
	public float amount; // 总成交金额

	public float bp1; // 买入价一
	public float bp2; // 买入价二
	public float bp3; // 买入价三
	public float bp4; // 买入价四
	public float bp5; // 买入价五

	public float bv1; // 买入量一
	public float bv2; // 买入量二
	public float bv3; // 买入量三
	public float bv4; // 买入量四
	public float bv5; // 买入量五

	public float sp1; // 卖出价一
	public float sp2; // 卖出价二
	public float sp3; // 卖出价三
	public float sp4; // 卖出价四
	public float sp5; // 卖出价五

	public float sv1; // 卖出量一
	public float sv2; // 卖出量二
	public float sv3; // 卖出量三
	public float sv4; // 卖出量四
	public float sv5; // 卖出量五

	public int traceCount; // 逐笔数（当前序号）
	public float neipan; // 内盘，负值
	public float limitUp; // 涨跌价
	public float limitDown; // 跌停价
	public float position; // 期货持仓
	public float avPrice; // 期货的结算价（平均价）
	public float temp2; //

	String getMarket() {
		return stkLabel.substring(0, 2);
	}
	String getStockId() {
		return stkLabel.substring(2);
	}
	
	void dump(boolean simple) {
		if (simple) {
	        System.out.format("%d %s %f\n", time, stkLabel, lastClose);
	    } else {
	        System.out.format("%d %s %f\n", time, stkLabel, lastClose);
	        System.out.format("o:%f h:%f l:%f c:%f v:%f a:%f\n", open, high, low, close, volume, amount);
	        System.out.format("bp1:%f bp2:%f bp3:%f bp4:%f bp5:%f\n", bp1, bp2, bp3, bp4, bp5);
	        System.out.format("bv1:%f bv2:%f bv3:%f bv4:%f bv5:%f\n", bv1, bv2, bv3, bv4, bv5);
	        System.out.format("cnt:%d neipan:%f limitUp:%f limitDown:%f position: %f avPrice:%f temp2: %f\n",
	                traceCount, neipan, limitUp, limitDown, position, avPrice, temp2);
	    }
	}
}
