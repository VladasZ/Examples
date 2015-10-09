#include <windows.h>
#include "resource.h"
#include <math.h>
#include <memory>
#include <list>



using namespace std;


HINSTANCE hInst;
HWND shooter;
HWND handle;
TCHAR text[50];

class Info {
	HWND hWnd;
	HWND infoItem;
	HWND hRect, hPosCaption, hLeftValue, hRightValue, hTopValue, hBotValue;
	HWND hMoveButton;
	int xPos;
	int yPos;
	int length;
	int width;
	RECT wRect;

	POINT position;

public:
	//Info();
	//Info(/*HWND hWnd,*/ HWND infoItem, int xPos, int yPos) : /*hWnd(hWnd),*/ infoItem(infoItem), xPos(xPos), yPos(yPos) {

	//	GetWindowRect(infoItem, &wRect);

	//	Rect = CreateWindowEx(0, TEXT("STATIC"), 0, WS_BORDER, xPos, yPos, 100, 100, 0, 0, hInst, 0);


	//}

	Info& setInfoAbout(HWND hWnd, HWND infoItem) {
		this->hWnd = hWnd;
		this->infoItem = infoItem;


		return *this;
	}

	Info& inPos(int x, int y) {
		this->xPos = x;
		this->yPos = y;

		hRect = CreateWindowEx(0, TEXT("STATIC"), 0, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE, xPos, yPos, 200, 200, hWnd, 0, hInst, 0);
		hBotValue = CreateWindowEx(0, TEXT("STATIC"), TEXT("BOT INFO"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_CLIENTEDGE, xPos + 84, yPos + 190, 30, 20, hWnd, 0, hInst, 0);
		hRightValue = CreateWindowEx(0, TEXT("STATIC"), TEXT("RIGHT INFO"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_CLIENTEDGE, xPos + 150, yPos + 90, 100, 20, hWnd, 0, hInst, 0);
		hPosCaption = CreateWindowEx(0, TEXT("STATIC"), TEXT("X - XXX, Y - YYY"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_CLIENTEDGE, xPos + 35, yPos + 90, 120, 20, hWnd, 0, hInst, 0);




		return *this;
	}

	Info& show() {

		GetWindowRect(infoItem, &wRect);

		length = wRect.right - wRect.left;
		width = wRect.bottom - wRect.top;

		position.y = wRect.top;
		position.x = wRect.left;

		ScreenToClient(hWnd, &position);

		wsprintf(text, TEXT("X-%d, Y-%d"), position.x, position.y);
		SetWindowText(hPosCaption, text);



		wsprintf(text, TEXT("%d"), length);
		SetWindowText(hBotValue, text);
		wsprintf(text, TEXT("%d"), width);
		SetWindowText(hRightValue, text);

		return *this;
	}

	Info& destroy() {
		DestroyWindow(hRect);
		DestroyWindow(hBotValue);
		DestroyWindow(hRightValue);
		DestroyWindow(hPosCaption);
		return *this;
	}

};

class Bullet;



class Bullet {
	double x, y;
	int xSide, ySide;
	double plusX, plusY;
	static const int xSize = 14, ySize = 14;
	HWND handle;


public:
	Bullet() {};

	Bullet(int x, int y, int xTarget, int yTarget, HWND hWnd) : x(x), y(y){
		xSide = xTarget - x;
		ySide = yTarget - y;

		double hypotenuse = sqrt(xSide*xSide + ySide*ySide);

		double coefficient = 100 / hypotenuse;

		plusX = xSide * coefficient / 100;
		plusY = ySide * coefficient / 100;


		handle = CreateWindowEx(0, TEXT("BUTTON"), TEXT("*"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_CLIENTEDGE, this->x, this->y, xSize, ySize, hWnd, 0, hInst, 0);



	}


	void move() {


		if (x < 0) plusX *= -1;
		if (y < 0) plusY *= -1;

		if (x > 500) plusX *= -1;
		if (y > 500) plusY *= -1;


		x += plusX;
		y += plusY;

		MoveWindow(handle, x, y, xSize, ySize, 1);
	}

	Bullet& coordinates(int x, int y) {
		this->x = x; this->y = y;
		return *this;
	}

	Bullet& targetCoordinates(int xTarget, int yTarget) {
		xSide = xTarget - x;
		ySide = yTarget - y;

		double hypotenuse = sqrt(xSide*xSide + ySide*ySide);

		double coefficient = 100 / hypotenuse;

		plusX = xSide * coefficient / 100;
		plusY = ySide * coefficient / 100;

		return *this;
	}

	Bullet& parentHandle(HWND hWnd) {
		this->handle = hWnd;
		handle = CreateWindowEx(0, TEXT("BUTTON"), TEXT("*"), WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_CLIENTEDGE, this->x, this->y, xSide, ySide, hWnd, 0, hInst, 0);
		return *this;
	}

};


class Gun {
public:
	list<shared_ptr<Bullet>> bullets;

	void shoot(int x, int y, int xTarget, int yTarget, HWND hWnd) {
		bullets.push_back(make_shared<Bullet>(x, y, xTarget, yTarget, hWnd));
	}


	void move() {
		for (auto a : bullets) {
			a->move();
		}
	}

}gun;



BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;


	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}





Info shooterInfo;



BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;



	case WM_INITDIALOG:

		shooter = GetDlgItem(hWnd, SHOOTER);

		if (GetDlgItem(hWnd, SHOOTER)) SetWindowText(hWnd, TEXT("daaa...."));

		/*shooterInfo.setInfoAbout(hWnd, shooter)
			.inPos(150, 150)
			.show();*/

	//	gun.shoot(100, 100, 851, 462, hWnd);


		MoveWindow(hWnd, 0, 0, 530, 550, 1);
		SetTimer(hWnd, 1, 1, 0);

		return TRUE;


	case WM_MOUSEMOVE:

		//wsprintf(text, TEXT("X - %d, Y - %d"), LOWORD(lParam), HIWORD(lParam));
		//SetWindowText(hWnd, text);

		//shooterInfo.show();
	//	gun.move();




		return TRUE;

	case WM_TIMER:	
		gun.move();

		return TRUE;

	case WM_LBUTTONUP:
		gun.shoot(250, 250, LOWORD(lParam), HIWORD(lParam), hWnd);

			return TRUE;

	case WM_COMMAND:

		handle = GetFocus();
		GetWindowText(handle, text, 20);

		if (!lstrcmp(text, TEXT("MOVE")) ){
			shooterInfo.destroy().inPos(LOWORD(lParam), HIWORD(lParam));

			SetWindowText(hWnd, text);
		}

		return TRUE;

	}





	return FALSE;
}


