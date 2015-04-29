#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
//#include "ray.h"    //was included in "device.h"
//#include "device.h" //was included in "sort.h"
#include "sort.h"

int h;
int cs;

void handler(int nsig){
    	if(nsig==SIGINT){
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
    	const int PORT = 5555;
    	struct sockaddr_in local;
    	local.sin_family = PF_INET;
    	local.sin_port = htons(PORT);
    	if(bind(h, (sockaddr *)&local, sizeof(local)) < 0){
        	perror("Binding");
        	close(h);
        	return 1;
    	}
    	if (listen(h, 10) < 0){
        	perror("Listening"); 
        	close(h); 
        	return 2;
    	}
    	struct sockaddr_in remote;
    	unsigned remoteLen=sizeof(remote);
    	if((cs=accept(h, (sockaddr *)&remote, &remoteLen))<0){
        	perror("Accepting");
        	return 3;
    	}
    	int rd;
        vector <Device*> my_device;
        SCREEN *my_screen;
        Laser *my_laser;

    	sendto(cs, "1", 1, 0, (sockaddr *)&remote, remoteLen);
    	while((rd=recvfrom(cs, buf, sizeof(buf), 0, (sockaddr *)&remote, &remoteLen))>0){
        	buf[rd]=0;
        	printf("%s\n", buf);
                int check = buf[0] - '0';
                printf("check = %d\n", check);
                switch(check){
                        case 1: //screen
                                {
                                float a1, x1, y1, x2, y2;
                                sscanf(buf, "%f %f %f %f %f", &a1, &x1, &y1, &x2, &y2);
                                my_screen = new SCREEN (x1,y1, x2,y2);
                                printf("Screen was created\n");
                                break;
                                }
                        case 2: //lens f>0
                                {
                                float a1, x, y, l, deg, f;
                                sscanf(buf, "%f %f %f %f %f %f",&a1,&x, &y, &l, &deg, &f);
                                Device  *d = new Lens(x, y, l, deg, f);
                                my_device.push_back(d);
                                printf("New lens f>0 was created\n");
                                break;
				}
			case 3:	//lens f<0
				{
                                float a1, x, y, l, deg, f;
                                sscanf(buf, "%f %f %f %f %f %f",&a1,&x, &y, &l, &deg, &f);
//                                Device  *d = new Lens(x, y, l, deg, f);
//                                my_device.push_back(d);
                                printf("New lens f<0 was created\n");
				break;
				}
			case 4:	//ploskoparallell plastinka
				{
                                float a1, x, y, len, wid, n;
                                sscanf(buf, "%f %f %f %f %f %f",&a1,&x, &y, &len, &wid, &n);
//                                Device  *d = new Lens(x, y, l, deg, f);
//                                my_device.push_back(d);
                                printf("New ploskoparallell plastinka was created\n");
				break;
				}
                        case 5: //Laser
                                {
                                float a1, x, y, deg;
                                sscanf(buf, "%f %f %f %f", &a1,&x, &y, &deg);
                                my_laser = new Laser(x, y, deg);
				printf("New laser was created\n");
                                break;
                                }
			case 6:	//sphere mirror
				{
                                float a1, x, y, r, deg1, deg2;
                                sscanf(buf, "%f %f %f %f %f %f",&a1,&x, &y, &r, &deg1, &deg2);
//                                Device  *d = new Lens(x, y, l, deg, f);
//                                my_device.push_back(d);
                                printf("New sphere mirror was created\n");
				break;
				}
			case 7:	//mirror
				{
                                float a1, x, y, deg;
                                sscanf(buf, "%f %f %f %f",&a1,&x, &y, &deg);
//                                Device  *d = new Lens(x, y, l, deg, f);
//                                my_device.push_back(d);
                                printf("New mirror was created\n");
				break;
				}
			case 8:	//triangle prism
				{
                                float a1, x1, y1, x2, y2, x3, y3, n;
                                sscanf(buf, "%f %f %f %f %f %f %f %f",&a1,&x1, &y1, &x2, &y2, &x3, &y3, &n);
//                                Device  *d = new Lens(x, y, l, deg, f);
//                                my_device.push_back(d);
                                printf("New triangle prism was created\n");
				break;
				}
                }
		
        	fflush(stdout);
        	buf[0]=0;
        	sendto(cs, "1", 1, 0, (sockaddr *)&remote, remoteLen);
    	}

	char buf_[64];
	float f1, f2, f3, f4;
	f1 = 10; f2 = 20; f3 = 30; f4 = 40;
	sprintf(buf_, "%f %f %f %f %c", f1, f2, f3, f4, '\0');
	printf("We try to send %s\n", buf_);
	sendto(cs, buf_, 10, 0,(sockaddr *)&remote, remoteLen);

    	close(cs);
    	close(h);
}  
