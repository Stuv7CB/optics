#include "device.h"
//#include "ray.h"
#include <stdio.h>
using namespace std;
int main(){
//	Lens *a;
	Device *a;
	a = new Lens(1,1,1);
	a -> info();
	Ray *r;
	a -> change_direction(*r);
//	a.info();
	r -> show_ray_pos(2);
	printf("I am good\n");
	return 0;
}
