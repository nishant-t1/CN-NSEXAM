#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h> 
#include <time.h>
int main(int argc,char *argv[])
{
int sockfd,newsockfd,clilen,i,pid; 
char buffer[512],a[50];
long t;
char *st;
struct sockaddr_in servaddr,cliaddr; if(argc!=3)
{
printf("Usage:server <portno>\n"); exit(1);
}
sockfd=socket(AF_INET,SOCK_STREAM,0); if(sockfd
< 0)
{
printf("error server socket\n");
exit(1);
}
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[2]);
servaddr.sin_port=htons(atoi(argv[1]));
if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
{
printf("error in bind");
exit(1);
}
if(listen(sockfd,5) < 0)
{
printf("listen");
exit(1);
}
for(; ;)
{
clilen=sizeof(cliaddr);
newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen); if(newsockfd<0)
{
printf("accept");
exit(1);
}
if((pid==fork())<0)
{
printf("server failed to creat child");
exit(1);
}
else
{

while(i=read(newsockfd,buffer,sizeof(buffer))!=0)
{
if(i<0)
{
printf("error in read");
exit(1);
}
t=time(&t);
st=(char *)ctime(&t);
strcpy(buffer,st);
i=strlen(st);

printf("server received %s %s",a,buffer);

if(write(newsockfd,buffer,i)!=i)
{
printf("error in write\n"); exit(1);
}
} 

} 
close(newsockfd);
}
}