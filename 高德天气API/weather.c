#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>//socket connect
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
int main()
{
    //创建套接字
    int socket_fd = socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd == -1)
    {
        printf("socket error\n");
    }
    printf("socket success\n");
    //连接服务器http
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;//IPV4协议
    server_addr.sin_port = htons(80); //http默认端口80
    server_addr.sin_addr.s_addr = inet_addr("120.77.134.169");//高德天气的IP地址
    int flag = connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(flag == -1)
    {
        printf("connect error\n");
    }
    printf("connect success\n");
    
    /*http报文

    GET https://restapi.amap.com/v3/weather/weatherInfo?parameters HTTP/1.1\r\n
    Host:restapi.amap.com\r\n
    \r\n

    */
    char * http_str = "GET https://restapi.amap.com/v3/weather/weatherInfo?key=你的密钥&city=城市的adcode编码 HTTP/1.1\r\nHost:restapi.amap.com\r\n\r\n";
    //发送Http报文
    write(socket_fd, http_str, strlen(http_str));
    //接收服务器返回的数据
    char recv_data[1024 * 1024] = {0};
    read(socket_fd, recv_data, sizeof(recv_data));
    printf("%s\n", recv_data);
    //关闭套接字
    close(socket_fd);

}