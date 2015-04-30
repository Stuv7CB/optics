#include <iostream>
#include <vector>
#include "math.h"
#include <stdio.h>
#include "ray.h"

using namespace std;

#define PI 3.14159265
#define NUMBER 10            // HERE YOU CAN CHANGE NUMBER OF CREATED RAYS {360 : (NUMBBER - 1)}

class Device{
public:
    	float x1, x2, y1, y2, deg, f ;      // y1 - up y2 - down x1 - left x2 - right
    	virtual void change_direction(RAY * r, point * p) const = 0;
    	virtual const char *getID() const = 0;
    	virtual point * cross_point (RAY * r) const = 0;
};

class Lens : public Device{
public:
    	float deg, f;
    	Lens( float x, float y, float l, float deg_0, float f_0){       //deg from vertical 0 <= deg <= 90  against hour ;
        	x1 = x - (float)(l/2) * sin (deg_0 * PI / 180) ;
        	x2 = x + (float)(l/2) * sin (deg_0 * PI / 180);
        	y1 = y - (float)(l/2) * cos (deg_0 * PI / 180);
        	y2 = y + (float)(l/2) * cos (deg_0 * PI / 180);
        	f = f_0;
        	deg = deg_0;
    	}
    	point * cross_point (RAY *r) const {
        	point * p = new point  ();
        	if ((( this->x1 + this->x2 )/2 > r->x) && ((r->deg <= 90) || (r->deg >= 270))){
            		float det = this->y2 - this->y1 - tan (r->deg * PI / 180) * (this->x1 - this->x2);
            		float det_1 = this->y2 * this->x1 - this->y1 * this->x2 - (this->x1 - this->x2) * (r->y + tan (r->deg * PI / 180) * r->x);
            		float det_2 = (this->y2 - this->y1) * (r->y + tan (r->deg * PI / 180) * r->x) - (this->y2 * this->x1 - this->y1 * this->x2) * tan (r->deg * PI / 180);
            		p->x = (float)det_1/det;
            		p->y = (float)det_2/det;
            		if (( p->x >= x1 ) && ( p->x <= x2 ) && ( p->y >= y1 ) && ( p->y <= y2 ))
                		return p;
        	}
        	if ((( this->x1 + this->x2 )/2 < r->x) && ((r->deg >= 90) || (r->deg <= 270))) {
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

    void change_direction(RAY * r, point * p ) const{
        // пока луч от 0 до 180 град точка пересечения выше опт оси
        float l_1 = 0;
        float alpha = 0;
        float l = (float) sqrt ((r->x - (this->x1 + this->x2)/2) * (r->x - (this->x1 + this->x2)/2)+ (r->y - (this->y1 + this->y2)/2) * (r->y - (this->y1 + this->y2)/2)) ;
        //cout << " l = " << l << "\n";
        float line_tg = fabs ((float)((r->y - (this->y1 + this->y2)/2) / ((this->x1 + this->x2)/2 - r->x))) ;
        //cout << " line_tg = " << line_tg;
        float a = l * cos (atan (line_tg));
        //cout << " a = " << a << "\n";
        
        if (a != this->f){
            if (a > this->f) {
                float b = (float) (this->f * a / (a - this->f));
                //cout << " b = " << b << "\n";
                float c =  sqrt ((p->x - (this->x1 + this->x2)/2) * (p->x - (this->x1 + this->x2)/2)+ (p->y - (this->y1 + this->y2)/2) * (p->y - (this->y1 + this->y2)/2)) ;
                if (((r->y <= ((this->y1 + this->y2)/2)) && (p->y <=  ((this->y1 + this->y2)/2))) || ((r->y >= ((this->y1 + this->y2)/2)) && (p->y >=  ((this->y1 + this->y2)/2)))) {
                    l_1 = c + (float) b * line_tg;
                    alpha = atan ((float) (l_1 / b)) * 180 / PI;
                    if ((r->y <= ((this->y1 + this->y2)/2)) && (p->y <=  ((this->y1 + this->y2)/2)))
                        alpha = 360 - alpha;
                }
                else {
                    l_1 = fabs (c - (float) b * line_tg);
                    alpha = atan ((float) (l_1 / b)) * 180 / PI;
                    if ((r->y <= ((this->y1 + this->y2)/2)) && (p->y <=  ((this->y1 + this->y2)/2 + (float) b * line_tg )))
                        alpha = 360 - alpha;
                    if ((r->y >= ((this->y1 + this->y2)/2)) && (p->y <=  ((this->y1 + this->y2)/2 - (float) b * line_tg )))
                        alpha = 360 - alpha;
                }
                r->deg = alpha ;
            }
            else {
                float b = fabs((float) (this->f * a / (a - this->f)));
                //cout << " b = " << b << "\n";
                float c =  sqrt ((p->x - (this->x1 + this->x2)/2) * (p->x - (this->x1 + this->x2)/2)+ (p->y - (this->y1 + this->y2)/2) * (p->y - (this->y1 + this->y2)/2)) ;
                if (((r->y <= ((this->y1 + this->y2)/2)) && (p->y >=  ((this->y1 + this->y2)/2))) || ((r->y >= ((this->y1 + this->y2)/2)) && (p->y <=  ((this->y1 + this->y2)/2)))) {
                    l_1 = c + (float) b * line_tg;
                    alpha = atan ((float) (l_1 / b)) * 180 / PI;
                    if ((r->y <= ((this->y1 + this->y2)/2)) && (p->y >=  ((this->y1 + this->y2)/2)))
                        alpha = 360 - alpha;
                }
                else {
                    l_1 = fabs (c - (float) b * line_tg);
                    alpha = atan ((float) (l_1 / b)) * 180 / PI;
                    if ((r->y <= ((this->y1 + this->y2)/2)) && (p->y <=  ((this->y1 + this->y2)/2 - (float) b * line_tg )))
                        alpha = 360 - alpha;
                    if ((r->y >= ((this->y1 + this->y2)/2)) && (p->y >=  ((this->y1 + this->y2)/2 + (float) b * line_tg )))
                        alpha = 360 - alpha;
                }
                r->deg = alpha ;
            }
        }
        else {
            alpha = atan (line_tg) * 180 / PI;
            if ((r->y < ((this->y1 + this->y2)/2)))
                alpha = 360 - alpha;
            r->deg = alpha;
        }
        //cout << "r->deg = " << r->deg << "\n";
    }
    const char *getID() const{
        return "Lens";
    }
  
    ~Lens (){
        cout << "Destructure of the Lens" << "\n";
    }
};

