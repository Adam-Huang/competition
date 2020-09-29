# socket 编程基础

![socket连接的基础过程](http://images.cnblogs.com/cnblogs_com/helloworldcode/1414395/o_05232335-fb19fc7527e944d4845ef40831da4ec2.png)

关于参数和代码实现，参考同目录代码`01_server.cpp & 01_client.cpp`和[C语言中文网教程](http://c.biancheng.net/view/2131.html)

- 创建`socket`函数

  1. 主要包括两种套接字：`SOCK_STREAM`和`SOCK_DGRAM`
  2. 理论上说，前两个参数是可以确定套接字的，但是有一种特殊情况还是要指定协议类型。

- `bind`

  1. 强制转换的那个数据结构是为了兼容`IPv4`和`IPv6`

- `accept`

  1. 返回值是一个新的套接字，`addr`参数也保存了客户端的`IP`地址和端口号等

- 缓冲区：

  1. 每个 socket 被创建后，都会分配两个缓冲区，输入缓冲区和输出缓冲区；一般大小是`8K`

     ![](http://c.biancheng.net/uploads/allimg/190219/1149355056-0.jpg)

  2. `write`之后是写入缓冲区，由TCP负责发送。

**循环读写代码`02_server.cpp & 02_client.cpp`**

