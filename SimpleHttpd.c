#include "winsock.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#pragma comment (lib,"wsock32")///����Ŀ��ļ�

void main()
{
 /////////////��ʼ��winsock����
 WSADATA wsadata;
 WORD wVersion=MAKEWORD(2,0);/////////winsock 2.0
 if(WSAStartup(wVersion,&wsadata)!=0)
 {
  printf("initalize failed!/n");
  WSACleanup();
  exit(1);
 }


 
 int sock,csock,length;//sock�Ƿ������������׽��֣�csock�ǿͻ��������׽���
 length=sizeof(struct sockaddr);


 struct sockaddr_in server_ipaddr,client_ipaddr;//������÷������Ϳͻ��˵ĵ�ַ��Ϣ
 memset(&server_ipaddr,0,length);
 server_ipaddr.sin_family=AF_INET;
 server_ipaddr.sin_port=htons(85);
 server_ipaddr.sin_addr.s_addr=inet_addr("211.81.55.200");


 char buff[4096];int nbuff;

 sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
///��
 if(bind(sock,(struct sockaddr *)&server_ipaddr,length)==SOCKET_ERROR)
 {
  printf("Bind error/n");
  WSACleanup();
  exit(1);
 }
////����
 if(listen(sock,5)==SOCKET_ERROR)
 {
  printf("Listen error/n");
  WSACleanup();
  exit(1);
 }

 /////////////
 char headers[1000];//////////����ͷ��
 /////////ͷ����ʽ
 char hdrFmt[]=
  "HTTP/1.0 200 OK/r/n"
  "Server: MySocket Server/r/n"
  "Date: %s/r/n"
  "Content-Type: text/html/r/n"
  "Accept-Ranges: bytes/r/n"
  "Content-Length: %d/r/n/r/n";
 char * strGmtNow="08/15/14 22:53:00 GMT";///////////���ָ����һ��ʱ��
 //wsprintf(headers, hdrFmt, (const char*) strGmtNow, strlen(CustomHtml));
 //////////Ҫ���͵���ҳ����
 char CustomHtml[]=
  "<html>/r/n"
  "<head>/r/n"
  "<title></title>/r/n"
  "</head>/r/n"
  "<body>/r/n"
  "<p>��ӭ�����ҵ���ҳ</p>/r/n"
  "<h3><a href='index.html'>�������</a></h3>/r/n"
  "<p>����</p>/r/n"
  "<p>��</p>/r/n"
  "</body></html>/r/n/r/n";
 wsprintf(headers, hdrFmt, (const char*) strGmtNow, strlen(CustomHtml));

 

 //////////
 while(1)
 {
  //////////���������Ӻ󣬲����µ��׽���
  ///////////�����Ϳͻ��˴�����Ϣ
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
 /////������Ӧͷ��
  send(csock,headers,strlen(headers),0);
 /////�������� 
  send(csock,CustomHtml,strlen(CustomHtml),0);
 /////////�رձ�������
  closesocket(csock);
 }

}

