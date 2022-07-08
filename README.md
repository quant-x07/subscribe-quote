# subscribe-quote
订阅行情数据

通过程序订阅股票实时数据，例如如下命令可订阅 SH600000 股票实时数据
```
./tstClient SH600000
```
数据信息包括当前K线的开高低收、当前盘口的5档数据等等

例如，如下命令可订阅标普500指数
```
./tstClient IXSPX
```

输出如下，注意 c: 一列是不断变化的
```
loopForever tid 139796787160896
ThreadProc tid 139796787156736
on_connect: Connection Accepted.
sub rc 0
Packet ID 1: The topic has been subscribed.
1657209963 IXSPX 3845.080078
o:3858.850098 h:3892.790039 l:3858.850098 ~c:3891.290039~ v:820534784.000000 a:0.000000
bp1:0.000000 bp2:0.000000 bp3:0.000000 bp4:0.000000 bp5:0.000000
bv1:0.000000 bv2:0.000000 bv3:0.000000 bv4:0.000000 bv5:0.000000
cnt:0 neipan:0.000000 limitUp:0.000000 limitDown:0.000000 position: 0.000000 avPrice:0.000000 temp2: 3891.919922
1657209964 IXSPX 3845.080078
o:3858.850098 h:3892.790039 l:3858.850098 ~c:3891.260010~ v:820574656.000000 a:0.000000
bp1:0.000000 bp2:0.000000 bp3:0.000000 bp4:0.000000 bp5:0.000000
bv1:0.000000 bv2:0.000000 bv3:0.000000 bv4:0.000000 bv5:0.000000
cnt:0 neipan:0.000000 limitUp:0.000000 limitDown:0.000000 position: 0.000000 avPrice:0.000000 temp2: 3891.919922
1657209965 IXSPX 3845.080078
o:3858.850098 h:3892.790039 l:3858.850098 ~c:3891.290039~ v:820660800.000000 a:0.000000
bp1:0.000000 bp2:0.000000 bp3:0.000000 bp4:0.000000 bp5:0.000000
bv1:0.000000 bv2:0.000000 bv3:0.000000 bv4:0.000000 bv5:0.000000
cnt:0 neipan:0.000000 limitUp:0.000000 limitDown:0.000000 position: 0.000000 avPrice:0.000000 temp2: 3891.919922
```

## Linux 下编译方法
在 ubuntu 18.04 验证通过

* 编译

安装依赖包
```
sudo apt-get install libmosquitto-dev zlib1g-dev
```

编译
```
cd sub-quote-cpp
cmake .
make
```

* 运行
```
./tstClient
```

* 注意
默认体验密码和服务器地址都已经在程序中固定，有需求可以联系我们获取独立的用户名密码