[toc]
### 远程桌面设计概要

### 控制消息协议定义 V1.0
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
cmd[5] = deltaHB; //delta hight bit.
cmd[6] = deltaHB; //delta low bit.


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

### 键盘指令传输与解析
1. 采用从QKeyEvent中获取当前控制端按下的键值
2. 键值映射转换是否应该在服务端处理？
如下场景：
2.1 控制端：Windows，被控制端：Linux/Mac
如果在控制端解析出映射的键值，在被控制端仍然需要处理。
而如果在被控制端解析键值映射，然后即可按当前系统特性响应键盘操作。
3. Qt键盘键位值映射
QKeyEvent::nativeModifiers()
QKeyEvent::nativeScanCode()
QKeyEvent::nativeVirtualKey()

4. Windows响应键盘操作
```C++

/*
@brief	VK_ESCAPE	0x1B	ESC 键
	Qt::Key_Escape	0x01000000
	nativeScanCode:  1  nativeVirtualKey:  27  nativeModifiers:  0

	int key = 0x1B;
	short sVkCode = VkKeyScan(0x1B);
	sVkCode = 1;
	keybd_event(sVkCode, MapVirtualKey(sVkCode, 0), KEYEVENTF_EXTENDEDKEY, 0)
*/

void SMsgHandler::keyPressed(int key)
{
    short sVkCode = VkKeyScan(key);

    //! virtual key code must between 1 and 254, [1, 254]
    if ( sVkCode < 1 || sVkCode > 254) {
        sVkCode = key;
    }

    BYTE bScan = MapVirtualKey(sVkCode, 0);
    keybd_event(sVkCode, bScan, KEYEVENTF_EXTENDEDKEY, 0);
}
```
5. 能否构建一个QKeyEvent事件，然后响应，来实现键盘操作？




### 控制消息协议定义 V2.0
1. 协议长度20字节
2. 协议组成
3. 支持鼠标移动/按键消息，键盘按键消息
- 键盘按键消息协议内容
``` 
char c[20];

//!
c[0] 消息类型（鼠标移动/按键消息，键盘按键消息）
c[1] 控制端系统类型（客户端），Windows/Linux/Mac
c[2] 被控制端系统类型（服务端），Windows/Linux/Mac
c[3] 扩展数据位，Qt::KeyboardModifiers modifiers

//! 键盘键值key value，int32_t
c[4]
c[5]
c[6]
c[7]

//! 原始扫描码，nativeScanCode，int32_t
c[8]
c[9]
c[10]
c[11]

//! 原始虚拟键值，nativeVirtualKey，int32_t
c[12] 
c[13]
c[14]
c[15]

//! 原始modify，nativeModifiers，int32_t
c[16] 
c[17]
c[18]
c[19]
```

- 鼠标消息协议内容
``` 
char c[20];

//!
c[0] 消息类型（鼠标移动/按键消息，键盘按键消息）
c[1] 控制端系统类型（客户端），Windows/Linux/Mac
c[2] 被控制端系统类型（服务端），Windows/Linux/Mac
c[3] 扩展数据位，

//! 鼠标位置（pt.x），int32_t
c[4] 
c[5] 
c[6] 
c[7] 

//! 鼠标位置（pt.y），int32_t
c[8] 
c[9] 
c[10]
c[11]

//! 鼠标滚轮步进（delta），int32_t
c[12]  
c[13] 
c[14] 
c[15] 

//! 
c[16]
c[17] 
c[18] 
c[19] 
```

### 协议数据存储及解析
- 读取4字节
```C++
//! 
RCBuffer::RCBuffer(char* b, int nn)
{
    p = bytes = b;
    nb_bytes = nn;
}

//! 跳过一定字节数
void RCBuffer::skip(int size)
{
    assert(p);
    assert(p + size >= bytes);
    assert(p + size <= bytes + nb_bytes);
    
    p += size;
}

void RCBuffer::write_1bytes(int8_t value)
{
    assert(require(1));
    
    *p++ = value;
}

int32_t RCBuffer::read_4bytes()
{
    assert(require(4));
    
    int32_t value;
    char* pp = (char*)&value;
    pp[3] = *p++;
    pp[2] = *p++;
    pp[1] = *p++;
    pp[0] = *p++;
    
    return value;
}

```
- client write data
```C++
//! eg, keyboard value
char c[20];
RCBuffer rcBuffer(c, 20);

//! write data
//! c[0] 消息类型
int8_t msgType = CMDTYPE::CMD_KEY_PRESS;
rcBuffer.write_1bytes(msgType);
rcBuffer.skip(1);

//! c[1] 控制端系统类型
int8_t controlSysType = Windows;
rcBuffer.write_1bytes(controlSysType);
rcBuffer.skip(1);

//! c[2] 被控制端系统类型
int8_t controlledSysType = null;
rcBuffer.write_1bytes(controlSysType);
rcBuffer.skip(1);

//! c[3] 扩展数据位
int8_t extraData = 0;
rcBuffer.write_1bytes(extraData);
rcBuffer.skip(1);

//! c[4] c[5] c[6] c[7] 键盘键值（4字节存储，int32_t）
int32_t keyValue = 0x20;
rcBuffer.write_4bytes(keyValue);
rcBuffer.skip(4);

//! c[8] c[9] c[10] c[11] 原始扫描码（4字节存储，int32_t）
int32_t scanCode = 0x20;
rcBuffer.write_4bytes(scanCode);
rcBuffer.skip(4);

//! c[12] c[13] c[14] c[15] 原始虚拟键值（4字节存储，int32_t）
int32_t virtualKey = 0x20;
rcBuffer.write_4bytes(virtualKey);
rcBuffer.skip(4);

//! c[16] c[17] c[18] c[19] 原始modify（4字节存储，int32_t）
int32_t modifier = 0x20;
rcBuffer.write_4bytes(modifier);
rcBuffer.skip(4);

//! client send data to client...

```

- server read data
```C++
//! eg, keyboard value

//! server read from client... 

char c[20];
RCBuffer rcBuffer(c, 20);

//! write data
//! c[0] 消息类型
int8_t msgType = CMDTYPE::CMD_KEY_PRESS;
rcBuffer.read_1bytes(msgType);
rcBuffer.skip(1);

//! c[1] 控制端系统类型
int8_t controlSysType = Windows;
rcBuffer.read_1bytes(controlSysType);
rcBuffer.skip(1);

//! c[2] 被控制端系统类型
int8_t controlledSysType = null;
rcBuffer.read_1bytes(controlSysType);
rcBuffer.skip(1);

//! c[3] 扩展数据位
int8_t extraData = 0;
rcBuffer.read_1bytes(extraData);
rcBuffer.skip(1);

//! c[4] c[5] c[6] c[7] 键盘键值（4字节存储，int32_t）
int32_t keyValue = 0x20;
rcBuffer.read_4bytes(keyValue);
rcBuffer.skip(4);

//! c[8] c[9] c[10] c[11] 原始扫描码（4字节存储，int32_t）
int32_t scanCode = 0x20;
rcBuffer.read_4bytes(scanCode);
rcBuffer.skip(4);

//! c[12] c[13] c[14] c[15] 原始虚拟键值（4字节存储，int32_t）
int32_t virtualKey = 0x20;
rcBuffer.read_4bytes(virtualKey);
rcBuffer.skip(4);

//! c[16] c[17] c[18] c[19] 原始modify（4字节存储，int32_t）
int32_t modifier = 0x20;
rcBuffer.read_4bytes(modifier);
rcBuffer.skip(4);

```