#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include "device.h"

int main() {
	int h = socket(PF_INET, SOCK_STREAM, 0);
	if (h < 0) {
		perror("creating socket");
	}
	const int PORT = 5679;
	struct sockaddr_in local;
	// inet_aton(
	local.sin_family = PF_INET;
	local.sin_port = htons(PORT);
 	if (bind(h, (sockaddr *)&local, sizeof local) < 0) {
    		perror("bind");
		close(h);
		return 1;
  	}
  	if (listen(h, 10) < 0) {
    		perror("listen"); close(h); return 2;
  	}
	int qw;
	vector <Device*> my_device;
	SOURCE *my_source;
	SCREEN * my_screen;
  	for (;;) {
		char buf[512] = "";
		int connect_socket;
		struct sockaddr_in remote;
		unsigned remoteLen = sizeof remote;
		connect_socket = accept(h, (sockaddr *)&remote, &remoteLen);
		qw = connect_socket;
		printf("Accepted!\n");
		int rd = read(connect_socket, buf, sizeof buf);
		printf("read %d bytes '%s'\n", rd, buf);
//		close(connect_socket);
		if (buf[0] == 'F') {
	  		printf("FINISH\n");
	  		break;
		}

        	int check = buf[0] - '0';
		printf("check = %d\n", check);
        	switch(check){
                	case 0: //source
                	        {
                        	int a1, x, y;
                        	sscanf(buf,"%d %d %d",&a1, &x, &y);
                        	my_source = new SOURCE(x, y);
//                      	= new SOURCE(x, y);
				printf("Source was made\n");
                        	break;
                        	}
                	case 1: //screen
                        	{
                        	int a1, x1, y1, x2, y2;
                        	sscanf(buf, "%d %d %d %d %d", &a1, &x1, &y1, &x2, &y2);
                        	my_screen = new SCREEN (x1,y1, x2,y2);
//				=new screen(x1, y1, x2, y2);
				printf("Screen was made\n");
                        	break;
                        	}
                	case 2: //lens
                        	{
                        	int a1, x, y, l, deg, f;
                        	sscanf(buf, "%d %d %d %d %d %d",&a1,&x, &y, &l, &deg, &f);
//                      	printf("%d %d %d %d %d %d\n", a1, a2,a3,a4,a5,a6);
                        	Device  *d = new Lens(x, y, l, deg, f);
                        	my_device.push_back(d);
				printf("New lens was created");
                        	break;
                        	}
        	}
//		sleep(1);
		int wr = write(qw, "1", 1);
		close(connect_socket);
  	}
	printf("%f %f \n",my_device[0]->x1, my_device[0]->y1);
	sleep(3);
	int wr = write(qw, "1", 1);
	close(qw);
	close(h);
}
  
