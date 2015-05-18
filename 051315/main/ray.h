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
inline float GradToRad(float deg) { return (float)(deg*PI/180.0);};
inline float RadToGrad(float arg) { return (float)(arg*180.0/PI);};
inline float Sqr(float x) {return x*x;}

int orient_ (float x1, float y1, float x2, float y2, float x3, float y3, float this_deg) {// x1,y1; x2,y2 - line   x3,y3 - point
    // cout << "x1 = " << x1 << " y1 = " << y1 << " x2 = " << x2 << " y2 = " << y2 << " x3 = " << x1 << " y3 = " << y3 << "\n";
    if (this_deg == 0){
        if (y3 <= y2){
            
            // cout << "trying 1 \n";
            return 1;
        }
        else{
            // cout << "trying -1 \n";
            return -1;
        }
    }
    else {
        if (((x3 -x1) * (y2 - y1) - (y3 -y1) * (x2 - x1)) >= 0)
            return 1;
        else
            return -1;
    }
    
}
class RAY                                                                                                                                       //      луч
{
public:
    float x, y;                                                                                                                         //      координаты
    float deg;                                                                                                                          //      угол

public:
    void set_ray_pos (float x_0, float y_0, float deg_0)                                        //      установка параметров x,y,deg
    { x = x_0; y = y_0; deg = deg_0;}

        bool CheckRayPoint(point *pp) const
        {
                //              Проверка луча (точка не на отрицательном продолжении луча за источником)
                float r_deg_delta = RadToGrad(atan2((this->y - pp->y), (pp->x - this->x)));
                r_deg_delta = Deg360(r_deg_delta);
                float r_deg = this->deg;
                if (r_deg == 360) r_deg = 0;
                if (fabs(r_deg - r_deg_delta) < 1) return true;
                return false;
        }

        void show_ray_pos(int i)
    { cout << "Ray(" << i << "):" << " x = " << x << " y = " << y << " deg = " << deg << "\n";}

        float Deg360(float deg1) const
        {                                       //      угол в диапазоне [0..360]
                do {
                        if (deg1 < 0)           deg1    += 360;
                        if (deg1 >360)          deg1    -= 360;
                }
                while (deg1 < 0 || deg1 > 360);
                return deg1;
        }

    ~RAY ()
    {
        cout << "Destructure of the ray (" << deg << ") x: " << x << " y: " << y <<"\n";
    }
};


class SCREEN
{
    public :
    float x1, x2, y1, y2,deg;
public:
    SCREEN (float x, float y, float l_0, float deg_0) {
        x1 = x - (float)(l_0/2) * sin (deg_0 * PI / 180);
        x2 = x + (float)(l_0/2) * sin (deg_0 * PI / 180);
        y1 = y - (float)(l_0/2) * cos (deg_0 * PI / 180);
        y2 = y + (float)(l_0/2) * cos (deg_0 * PI / 180);
        deg = deg_0;
    }
    void screen_pos()
    { cout << " x1 = " << x1 << " y1 = " << y1  << " x2 = " << x2 << " y2 = " << y2  <<"\n";}
    
    point * cross_point (RAY * r)  {
        point * p = new point  ();
        if ((orient_ (this->x1,this->y1,this->x2,this->y2,r->x,r->y,1) < 0) && ((r->deg <= 90) || (r->deg >= 270))){
            float det = this->y2 - this->y1 - tan (r->deg * PI / 180) * (this->x1 - this->x2);
            float det_1 = this->y2 * this->x1 - this->y1 * this->x2 - (this->x1 - this->x2) * (r->y + tan (r->deg * PI / 180) * r->x);
            float det_2 = (this->y2 - this->y1) * (r->y + tan (r->deg * PI / 180) * r->x) - (this->y2 * this->x1 - this->y1 * this->x2) * tan (r->deg * PI / 180);
            p->x = (float)det_1/det;
            p->y = (float)det_2/det;
            if (( p->x >= x1 ) && ( p->x <= x2 ) && ( p->y >= y1 ) && ( p->y <= y2 ))
                return p;
        }
        if ((orient_ (this->x1,this->y1,this->x2,this->y2,r->x,r->y,1) > 0) && ((r->deg >= 90) && (r->deg <= 270))) {
            float det = this->y2 - this->y1 - tan (r->deg * PI / 180) * (this->x1 - this->x2);
            float det_1 = this->y2 * this->x1 - this->y1 * this->x2 - (this->x1 - this->x2) * (r->y + tan (r->deg * PI / 180) * r->x);
            float det_2 = (this->y2 - this->y1) * (r->y + tan (r->deg * PI / 180) * r->x) - (this->y2 * this->x1 - this->y1 * this->x2) * tan (r->deg * PI / 180);
            p->x = (float)det_1/det;
            cout << "p->x = " << p->x << "\n" ;
            p->y = (float)det_2/det;
            cout << "p->x = " << p->x << "\n" ;
            if (( p->x >= x1 ) && ( p->x <= x2 ) && ( p->y >= y1 ) && ( p->y <= y2 ))
                return p;
        }        return NULL;
    }
    
    ~SCREEN ()
    {
        cout << "Destructure of the screen" << "\n";
    }
};

class SOURCE
{
public:
    float x, y;

public:
    SOURCE (float x_0, float y_0) :
    x(x_0), y(y_0)
    { }
    void source_pos()
    { cout << " x = " << x << " y = " << y  << "\n";}
    RAY** rays_create ()
    {   const int num_of_rays = NUMBER;
        float deg_step = (float)360 / (num_of_rays - 1);
        RAY ** ray = new RAY *[num_of_rays];
        float deg_i = 0;
        for (int i = 0; i < num_of_rays; i++) {
            ray[i]=new RAY();
            ray[i]->set_ray_pos (x, y, deg_i);
            ray[i]->show_ray_pos(i);
            deg_i = deg_i + deg_step;
        }
        return ray;
    }
    ~SOURCE ()
    {
        cout << "Destructure of the source" << "\n";
    }
};
class LASER
{
private:
    float x, y, deg;

public:
    LASER (float x_0, float y_0, float deg_0) :
    x(x_0), y(y_0), deg (deg_0)
    { }
    void laser_pos()
    { cout << " x = " << x << " y = " << y  << "\n";}
    RAY * rays_create ()
    {
        RAY * ray = new RAY ();
        ray->set_ray_pos (x, y, deg);
        ray->show_ray_pos(0);
        return ray;
    }
    ~LASER ()
    {
        cout << "Destructure of the source" << "\n";
    }
};

