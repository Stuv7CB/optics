#include <iostream>
#include <vector>
#include "math.h"
#include <stdio.h>

using namespace std;

#define PI 3.14159265
#define NUMBER 10            // HERE YOU CAN CHANGE NUMBER OF CREATED RAYS {360 : (NUMBBER - 1)}


struct point  {
    float x ;
    float y ;
};

class RAY{
public:
    	float x, y;
    	float deg;
	void set_ray_pos(float x_0, float y_0, float deg_0){
		x = x_0;
		y = y_0;
		deg = deg_0;
	}
	void show_ray_pos(int i){
		printf("%d: x = %f, y = %f, deg = %f\n", i, x, y, deg);
	}
	RAY(float x_0, float y_0, float deg_0){
		x = x_0;
		y = y_0;
		deg = deg_0;
	}
    	~RAY (){
		printf("Ray was destructed\n");
    	}
};

class SCREEN
{
public :
    	float x1, x2, y1, y2;
    	SCREEN (float x1_0, float y1_0, float x2_0, float y2_0 ) : x1 (x1_0), y1 (y1_0), x2 (x2_0), y2 (y2_0)
    	{ }
    	void screen_pos(){ 
		cout << " x1 = " << x1 << " y1 = " << y1  << " x2 = " << x2 << " y2 = " << y2  <<"\n";
	}
    
    	point * cross_point (RAY * r){
        	point * p = new point  ();
        	if ((( this->x1 + this->x2 )/2 > r->x) && ((r->deg <= 90) || (r->deg >= 270))) {
            		float det = this->y2 - this->y1 - tan (r->deg * PI / 180) * (this->x1 - this->x2);
            		float det_1 = this->y2 * this->x1 - this->y1 * this->x2 - (this->x1 - this->x2) * (r->y + tan (r->deg * PI / 180) * r->x);
            		float det_2 = (this->y2 - this->y1) * (r->y + tan (r->deg * PI / 180) * r->x) - (this->y2 * this->x1 - this->y1 * this->x2) * tan (r->deg * PI / 180);
            		p->x = (float)det_1/det;
            		p->y = (float)det_2/det;
            		if (( p->x >= x1 ) && ( p->x <= x2 ) && ( p->y >= y1 ) && ( p->y <= y2 ))
                		return p;
        	}
        	if ((( this->x1 + this->x2 )/2 > r->x) && ((r->deg <= 90) || (r->deg >= 270))) {
            		float det = this->y2 - this->y1 - tan (r->deg * PI / 180) * (this->x1 - this->x2);
            		float det_1 = this->y2 * this->x1 - this->y1 * this->x2 - (this->x1 - this->x2) * (r->y + tan (r->deg * PI / 180) * r->x);
            		float det_2 = (this->y2 - this->y1) * (r->y + tan (r->deg * PI / 180) * r->x) - (this->y2 * this->x1 - this->y1 * this->x2) * tan (r->deg * PI / 180);
            		p->x = (float)det_1/det;
           	 	p->y = (float)det_2/det;
            		if (( p->x >= x1 ) && ( p->x <= x2 ) && ( p->y >= y1 ) && ( p->y <= y2 ))
                		return p;
            	}
        
        	return NULL;
    	}
    
    	~SCREEN (){
        	cout << "Destructure of the screen" << "\n";
    	}
};

/*class SOURCE
{
private:
    float x, y;
    
public:
    SOURCE (float x_0, float y_0) :
    x(x_0), y(y_0)
    { }
    void source_pos()
    { cout << " x = " << x << " y = " << y  << "\n";}
    RAY * rays_create ()
    {   const int num_of_rays = NUMBER;
        float deg_step = (float)360 / (num_of_rays - 1);
        RAY * ray = new RAY [num_of_rays];
        float deg_i = 0;
        for (int i = 0; i < num_of_rays; i++) {
            ray[i].set_ray_pos (x, y, deg_i);
            ray[i].show_ray_pos(i);
            deg_i = deg_i + deg_step;
        }
        return ray;
    }
    ~SOURCE ()
    {
        cout << "Destructure of the source" << "\n";
    }
};*/
class Laser{
public:
	RAY *ray;
	Laser(float x, float y, float deg){
		ray = new RAY(x, y, deg);
	}
	~Laser(){
		printf("Laser destructed\n");
	}
};
