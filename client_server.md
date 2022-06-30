
### 远程桌面设计概要


### 服务端server
1. 窗口程序，便于后续显示客户端连接信息，或设置服务端参数
2. 定义服务端初始化参数（服务端桌面分辨率）
3. 

- server
create socket->bind->listen->accept->recv/send

- client
create socket->connect->send->send/recv

select

### 客户端client