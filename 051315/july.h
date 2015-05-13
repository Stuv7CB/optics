#include <iostream>
#include <vector>
#include "math.h"

using namespace std;

#define PI 3.14159265
#define NUMBER 13            // HERE YOU CAN CHANGE NUMBER OF CREATED RAYS {360 : (NUMBER - 1)}


//3) Опционально параболическое зеркало (XY – координаты; lenght – длина зеркала; f – фокус).
class Parabolic	:	public Device {
public:
    float len, p;
	point *F;
	point *OC;
	Parabolic( float x, float y, float _len, float len_f)
	{       
		OC = new point();		//deg from vertical 0 <= deg <= 90  against hour ;
		F = new point();
		OC->x = x;					//	вершина параболы
		OC->y = y;
		F->x = OC->x - len_f;		//	точка фокуса параболы
		F->y = OC->y;
		p = 2 * len_f;
		len = _len;
        x1 = OC->x - len;
        x2 = OC->x - len;
		y1 = OC->y + sqrt(2 * p * fabs(x1 - OC->x));
        y2 = OC->y - sqrt(2 * p * fabs(x2 - OC->x));
		std::cout << "\nCreate Parabolic x: " << x << " y: " << y << "  len: " << len << " focus: " << len_f << "\n";
		std::cout << "X1:" << x1 << " Y1: " << y1 << " X2: " << x2 << " Y2: " << y2 << "\n";
    }

	point *cross_point(RAY *r) const {					//	точка пересечения параболы и луча
        point *p = new point();

		float xn, yn, k_ray, b_ray;
		float xc, yc;
		float dd, bb;
		point p1, p2;

		if (r->deg < 90 || r->deg > 270) {
			if (r->deg == 0) 
			{
				p1.y = r->y - OC->y;
				p1.x = OC->x - Sqr(p1.y) / (2 * this->p);
			}
			else {
				bb = 2 * this->p / tan(GradToRad(r->deg));
				dd = sqrt( Sqr(bb)  + 8 * this->p * (OC->x - r->x) );
				p1.y = (-bb + dd) / 2;  
				p2.y = (-bb - dd) / 2;
				p1.x = OC->x - Sqr(p1.y) / (2 * this->p); //p1.y / fabs( tan(GradToRad(r->deg))) + r->x;
				p2.x = p1.x;
				p->x = p1.x; 
				p->y = OC->y - p1.y;
			}

/*			if (sin (GradToRad(r->deg)) >= 0) {
				p->x = p1.x; 
				p->y = OC->y - p1.y;
			}
			else { 
				p->x = p1.x; 
				p->y = OC->y + p1.y;
			}*/

			std::cout << "p->x: " << p->x << " p->y: " << p->y << " r->deg: " << r->deg << "\n";
			return p;
		} else {
			;
		}

        return NULL;
    }


    void change_direction(RAY *r, point *p) const			//	Параболическое зеркало
    {
		std::cout << "\nPrev r->deg: " << r->deg << "\n";	//	исходный угол луча
		float a1 = p->x - r->x;
		float b1 = r->y - p->y;
		float a2 = -1;
		float b2 = p->y - OC->y;
		float deg_f = RadToGrad(atan((a1 * b2 - a2 * b1) / (a1 * a2 + b1 * b2)));		//	угол между лучом и нормалью
		std::cout << "Deg ray-normal: " << deg_f << "\n";

		if (r->deg > 180 && r->deg <= 360) {
			r->deg = 360 - r->deg + 2 * fabs(deg_f);
		} 
		if (r->deg >= 0 && r->deg <= 180) {
			r->deg = r->deg + (180 + 2 * fabs(deg_f));
		}
		r->deg = r->Deg360(r->deg);
		std::cout << "New r->deg: " << r->deg << "\n";
    }

    const char *getID() const {
        return "Parabolic";
    }
  
    ~Parabolic()
    {
        cout << "Destructure of the " << this->getID() << "\n";
    }
};

//4) Опционально эллиптическое зеркало (XY – координаты; lenght – длина зеркала; f1, f2 – фокусы).
class Ellipse	:	public Device {
public:
    float len, p, a , b, c;
	float deg1, deg2;
	point *F1, *F2;
	point *OC;
	Ellipse( float x, float y, float _len, float f1_x, float f1_y, float f2_x, float f2_y, float _a)
	{       
		OC = new point();		//deg from vertical 0 <= deg <= 90  against hour ;
		F1 = new point();
		F2 = new point();
		OC->x = x;						//	середина эллипса
		OC->y = y;
		F1->x = f1_x;					//	точка фокуса эллипса
		F1->y = f1_y;
		F2->x = f2_x;					//	точка фокуса эллипса
		F2->y = f2_y;
		len = _len;
		c = LenVect(F1, F2) / 2;
		a = _a;							//	большая полуось
		b = sqrt( Sqr(a) - Sqr(c) );

		y1 = OC->y + len/2;				//	y -> a
        y2 = OC->y - len/2;				//	x -> b
		x1 = b * sqrt(1 - Sqr((y1 - OC->y) /a)) + OC->x;
		x2 = b * sqrt(1 - Sqr((y2 - OC->y) /a)) + OC->x;

		deg1 = RadToGrad(atan((OC->y - y1) / (x1 - OC->x)));
		deg2 = RadToGrad(atan((OC->y - y2) / (x2 - OC->x)));
		std::cout << "\n	Create Ellipse x: " << x << " y: " << y << "  len: " << len << " focus: x1=" << f1_x << " y1=" << f1_y 
			<< " f2_x=" << f1_x << "f2_y=" << f1_x << "\n";
		std::cout << "X1:" << x1 << " Y1: " << y1 << " X2: " << x2 << " Y2: " << y2 << "\n";
    }



