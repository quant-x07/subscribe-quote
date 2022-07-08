package top.x07.tstClient.traceCompress;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import top.x07.tstClient.Trace;

public class TraceCompress {
	final short precision = 100;
	//final short precision_vol = 100;
	final short precision_vol = 1;

	private int tmpOffset;
	private byte[] buf;
	
	public static float readFloatFromC(byte[] bytes, int offset){
	    byte[] floatBytes = new byte[Float.SIZE/8];
	    System.arraycopy(bytes, offset, floatBytes, 0, Float.SIZE/8);
	    return ByteBuffer.wrap(floatBytes).order(ByteOrder.LITTLE_ENDIAN).getFloat();
	}

	public static int readIntLe(byte[] bytes, int offset) {
	    return (bytes[offset] & 0xff) | (bytes[offset + 1] & 0xff) << 8
	            | (bytes[offset + 2] & 0xff) << 16 | (bytes[offset + 3] & 0xff) << 24;
	}

	public static short readUint16Le(byte[] bytes, int offset) {
	    return (short) ((bytes[offset] & 0xff) | (bytes[offset + 1] & 0xff) << 8);
	}

	public static String byteArrayToString(byte[] bytes){
	    String s = null;
	    try {
	        s = new String(bytes, "GBK");
	    } catch (UnsupportedEncodingException e) {
	        e.printStackTrace();
	    }
	    return s.substring(0, s.indexOf(0));
	}
	
	public boolean isAtEnd() {
		return tmpOffset >= buf.length;
	}
	
	public void initBuf(byte[] bufIn) {
    	buf = bufIn;
        tmpOffset = 0;
	}

    public Trace decompress() throws IOException {
    	Trace k = new Trace();

        // ### time
        k.time = readIntLe(buf, tmpOffset);
        tmpOffset += 4;

        // ### stkLabel
        byte[] stkLabelBytes = new byte[12];
        System.arraycopy(buf, tmpOffset, stkLabelBytes, 0, 12);
        k.stkLabel = byteArrayToString(stkLabelBytes);
        tmpOffset += 12;

        byte[] dataFlagsBytes = new byte[8];
        System.arraycopy(buf, tmpOffset, dataFlagsBytes, 0, 8);
        DataFlags f = new DataFlags(dataFlagsBytes);
        tmpOffset += 8;

        // price bases
        int base_0 = 0;

        // ### lastClose
        k.lastClose = popDynInt(f.lastClose(), base_0, precision);
        int base_lastClose = p2i(k.lastClose);
        // ### open
        k.open = popDynInt(f.open(), base_lastClose, precision);
        // ### high
        k.high = popDynInt(f.high(), base_lastClose, precision);
        // ### low
        k.low = popDynInt(f.low(), base_lastClose, precision);
        // ### close
        k.close = popDynInt(f.close(), base_lastClose, precision);
        int base_close = p2i(k.close);

        // ### volume
        k.volume = popDynInt(f.volume(), base_0, precision_vol);
        // for neipan compress
        int base_volume = v2i(k.volume);

        // ### amount
        k.amount = readFloatFromC(buf, tmpOffset);
        tmpOffset += 4;

        // ### bp1
        k.bp1 = popDynInt(f.bp1(), base_close, precision);
        // ### bp2
        k.bp2 = popDynInt(f.bp2(), base_close, precision);
        // ### bp3
        k.bp3 = popDynInt(f.bp3(), base_close, precision);
        // ### bp4
        k.bp4 = popDynInt(f.bp4(), base_close, precision);
        // ### bp5
        k.bp5 = popDynInt(f.bp5(), base_close, precision);
        
        // ### bv1
        k.bv1 = popDynInt(f.bv1(), base_0, precision_vol);
        int base_bv1 = v2i(k.bv1);
        // ### bv2
        k.bv2 = popDynInt(f.bv2(), base_bv1, precision_vol);
        // ### bv3
        k.bv3 = popDynInt(f.bv3(), base_bv1, precision_vol);
        // ### bv4
        k.bv4 = popDynInt(f.bv4(), base_bv1, precision_vol);
        // ### bv5
        k.bv5 = popDynInt(f.bv5(), base_bv1, precision_vol);

        // ### sp1
        k.sp1 = popDynInt(f.sp1(), base_close, precision);
        // ### sp2
        k.sp2 = popDynInt(f.sp2(), base_close, precision);
        // ### sp3
        k.sp3 = popDynInt(f.sp3(), base_close, precision);
        // ### sp4
        k.sp4 = popDynInt(f.sp4(), base_close, precision);
        // ### sp5
        k.sp5 = popDynInt(f.sp5(), base_close, precision);

        // ### sv1
        k.sv1 = popDynInt(f.sv1(), base_bv1, precision_vol);
        // ### sv2
        k.sv2 = popDynInt(f.sv2(), base_bv1, precision_vol);
        // ### sv3
        k.sv3 = popDynInt(f.sv3(), base_bv1, precision_vol);
        // ### sv4
        k.sv4 = popDynInt(f.sv4(), base_bv1, precision_vol);
        // ### sv5
        k.sv5 = popDynInt(f.sv5(), base_bv1, precision_vol);

        // ### traceCount
        k.traceCount = readIntLe(buf, tmpOffset);
        tmpOffset += 4;

        // ### neipan
        k.neipan = popDynInt(f.neipan(), base_volume, precision_vol);
        // ### limitUp
        k.limitUp = popDynInt(f.limitUp(), base_lastClose, precision);
        // ### limitDown
        k.limitDown = popDynInt(f.limitDown(), base_lastClose, precision);
        // ### position
        k.position = popDynInt(f.position(), base_0, precision_vol);
        // ### avPrice
        k.avPrice = popDynInt(f.avPrice(), base_0, precision);
        // ### temp2
        k.temp2 = popDynInt(f.temp2(), base_close, precision);

    	return k;
    }
    
    float popDynInt(int flag, int base, int prec) throws IOException
    {
        if (flag == 0x00) {
            return (float)base / prec;
        } else if (flag == 0x01) {
            // push as int8
            byte delta = buf[tmpOffset];
            tmpOffset += 1;
            return (float)(delta + base) / prec;
        }
        else if (flag == 0x02) {
            // push as int16
        	short delta = readUint16Le(buf, tmpOffset);
        	tmpOffset += 2;
            return (float)(delta + base) / prec;
        }
        else {
            // push orig as float
        	float orig = readFloatFromC(buf, tmpOffset);
        	tmpOffset += 4;
            return orig;
        }
    }

    private int p2i(float price) {
    	return (int) Math.floor(price * precision + 0.5);
    }

    private int v2i(float price) {
    	return (int) Math.floor(price * precision_vol + 0.5);
    }
}
