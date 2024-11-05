#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
int main(int argc,char *argv[])
{
int sockmain,sockcli,i,j;
int child;
char buffer[50],buffer1[50];
struct sockaddr_in servaddr,cliaddr;
if(argc !=3)
{
printf("Usage:client <portno> <server>\n");
exit(1);
}
sockmain=socket(AF_INET,SOCK_STREAM,0);
if(sockmain < 0)
{
printf("socket");
exit(1);
}
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[2]);
servaddr.sin_port=htons(atoi(argv[1]));
if(connect(sockmain,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
{
printf("error in connect\n");
exit(0);
}
printf("enter a message\n");
fgets(buffer,70,stdin);
write(sockmain,buffer,sizeof(buffer));
read(sockmain,buffer1,sizeof(buffer1));
printf("client recd the message %s\n",buffer1);
close(sockmain);
}