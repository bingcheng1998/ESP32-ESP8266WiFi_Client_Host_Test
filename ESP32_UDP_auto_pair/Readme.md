# ESP32/ESP8266 WiFi UDP

这是一个WiFi开发板的UDP数据传输实验的代码。

已经在`ESP8266 NodeMCU` 与`ESP32 Dev module` 上面测试通过。

## Arduino 端

<table>
    <tr>
        <td ><center><img src="https://ws2.sinaimg.cn/large/006tNc79ly1fyvhgwppz6j30rs0xcdi3.jpg" >图1  Arduino 程序界面 </center></td>
        <td ><center><img src="https://ws2.sinaimg.cn/large/006tNc79ly1fyvho4xc3xj30x60ne0vb.jpg"  >图2 ESP8266 设置</center></td>
        <td ><center><img src="https://ws2.sinaimg.cn/large/006tNc79ly1fyvho4xc3xj30x60ne0vb.jpg"  >图3 ESP32 设置</center></td>
    </tr>
</table>
## Processing 端

<table>
    <tr>
        <td ><center><img src="https://ws3.sinaimg.cn/large/006tNc79ly1fyvhpntyaij30xr0u0q4c.jpg" >图1  Processing 程序界面 </center></td>
        <td ><center><img src="https://ws4.sinaimg.cn/large/006tNc79ly1fyvhqiiw58j307408cmwy.jpg"  >图2 交互窗口</center></td>
        <td ><center><img src="https://ws3.sinaimg.cn/large/006tNc79ly1fyvhri6kk2j30n606kt8y.jpg"  >图3 目标IP与端口设置</center></td>
    </tr>
</table>

## 程序测试

### 1. 程序开始

```c++
//---------Program Begin----------//


Connecting to fisher...
...
IP address: 
192.168.253.55
WiFi connected
UDP connecting...
...................................
...................................
...................................
...................................
```

### 2. 当接收到非`s`的开始信息

```bash
Received packet of size 1
From 192.168.253.46, port 1998
You should sent 's' to start udp connection instead of Q
```

### 3. 当接收到`s`时

```bash
Received packet of size 1
From 192.168.253.46, port 6767
UDP connected
```

### 4. 之后任意发送信息

```bash
Received packet of size 1
From 192.168.253.46, port 6767
message received:	[2]
Received packet of size 1
From 192.168.253.46, port 6767
message received:	[3]
Received packet of size 1
From 192.168.253.46, port 6767
message received:	[g]
Received packet of size 1
From 192.168.253.46, port 6767
message received:	[s]
```





