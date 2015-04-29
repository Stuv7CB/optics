#include <iostream>
#include <vector>
#include "math.h"

using namespace std;

#define PI 3.14159265
#define NUMBER 20            // HERE YOU CAN CHANGE NUMBER OF CREATED RAYS {360 : (NUMBBER - 1)}


struct point  {
    float x ;
    float y ;
};

class RAY
{
public:
    float x, y;
    float deg;
    
public:
    void set_ray_pos (float x_0, float y_0, float deg_0)
    { x = x_0; y = y_0; deg = deg_0;}
    void show_ray_pos(int i)
    { cout <<i << ":" <<" x = " << x << " y = " << y << " deg = " << deg << "\n";}
    ~RAY ()
    {
        cout << "Destructure of the ray" << "\n";
    }
};


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
    
public:
    Lens( float x, float y, float l, float deg_0, float f_0){       //deg from vertical 0 <= deg <= 90  against hour ;
        x1 = x - (float)(l/2) * sin (deg_0 * PI / 180) ;
        x2 = x + (float)(l/2) * sin (deg_0 * PI / 180);
        y1 = y - (float)(l/2) * cos (deg_0 * PI / 180);
        y2 = y + (float)(l/2) * cos (deg_0 * PI / 180);
        f = f_0;
        deg = deg_0;
    }
    point * cross_point (RAY * r) const {
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

    void change_direction(RAY * r, point * p ) const
    {
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
  
    ~Lens ()
    {
        cout << "Destructure of the Lens" << "\n";
    }
    
    
};

class SCREEN
{
public :
    float x1, x2, y1, y2;
public:
    SCREEN (float x1_0, float y1_0, float x2_0, float y2_0 ) : x1 (x1_0), y1 (y1_0), x2 (x2_0), y2 (y2_0)
    { }
    void screen_pos()
    { cout << " x1 = " << x1 << " y1 = " << y1  << " x2 = " << x2 << " y2 = " << y2  <<"\n";}
    
    point * cross_point (RAY * r)  {
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
    
    ~SCREEN ()
    {
        cout << "Destructure of the screen" << "\n";
    }
};

class SOURCE
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
};




