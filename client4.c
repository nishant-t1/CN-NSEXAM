#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc,char *argv[])
{
int sockfd,i;
int read_frm_stdin,read_frm_sock;
char buffer[512];
struct sockaddr_in servaddr;
if(argc !=3)
{
printf("Client :Usage:client <portno> <server_name>\n"); exit(1);
}
sockfd=socket(AF_INET,SOCK_STREAM,0); if(sockfd
< 0)
{
perror("socket");
exit(1);
}
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[2]);
servaddr.sin_port=htons(atoi(argv[1]));
if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
{
perror("connect");
exit(1);
}
write(sockfd,"the time and date is",50);
read(sockfd,buffer,sizeof(buffer));
printf("Client received the time and date is:%s\n",buffer);
close(sockfd);
}