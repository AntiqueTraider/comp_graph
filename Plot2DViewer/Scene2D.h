#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
	
public:
	Scene2D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{
	}
	void Plot(HDC dc, Func f, bool axes=true)
	{
		if (axes)
			Axes(dc);

		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
		double h =1/px;
		MoveTo(L(),f(L()));
		for (double i = L(); i < R(); i = i + h) {
			LineTo(dc, i, f(i));
		}

	}
	void ParametricPlot(HDC dc, Func funcX,Func funcY, bool axes = true) {
		if (axes)
			Axes(dc);

		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
		double h = 0.001;
		MoveTo(0,0);
		for (double i = 0; i < 2* M_PI; i = i + h) {
			LineTo(dc, CircleX(i), CircleY(i));
		}
	    LineTo( dc, CircleX(2 * M_PI), CircleY(2 * M_PI));
	}
	void NetPlot(HDC dc ){
		double h = 0.001;
		for (double m = 1; m < 5; m += 0.5) {
			MoveTo(ChangeX(0, m), ChangeY(0, m));
			for (double v = 0; v < 2 * M_PI; v += 0.001)
			{
				LineTo(dc, ChangeX(v, m), ChangeY(v, m));
			}
			LineTo(dc, ChangeX(0, m), ChangeY(0, m));
		}
	}
};

#endif SCENE_2D_H
