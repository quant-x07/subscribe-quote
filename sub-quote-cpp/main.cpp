#include "MqttPub.h"
#include <string>

int main(int argc, char **argv)
{
    MqttPub *pub = MqttPub::instance();
    std::string stkLabel = "IXSPX";  // 标普500指数
    if (argc > 1) {
        stkLabel = argv[1];
    }
    pub->client_init(stkLabel);
    pub->loopForever();
    pub->stopAndJoin();
    return 0;
}
