#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(int argc,char *argv[])
{
int sockfd,servlen;
char a[50],a1[50];
struct sockaddr_in servaddr,cliaddr;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(argc!=3)
{
printf("usage:<client> <port> <ipaddress>\n");
exit(0);
}
if(sockfd < 0)
{
printf("can't bind");
exit(0);
}
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[2]);
servaddr.sin_port=htons(atoi(argv[1]));
cliaddr.sin_family=AF_INET;
cliaddr.sin_addr.s_addr=inet_addr(argv[2]);
cliaddr.sin_port=htons(0);
bind(sockfd,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
printf("enter a Percentage:");
fgets(a,50,stdin);
servlen=sizeof(servaddr);
sendto(sockfd,a,50,0,(struct sockaddr*)&servaddr,servlen);
recvfrom(sockfd,a1,50,0,(struct sockaddr*)&servaddr,&servlen);
printf("client received msg:%s",a1);
}