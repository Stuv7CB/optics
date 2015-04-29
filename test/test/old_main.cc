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
	const int PORT = 5678;
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
//	SOURCE *my_source;
	SCREEN *my_screen;
	Laser *my_laser;
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
                        	float a1, x, y;
                        	sscanf(buf,"%f %f %f",&a1, &x, &y);
  //                      	my_source = new SOURCE(x, y);
//                      	= new SOURCE(x, y);
				printf("Source was created\n");
                        	break;
                        	}
                	case 1: //screen
                        	{
                        	float a1, x1, y1, x2, y2;
                        	sscanf(buf, "%f %f %f %f %f", &a1, &x1, &y1, &x2, &y2);
                        	my_screen = new SCREEN (x1,y1, x2,y2);
//				=new screen(x1, y1, x2, y2);
				printf("Screen was created\n");
                        	break;
                        	}
                	case 2: //lens f>0
                        	{
                        	float a1, x, y, l, deg, f;
                        	sscanf(buf, "%f %f %f %f %f %f",&a1,&x, &y, &l, &deg, &f);
//                      	printf("%d %d %d %d %d %d\n", a1, a2,a3,a4,a5,a6);
                        	Device  *d = new Lens(x, y, l, deg, f);
                        	my_device.push_back(d);
				printf("New lens was created\n");
                        	break;
                        	}
			case 3:
				break;
			case 4:
				break;
			case 8:
				break;
			case 6:
				break;
			case 7:
				break;
			case 5: //Laser
				{
				float a1, x, y, deg;
				sscanf(buf, "%f %f %f %f", &a1,&x, &y, &deg);
				my_laser = new Laser(x, y, deg);
				break;
				}
        	}
//		sleep(1);
//		int wr = write(qw, "1", 1);
		close(connect_socket);
  	}
//	printf("%f %f \n",my_device[0]->x1, my_device[0]->y1);
//	sleep(3);

//	main part begins
//сортировка девайсов по x
	point *cross = NULL;	
        cross = my_screen->cross_point ( my_laser -> ray );

//first: пробегаем весь отсортированный массив девайсов. Первое пересечение -> break. Пусть пересекло первым второй девайс
//Тогда запускаем новый пробег for 3 to n. И так далее пока не дошли до конца. Если мы успешно прошли весь цикл или сделали брейк на энтом, то
//Запускаем проверку для выходного луча. Пересечет ли он экран? Если да, то в какой точке????. 
//После нахождения каждой из точек отправляем Лене запись. write(wr, "точка1, точка 2", 3).



        if ( cross != NULL ) {
		printf("ray crossed screen at the point x = %f, y = %f\n", cross->x, cross->y);
                for (int i = 0; i < my_device.size(); i++){
                        cross = my_device[i]->cross_point ( my_laser -> ray );
                        if ( cross != NULL ) {
				printf("ray crossed device #%d in point x = %f, y = %f\n", i, cross->x, cross->y);
//                                cout << "prev r->deg = " <<  my_laser->ray->deg << "\n" << "device_number =" << i << "\n";
                                my_device[i]->change_direction(  my_laser->ray,  cross);
//                                cout << " new r->deg = " << my_laser->ray->deg << " \n";
                                my_laser->ray->x = cross->x;
                                my_laser->ray->y = cross->y;
				int wr = write(qw, "2", 1);
                        }
                }
                if (cross == NULL){
                        cout << "ray did not cross devices "<< "\n";
                }
                cross = my_screen->cross_point(my_laser -> ray);
                if (cross !=NULL){
                        printf("ray crossed screen at point x = %f, y = %f\n", cross->x, cross->y);
                }
        }
	else{
		printf("ray didn't cross screen without devices\n");
      		for (int i = 0; i < my_device.size(); i++){
                 	cross = my_device[i]->cross_point ( my_laser -> ray );
                     	if ( cross != NULL ) {
                      		cout << "prev r->deg = " <<  my_laser->ray->deg << "\n" << "device_number =" << i << "\n";
                      		my_device[i]->change_direction(  my_laser->ray,  cross);
                     		cout << " new r->deg = " << my_laser->ray->deg << " \n";
                  		my_laser->ray->x = cross->x;
                       		my_laser->ray->y = cross->y;
                       	}
                }
		if (cross == NULL){
			cout << "ray did not cross devices "<< "\n";
		}				
		cross = my_screen->cross_point(my_laser -> ray);
		if (cross !=NULL){
			printf("ray crossed screen at point x = %f, y = %f\n", cross->x, cross->y);
		}
		else printf("This ray doesn't cross any object. We can avoid it.");
	}

//
	
	int wr = write(qw, "3", 1);//means everything is OK and program can be finished
	close(qw);
	close(h);
	return 0;
}
  
