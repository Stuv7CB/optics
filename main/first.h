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
	if (d.size()==0){
		return ret;
	}
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
int first_s(vector <SCREEN *> d, RAY *r){
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
