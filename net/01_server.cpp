/*
http://c.biancheng.net/view/2128.html
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // serv_sock == 3

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
	/*
	(gdb) p serv_addr
	$2 = {sin_family = 2, sin_port = 53764, sin_addr = {s_addr = 16777343}, sin_zero = "\000\000\000\000\000\000\000"}
	*/
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	// 为什么此处要强制转换成sockaddr类型: http://c.biancheng.net/view/2344.html
	

    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);

    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size); // 阻塞等待 -> 连接之后clnt_sock == 4，可以理解成是文件描述符的第4位

    //向客户端发送数据
    char str[] = "http://c.biancheng.net/socket/";
    write(clnt_sock, str, sizeof(str));
   
    //关闭套接字
    close(clnt_sock);
    close(serv_sock);

    return 0;
}
