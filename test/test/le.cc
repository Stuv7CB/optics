#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>

int h;
int cs;

void handler(int nsig)
{
    	if(nsig==SIGINT)
    	{
        	close(cs);
        	close(h);
        	printf("Shutting down\n");
        	exit(0);
    	}
}

int main() 
{
    	(void)signal(SIGINT, handler);
    	h = socket(PF_INET, SOCK_STREAM, 0);
    	char buf[512];
    	if (h < 0){
        	perror("Creating socket");
    	}
    	const int PORT = 5678;
    	struct sockaddr_in local;
    	local.sin_family = PF_INET;
    	local.sin_port = htons(PORT);
    	if(bind(h, (sockaddr *)&local, sizeof(local)) < 0){
        	perror("Binding");
        	close(h);
        	return 1;
    	}
    	if (listen(h, 10) < 0) 
    	{
        	perror("Listening"); 
        	close(h); 
        	return 2;
    	}
    	struct sockaddr_in remote;
    	unsigned remoteLen=sizeof(remote);
    	if((cs=accept(h, (sockaddr *)&remote, &remoteLen))<0)
    	{
        	perror("Accepting");
        	return 3;
    	}
    	int rd;
    	sendto(cs, "1", 1, 0, (sockaddr *)&remote, remoteLen);
    	while((rd=recvfrom(cs, buf, sizeof(buf), 0, (sockaddr *)&remote, &remoteLen))>0)
    	{
        	buf[rd]=0;
        	printf("%s\n", buf);
        	fflush(stdout);
        	buf[0]=0;
        	sendto(cs, "1", 1, 0, (sockaddr *)&remote, remoteLen);
    	}
    	close(cs);
    	close(h);
}  
