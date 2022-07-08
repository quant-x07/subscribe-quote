import sys
from MqttSub import MqttSub

if __name__ == '__main__':
    sub = MqttSub()
    stkLabel = 'SH000001'
    if len(sys.argv) > 1:
        stkLabel = sys.argv[1]

    sub.client_init(stkLabel)
    sub.loopForever()
