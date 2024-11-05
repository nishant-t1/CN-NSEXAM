#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc,char *argv[])
{
int sockmain,sockcli,i,j;
int child;
char buffer[512];
struct sockaddr_in servaddr,cliaddr;
if(argc !=3)
{
printf("Usage:server <portno>\n");
exit(1);
}
sockmain=socket(AF_INET,SOCK_STREAM,0);
if(sockmain < 0)
{
printf("error in server socket");
exit(1);
}
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[2]);
servaddr.sin_port=htons(atoi(argv[1]));
if(bind(sockmain,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
{
printf("error in bind");
exit(1);
}
if(listen(sockmain,5) < 0)
{
printf("error in listen");
exit(1);
}

i=sizeof(cliaddr);
sockcli=accept(sockmain,(struct sockaddr *)&cliaddr,&i);
if(sockcli<0)
{
printf("error in accept");
exit(1);
}

read(sockcli,buffer,sizeof(buffer));
printf("server received message %s\n",buffer);
write(sockcli,buffer,sizeof(buffer));
close(sockcli);
}