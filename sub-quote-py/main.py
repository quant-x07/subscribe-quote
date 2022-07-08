from MqttSub import MqttSub

if __name__ == '__main__':
    sub = MqttSub()
    sub.client_init('SH600000')
    sub.loopForever()
