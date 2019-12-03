#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>
#include "Math.h"

class Camera2D
{
protected:
	double X0, Y0;						// Экранные координаты начала мировой системы координат
	double px, py;                      // Единицы масштаба мировой системы координат, выраженные в пикселях
	double Rad=200;                       
	int W, H;							// Разрешение рабочей области окна
	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return px*X+X0;
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return Y0+py*Y;
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		return (X-X0)/px;
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		return (Y-Y0)/py;
	}
	double L()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return -X0/px;
	}
	double R()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return (W-X0)/px;
	}
	double T()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return -Y0 / py;
	}
	double B()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return (H - Y0) / py;
	}
	
private:
	double posX, posY;	
	bool isDragging;
	int xDrag, yDrag;
				// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
public:
	Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py), H(0), W(0),posX(0),posY(0),isDragging(false)
	{
	}

	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc),&r);
		Rectangle(dc, 0, 0, r.right, r.bottom);

		// Очистка рабочей области окна
	}
	void SetResolution(HDC dc)
	{
		// Данная процедура вызывается при изменении размеров окна
		// В ней задаются значения величин W, H, а также настраиваются значения параметров X0, Y0, px, py таким образом, чтобы обеспечить одинаковые масштабы по координатным осям

		RECT r;
		GetClientRect(WindowFromDC(dc),&r);
		W = r.right + 1;
		H = r.bottom + 1;
	}
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
		// Перемещение графического курсора (posX, posY)
		// Обратите внимание, что мы действуем в мировых координатах
	}
	void LineTo(HDC dc, double X, double Y)
	{
		// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
		// Обратите внимание, что мы действуем в мировых координатах
		// При отрисовке линии могут быть использованы WinApi функции
		// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)

		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X,Y);

	}
	
	void Axes(HDC dc)
	{
		// Отрисовка координатных осей
		MoveTo(R(),0);
		LineTo(dc, L(), 0);
		MoveTo(0, B());
		LineTo(dc, 0, T());
	}
	void Resize(int res) {
		int newSize = res * 5;
		double new_px = px + px / py * newSize;
		double new_py = py + py / px * newSize;
		if (new_px > 10) px = new_px;
		if (new_py > 10) py = new_py;
	}
	/*void MoveCamera(int X, int Y) // Перемещает камеру по пикселям
	{
		this->px += ScreenX;
		this->px += Y;
	}
	void MoveCameraTo(int X, int Y)
	{
		this->px = X;
		this->px = Y;

	}*/
	void StartDraggingCamera(int X, int Y)
	{
		this->isDragging = true;
		this->xDrag = X;
		this->yDrag = Y;
	}
	void DragCamera(int X, int Y)
	{
		X0 += (X - xDrag);
		Y0 += (Y - yDrag);
		xDrag = X0;
		yDrag = Y0;
	}
	void StopDraggingCamera()
	{
		isDragging = false;
	}
	bool IsDraggingCamera()
	{
		return isDragging;
	}
	
};


#endif CAMERA_2D_H
