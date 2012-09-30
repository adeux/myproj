#include "winsock.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#pragma comment (lib,"wsock32")///所需的库文件

void main()
{
 /////////////初始化winsock环境
 WSADATA wsadata;
 WORD wVersion=MAKEWORD(2,0);/////////winsock 2.0
 if(WSAStartup(wVersion,&wsadata)!=0)
 {
  printf("initalize failed!/n");
  WSACleanup();
  exit(1);
 }


 
 int sock,csock,length;//sock是服务器端侦听套接字，csock是客户端连接套接字
 length=sizeof(struct sockaddr);


 struct sockaddr_in server_ipaddr,client_ipaddr;//用来获得服务器和客户端的地址信息
 memset(&server_ipaddr,0,length);
 server_ipaddr.sin_family=AF_INET;
 server_ipaddr.sin_port=htons(85);
 server_ipaddr.sin_addr.s_addr=inet_addr("211.81.55.200");


 char buff[4096];int nbuff;

 sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
///绑定
 if(bind(sock,(struct sockaddr *)&server_ipaddr,length)==SOCKET_ERROR)
 {
  printf("Bind error/n");
  WSACleanup();
  exit(1);
 }
////侦听
 if(listen(sock,5)==SOCKET_ERROR)
 {
  printf("Listen error/n");
  WSACleanup();
  exit(1);
 }

 /////////////
 char headers[1000];//////////保存头部
 /////////头部格式
 char hdrFmt[]=
  "HTTP/1.0 200 OK/r/n"
  "Server: MySocket Server/r/n"
  "Date: %s/r/n"
  "Content-Type: text/html/r/n"
  "Accept-Ranges: bytes/r/n"
  "Content-Length: %d/r/n/r/n";
 char * strGmtNow="08/15/14 22:53:00 GMT";///////////随便指定了一个时间
 //wsprintf(headers, hdrFmt, (const char*) strGmtNow, strlen(CustomHtml));
 //////////要传送的网页内容
 char CustomHtml[]=
  "<html>/r/n"
  "<head>/r/n"
  "<title></title>/r/n"
  "</head>/r/n"
  "<body>/r/n"
  "<p>欢迎访问我的主页</p>/r/n"
  "<h3><a href='index.html'>快乐天地</a></h3>/r/n"
  "<p>结束</p>/r/n"
  "<p>　</p>/r/n"
  "</body></html>/r/n/r/n";
 wsprintf(headers, hdrFmt, (const char*) strGmtNow, strlen(CustomHtml));

 

 //////////
 while(1)
 {
  //////////侦听到连接后，产生新的套接字
  ///////////用来和客户端传递消息
  csock=accept(sock,(struct sockaddr *)&client_ipaddr,&length);
  if(csock==SOCKET_ERROR)
  {
   printf("Listen error/n");
   WSACleanup();
   exit(1);
  }
  nbuff=recv(csock,buff,4095,0);
   buff[nbuff]='/0';
  printf("%s",buff);
 /////发送响应头部
  send(csock,headers,strlen(headers),0);
 /////发送内容 
  send(csock,CustomHtml,strlen(CustomHtml),0);
 /////////关闭本次连接
  closesocket(csock);
 }

}

