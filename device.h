#include <stdio.h>
#include "ray.h"
using namespace std;
class Device{
public:
        double x1, x2, y1, y2;
	virtual void info() const = 0;
	virtual void change_direction(Ray r) const = 0;
};
class Lens : public Device{
public:
        void info() const{
                printf("GOOD\n");
        }
        void change_direction(Ray r) const{
                r.set_ray_pos(1,1,0);
                printf("direction changed\n");
        }
        const char *getID() const{
                return "Lens";
        }
        Lens(double x, double y, double l){
                x1 = x - l/2;
                x2 = x + l/2;
                y1 = y - l/2;
                y2 = y + l/2;
        }
};

