[toc]
### 远程桌面设计概要

### 控制消息协议定义
1. 协议长度
8字节
2. 协议组成
```C++

/*
@brief client/server operation cmd define
*/
enum CMDTYPE
{
	CMD_UNKNOWN             = 0,
	CMD_MOUSE_MOVE_TO		= 1,
	CMD_MOUSE_LEFT_DOWN		= 2,
	CMD_MOUSE_LEFT_UP		= 3,
	CMD_MOUSE_RIGHT_DOWN	= 4,
	CMD_MOUSE_RIGHT_UP		= 5,
	CMD_MOUSE_WHEEL			= 6,
	CMD_MOUSE_DOUBLE_CLICK	= 7,
	CMD_KEY_PRESS			= 8,
	CMD_KEY_RELEASE			= 9,
	CMD_GET_SCREEN_SIZE		= 11,
	CMD_GET_SCREEN_SIZE_RES = 12,
};

unsigned char cmd[8] = {0};

cmd[0] = CMDTYPE::CMD_UNKNOWN;

//! 鼠标消息
//! 1. 鼠标左键按下
cmd[0] = CMDTYPE::CMD_MOUSE_LEFT_DOWN;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.

//! 鼠标消息
//! 11. 鼠标左键弹起
cmd[0] = CMDTYPE::CMD_MOUSE_LEFT_UP;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.

//! 2. 鼠标右键按下
cmd[0] = CMDTYPE::CMD_MOUSE_RIGHT_DOWN;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.

//! 21. 鼠标右键弹起
cmd[0] = CMDTYPE::CMD_MOUSE_RIGHT_UP;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.

//! 3. 鼠标中键按下
cmd[0] = CMDTYPE::CMD_MOUSE_MID_DOWN;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.

//! 31. 鼠标中键弹起
cmd[0] = CMDTYPE::CMD_MOUSE_MID_UP;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.


//! 4. 鼠标左键双击
cmd[0] = CMDTYPE::CMD_MOUSE_DOUBLE_CLICK;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.


//! 5. 鼠标移动 
cmd[0] = CMDTYPE::CMD_MOUSE_MOVE_TO;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.

//! 6. 鼠标框选


//! 7. 鼠标滚轮
cmd[0] = CMDTYPE::CMD_MOUSE_WHEEL;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.



//! 键盘消息
//! 1.普通单键按下
cmd[0] = CMDTYPE::CMD_KEY_PRESS;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.


//! 11.普通单键弹起
cmd[0] = CMDTYPE::CMD_KEY_RELEASE;
cmd[1] = xHB;   //x pos hight bit.
cmd[2] = xLB;   //x pos low bit.
cmd[3] = yHB;   //x pos hight bit.
cmd[4] = yLB;   //x pos low bit.

//! 2.组合键



```


3. 

### 控制消息存储解析设计
1. 构建基础消息数据，大小8字节
2. 构建存储解析消息基类，提供设置/获取基础数据接口，设置/获取鼠标位置		x/y（or 宽高w/h）数据接口
   基础消息默认第一个字节存储消息类型，第二三四五字节存储鼠标位置x/y（or 宽高w/h）信息
3. 解析子类中实现不同类型消息设置/获取特定数据的接口
4. 鼠标位置，宽高存储的数值无法用一个字节存储，两个字节可以表达。
   2^8 = 256, 2^16 = 65536。因此拆解为两个字节存储
5. 

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



### 客户端/服务端 类结构
```
CMsgReader <---> SMsgWriter
CMsgWriter <---> SMsgReader
CImgReader <---> SImgWriter
```

