package top.x07.tstClient;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import top.x07.tstClient.traceCompress.TraceCompress;

public class OnMessageCallback implements MqttCallback {
	public void connectionLost(Throwable cause) {
        // 连接丢失后，一般在这里面进行重连
        System.out.println("连接断开，可以做重连");
    }

    public void messageArrived(String topic, MqttMessage message) throws Exception {
        // subscribe后得到的消息会执行到这里面
        System.out.println("接收消息主题:" + topic);
        System.out.println("接收消息Qos:" + message.getQos());
        System.out.println("接收消息内容:" + String.valueOf(message.getPayload().length));
        // byte[] data = CompressUtil.decompress(message.getPayload());
        // System.out.println("zlib解压后大小:" + String.valueOf(data.length));
        TraceCompress compress = new TraceCompress();
        compress.initBuf(message.getPayload());
        Trace k = null;
        while (!compress.isAtEnd()) {
        	k = compress.decompress();
        	System.out.println("trace解压后:" + k.stkLabel);
        	k.dump(false);
        }
    }

    public void deliveryComplete(IMqttDeliveryToken token) {
        System.out.println("deliveryComplete---------" + token.isComplete());
    }
}
