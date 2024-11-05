#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
void togglecase(char *a,int cnt); 
int main(int argc,char *argv[])
{
int sockfd,newsockfd,clilen,n; struct
sockaddr_in servaddr,cliaddr; char
a[50];
int cnt=80;
int pid;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(argc!=2)
{
printf("Usage: <server> <portno>");
exit(0);
}
if(sockfd < 0)
{
printf("can't create"); exit(0);
}
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("172.0.5.48");
servaddr.sin_port=htons(atoi(argv[1]));
if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0 )
{
printf("can't bind");
exit(0);
}
while(1)
{
clilen=sizeof(cliaddr);
if(recvfrom(sockfd,a,50,0,(struct sockaddr *)&cliaddr,&clilen) <0)
{
printf("error in recvfrom\n"); exit(0);
}
printf("server recd the message:%s\n",a);
pid=fork();
if(pid ==0)
{

togglecase(a,cnt);
if(sendto(sockfd,a,50,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr) )<0)
{
printf("error in sendto\n"); exit(0);
}
}
}
close(sockfd);
}
void togglecase(char *a,int cnt)
{
int i; for(i=0;i<cnt;i++)
{
if((a[i] >='A') && (a[i] <= 'Z'))
a[i] += 0X20;
else if((a[i] >='a') && (a[i] <='z')) a[i]
-= 0X20;
}
}