	point *cross_point(RAY *r) const {					//	точка пересечения эллипса и луча
        point *p = new point();

		float xn, yn, k_ray, b_ray;
		float xc, yc;
		float dd, bb, aa, cc;
		point p1, p2;
		if (r->deg != 90 && r->deg != 270) { 
			k_ray = -tan(GradToRad(r->deg));					//	уравнение прямой y = k*x + b
			b_ray = r->y - r->x * k_ray;
																//	уравнение эллипса  y2/a2 + x2/b2 = 1
																//	нахождение общих точек
			aa = Sqr(this->a) + Sqr(this->b * k_ray);											
			bb = 2 * k_ray * Sqr(this->b) * (b_ray - OC->y) - 2 * Sqr(this->a) * OC->x; 
			cc = Sqr(this->b * OC->x) + Sqr(this->b * (b_ray - OC->y)) - Sqr(this->a * this->b);

			dd = Sqr(bb)  - 4 * aa * cc;
			if (dd < 0) return NULL;				//	корней нет 
			dd = sqrt(dd);

			p1.x = (-bb + dd) / (2 * aa);			//	корни пересечений
			p2.x = (-bb - dd) / (2 * aa);

			p1.y = k_ray * p1.x + b_ray; 
			p2.y = k_ray * p2.x + b_ray; 
		} else {
													//	вертикальный луч (r->deg = 90, 270)
			if (fabs(r->x - OC->x) > b)		return NULL;	//	не пересекает эллипс
			p1.x = r->x;							
			p2.x = r->x;
			p1.y = OC->y - a * sqrt(1.0 - Sqr((r->x - OC->x) / b));
			p2.y = OC->y + a * sqrt(1.0 - Sqr((r->x - OC->x) / b));
		}

		float delta1 = Sqr((p1.x - OC->x) / this->b) + Sqr((p1.y - OC->y) / this->a) - 1;	//	проверка принадлежности эллипсу delta = 0
		float delta2 = Sqr((p2.x - OC->x) / this->b) + Sqr((p2.y - OC->y) / this->a) - 1;

		//	check p1
		float p1_deg = RadToGrad(atan2((OC->y - p1.y), (p1.x - OC->x)));			//	угол относительно центра
		float p2_deg = RadToGrad(atan2((OC->y - p2.y), (p2.x - OC->x)));
		if (p1_deg >= deg1 && p1_deg <= deg2 /*&& delta1 < 0.1*/) {					//	лежит в сегменте эллипса
			if (r->CheckRayPoint(&p1)) {		//		Проверка луча (точка находится на луче)
				p->x = p1.x; 
				p->y = p1.y;
				std::cout << "Ellips intersection 1\n";
				std::cout << "p->x: " << p->x << " p->y: " << p->y << " r->deg: " << r->deg << "\n";
				return p;
			}
		}
		if (p2_deg >= deg1 && p2_deg <= deg2 /*&& delta2 < 0.1*/) {					//	лежит в сегменте эллипса
			if (r->CheckRayPoint(&p2)) {		//		Проверка луча (точка находится на луче)
				p->x = p2.x; 
				p->y = p2.y;
				std::cout << "Ellips intersection 2\n";
				std::cout << "p->x: " << p->x << " p->y: " << p->y << " r->deg: " << r->deg << "\n";
				return p;
			}
		}

        return NULL;
    }


    void change_direction(RAY *r, point *p) const			//	Эллиптическое зеркало
    {
		std::cout << "\nPrev r->deg: " << r->deg << "\n";	//	исходный угол луча
		float a1 = p->y - r->y;											//	луч				a1 x + b1 y + c = 0
		float b1 = r->x - p->y;
		float a2 = Sqr(b/a) * ((OC->y - p->y) /(p->x - OC->x));			//	нормаль к эллипсу a2 x + b2 y + c = 0
		float b2 = -1;
		//float deg_f = RadToGrad(atan2((a1 * b2 - a2 * b1), (a1 * a2 + b1 * b2)));		//	угол между лучом и нормалью
		float deg_norm = RadToGrad(atan(Sqr(b/a) * ((OC->y - p->y) /(p->x - OC->x))));		//	нормаль
		std::cout << "Deg Normal " << deg_norm << "\n";
		float sign = 1;
		float deg_ray = r->deg;
		if (deg_ray > 180) {					//	ниже гориз оси
			deg_ray = 360 - deg_ray;
			sign = -1;
		}
		float deg_f;
		//if ( (fabs(deg_norm) >= deg_ray ) ) {
			deg_f = fabs(fabs(deg_norm) - deg_ray);		//	угол между лучом и нормалью
		//}

		//float deg_f = deg_ray - fabs(deg_norm);						
		std::cout << "Deg ray-normal: " << deg_f << "\n";
		if (fabs(deg_f) > 90) {
			deg_f = 180 - deg_f;
		}
		r->deg = r->deg - 2 * deg_f * sign + 180 * sign;
		std::cout << "New r->deg: " << r->deg << "\n";
		//if (deg_f < 0)  r->deg = r->deg + 2 * deg_f + 180;
		//if (deg_f >= 0) r->deg = r->deg + 2 * deg_f - 180;

		r->deg = r->Deg360(r->deg);								//	угол луча в [0..360]
		std::cout << "New r->deg: " << r->deg << "\n";
    }

    const char *getID() const {
        return "Ellipse";
    }
  
    ~Ellipse()
    {
        cout << "Destructure of the " << this->getID() << "\n";
    }
};

