#include <stdio.h>
#include "./device.h"
#include "math.h"

int min_(vector <float> a){
	int ret = -1;
	float min = 100000;
	for (int i = 0; i < a.size(); i++){
		if (a[i] < min){
			min = a[i];
			ret = i;
		}
	}
	return ret;
}
float rast_(point *a, point *b){
	float ret;
	ret = sqrt((((a->x)-(b->x))*((a->x)-(a->x)))+(((a->y)-(b->y))*((a->y)-(b->y))));
	return ret;
}
void print_(vector <Device *> my_device){
        for (int i = 0; i < my_device.size(); i++){
                printf("%d\n", i);
        }
	printf("\n");
}
point *point_(RAY *r){
	point *ret;
	ret -> x = r -> x;
	ret -> y = r -> y;
	return ret;
}
void first_(RAY *r, vector <Device *> d){
	point *q = point_(r);
	vector <point *> points_;
	point *qwer;
//	for (int i = 0; i < 3; i++){
//		p = d[0]->cross_point(r);
//		if (p!=NULL){
//			points.push_back(p);
//		}
//		else{
			qwer->x = 100;
//			qwer->y = 100000;
//			points_.push_back(q);
//		}
//	}
/*	vector <float> rasts;
	float rast;
	for (int i = 0; i < points.size(); i++){
		rast = rast_(q, points[i]);
		rasts.push_back(rast);
	}
//	int ret = min_(rasts);
*/
}
int main(){
        vector <Device *> my_device;
        Device *d1 = new Lens(30, 10, 10, 5, 0);
        Device *d2 = new Lens(20, 10, 10, 10, 0);
        Device *d3 = new Lens(50, 10, 10, 20, 0);
        my_device.push_back(d1);
        my_device.push_back(d2);
        my_device.push_back(d3);
	RAY *r = new RAY();
	r->set_ray_pos(5, 5, 5);
	point *q = point_(r);
	printf("%f %f\n", q->x, q->y);
	vector <point *> points;
	for (int i = 0; i < 3; i++){
	q->x = 10000;
	q->y = 10000;
	points.push_back(q);
//	printf("%f %f\n", points[i]->x, points[i]->y);
	}
	first_(r, my_device);
	return 0;
}
