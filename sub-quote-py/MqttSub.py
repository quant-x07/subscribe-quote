#import zlib
from paho.mqtt import client as mqtt_client
from TraceCompress import TraceCompress

class MqttSub(object):
    def __init__(self):
        self.broker = '121.4.14.59'
        self.port = 1883
        self.username = 'test'
        self.password = 'test'

    def client_init(self, stkLabel):
        def on_connect(client, userdata, flags, rc):
            if rc == 0:
                print("Connected to MQTT Broker!")
            else:
                print("Failed to connect, return code %d\n", rc)

        def on_message(client, userdata, msg):
            #data = zlib.decompress(msg.payload)
            data = msg.payload
            print("Received %s -> %s from %s topic" % (len(msg.payload), len(data), msg.topic))
            compress = TraceCompress()
            trace = compress.initBuf(data)
            while not compress.isAtEnd():
                k = compress.decompress()
                print("trace解压后: %s" % k.stkLabel)
                k.dump(False)

        def on_subscribe(mosq, obj, mid, granted_qos):
            print("Subscribed: " + str(mid) + " " + str(granted_qos))

        self.client = mqtt_client.Client()
        self.client.username_pw_set(self.username, self.password)
        self.client.on_connect = on_connect
        self.client.on_message = on_message
        self.client.connect(self.broker, self.port)
        topic = 'quote/' + stkLabel
        self.client.subscribe(topic, 0)

    def loopForever(self):
        # Continue the network loop, exit when an error occurs
        rc = 0
        while rc == 0:
            rc = self.client.loop()
        print("rc: " + str(rc))
