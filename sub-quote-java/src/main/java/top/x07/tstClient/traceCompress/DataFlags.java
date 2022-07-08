package top.x07.tstClient.traceCompress;

import java.nio.ByteBuffer;

public class DataFlags extends javolution.io.Struct {
	private final Unsigned8 f_low = new Unsigned8(2);  // b-> lastClose
	private final Unsigned8 f_high = new Unsigned8(2);  // b-> lastClose
	private final Unsigned8 f_open = new Unsigned8(2);  // b-> lastClose
	private final Unsigned8 f_lastClose = new Unsigned8(2);  // b-> 0

	private final Unsigned8 f_bp2 = new Unsigned8(2);  // b-> close
	private final Unsigned8 f_bp1 = new Unsigned8(2);  // b-> close
	private final Unsigned8 f_volume = new Unsigned8(2);  // b-> 0
	private final Unsigned8 f_close = new Unsigned8(2);  // b-> lastClose

	private final Unsigned8 f_bv1 = new Unsigned8(2);  // b-> 0
	private final Unsigned8 f_bp5 = new Unsigned8(2);  // b-> close
	private final Unsigned8 f_bp4 = new Unsigned8(2);  // b-> close
	private final Unsigned8 f_bp3 = new Unsigned8(2);  // b-> close

	private final Unsigned8 f_bv5 = new Unsigned8(2);  // b-> bv1
	private final Unsigned8 f_bv4 = new Unsigned8(2);  // b-> bv1
	private final Unsigned8 f_bv3 = new Unsigned8(2);  // b-> bv1
	private final Unsigned8 f_bv2 = new Unsigned8(2);  // b-> bv1

	private final Unsigned8 f_sp4 = new Unsigned8(2);  // b-> close
	private final Unsigned8 f_sp3 = new Unsigned8(2);  // b-> close
	private final Unsigned8 f_sp2 = new Unsigned8(2);  // b-> close
	private final Unsigned8 f_sp1 = new Unsigned8(2);  // b-> close

	private final Unsigned8 f_sv3 = new Unsigned8(2);  // b-> bv1
	private final Unsigned8 f_sv2 = new Unsigned8(2);  // b-> bv1
	private final Unsigned8 f_sv1 = new Unsigned8(2);  // b-> bv1 [special!!]
	private final Unsigned8 f_sp5 = new Unsigned8(2);  // b-> close

	private final Unsigned8 f_limitUp = new Unsigned8(2);  // b-> lastClose
	private final Unsigned8 f_neipan = new Unsigned8(2);  // b-> volume
	private final Unsigned8 f_sv5 = new Unsigned8(2);  // b-> bv1
	private final Unsigned8 f_sv4 = new Unsigned8(2);  // b-> bv1

	private final Unsigned8 f_temp2 = new Unsigned8(2);  // b-> close
	private final Unsigned8 f_avPrice = new Unsigned8(2);   // 期货的结算价（平均价） b-> 0
	private final Unsigned8 f_position = new Unsigned8(2);  // 期货持仓 b-> 0
	private final Unsigned8 f_limitDown = new Unsigned8(2);  // b-> lastClose

	public DataFlags(byte[] b) {
		this.setByteBuffer(ByteBuffer.wrap(b), 0);
	}

	public short lastClose() { return f_lastClose.get(); }
	public short open() { return f_open.get(); }
	public short high() { return f_high.get(); }
	public short low() { return f_low.get(); }
	public short close() { return f_close.get(); }
	public short volume() { return f_volume.get(); }

	public short bp1() { return f_bp1.get(); }
	public short bp2() { return f_bp2.get(); }
	public short bp3() { return f_bp3.get(); }
	public short bp4() { return f_bp4.get(); }
	public short bp5() { return f_bp5.get(); }
	public short bv1() { return f_bv1.get(); }
	public short bv2() { return f_bv2.get(); }
	public short bv3() { return f_bv3.get(); }
	public short bv4() { return f_bv4.get(); }
	public short bv5() { return f_bv5.get(); }

	public short sp1() { return f_sp1.get(); }
	public short sp2() { return f_sp2.get(); }
	public short sp3() { return f_sp3.get(); }
	public short sp4() { return f_sp4.get(); }
	public short sp5() { return f_sp5.get(); }
	public short sv1() { return f_sv1.get(); }
	public short sv2() { return f_sv2.get(); }
	public short sv3() { return f_sv3.get(); }
	public short sv4() { return f_sv4.get(); }
	public short sv5() { return f_sv5.get(); }

	public short neipan() { return f_neipan.get(); }
	public short limitUp() { return f_limitUp.get(); }
	public short limitDown() { return f_limitDown.get(); }
	public short position() { return f_position.get(); }

	public short avPrice() { return f_avPrice.get(); }
	public short temp2() { return f_temp2.get(); }
}
