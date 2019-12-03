#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>
#include "Math.h"

class Camera2D
{
protected:
	double X0, Y0;						// �������� ���������� ������ ������� ������� ���������
	double px, py;                      // ������� �������� ������� ������� ���������, ���������� � ��������
	double Rad=200;                       
	int W, H;							// ���������� ������� ������� ����
	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return px*X+X0;
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return Y0+py*Y;
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return (X-X0)/px;
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return (Y-Y0)/py;
	}
	double L()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return -X0/px;
	}
	double R()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	{
		return (W-X0)/px;
	}
	double T()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return -Y0 / py;
	}
	double B()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	{
		return (H - Y0) / py;
	}
	
private:
	double posX, posY;	
	bool isDragging;
	int xDrag, yDrag;
				// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
public:
	Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py), H(0), W(0),posX(0),posY(0),isDragging(false)
	{
	}

	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc),&r);
		Rectangle(dc, 0, 0, r.right, r.bottom);

		// ������� ������� ������� ����
	}
	void SetResolution(HDC dc)
	{
		// ������ ��������� ���������� ��� ��������� �������� ����
		// � ��� �������� �������� ������� W, H, � ����� ������������� �������� ���������� X0, Y0, px, py ����� �������, ����� ���������� ���������� �������� �� ������������ ����

		RECT r;
		GetClientRect(WindowFromDC(dc),&r);
		W = r.right + 1;
		H = r.bottom + 1;
	}
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
		// ����������� ������������ ������� (posX, posY)
		// �������� ��������, ��� �� ��������� � ������� �����������
	}
	void LineTo(HDC dc, double X, double Y)
	{
		// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
		// �������� ��������, ��� �� ��������� � ������� �����������
		// ��� ��������� ����� ����� ���� ������������ WinApi �������
		// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)

		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X,Y);

	}
	
	void Axes(HDC dc)
	{
		// ��������� ������������ ����
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
	/*void MoveCamera(int X, int Y) // ���������� ������ �� ��������
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
