#include <iostream>
using namespace std;
class Ray{
private:
    int x, y;
    float deg;
public:
    void set_ray_pos (int x_0, int y_0, float deg_0)
    { x = x_0; y = y_0; deg = deg_0;}
    void show_ray_pos(int i)
    { cout <<i << ":" <<" x = " << x << " y = " << y << " deg = " << deg << "\n";}
};

