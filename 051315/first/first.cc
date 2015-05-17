#include <stdio.h>
#include "device.h"
#include <math.h>


float min_(float x1, float x2){
	if (x1 < x2)
		return x1;
	else return x2;
}
void print_(vector <Device *> my_device){
        for (int i = 0; i < my_device.size(); i++){
                printf("%d:%f\n", i,min_(my_device[i]->x1, my_device[i]->x2));
        }
	printf("\n");
}
float sqr_(float x){
	return x*x;
}

int first(vector <Device *> d, RAY *r){
	int ret = -1;
	float x = r->x;
	float y = r->y;
	float rast;
	float min = 100000;
	for (int i = 0; i < d.size(); i++){
		point *cross = NULL;
		cross = d[i] -> cross_point(r);
		if (cross != NULL){
			float xp = cross -> x;
			float yp = cross -> y;
			rast = sqrt(sqr_(x - xp)+sqr_(y - yp));
		}
		else{
			rast = 1000000;
		}
		if (rast < min){
			min = rast;
			ret = i;	
		}
	}
	return ret;
}

int main(){
        vector <Device *> my_device;
        Device *d1 = new Lens(30, 0, 10, 5, 0);
        Device *d2 = new Lens(10, 0, 10, 10, 0);
        Device *d3 = new Lens(50, 0, 10, 20, 0);
        my_device.push_back(d1);
        my_device.push_back(d2);
        my_device.push_back(d3);
	RAY *r = new RAY();
	r->set_ray_pos(40, 0, 10);
	int q = first(my_device, r);
	printf("%d\n", q);
//	sort_(my_device);
	return 0;
}
