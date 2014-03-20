//main.cpp - Naman Gupta 2010 // main code for paint program

#include <Windows.h>
#include <string>
#include <vector>
#include "../Inc/Shape.h"
#include "../Inc/BackBuffer.h"
#include "../Inc/resource.h"

using namespace std;

// The Globals
BackBuffer* gBackBuffer = 0; 

const COLORREF BLACK = RGB(0, 0, 0);
const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF RED   = RGB(255, 0, 0);
const COLORREF GREEN = RGB(0, 255, 0);
const COLORREF YELLOW= RGB(255, 255, 224);
const COLORREF BLUE  = RGB(0, 0, 255);

HWND		ghMainWnd = 0;
HINSTANCE	ghAppInst = 0;
HMENU		ghMenu = 0;

vector <Shape*> gShapes;

Shape* gCube[2+4];

Shape* gShape = 0;

bool gMouseDown = false;

POINT temp1,temp2;
// Current status of the BRush and the pen (Style color and shape)

int gCurrPrimSel		= ID_PRIMITIVE_LINE;
int gCurrPenColSel		= ID_PENCOLOR_BLACK;
int gCurrBrushColSel	= ID_BRUSHCOLOR_BLACK;
int gCurrPenStyleSel	= ID_PENSTYLE_SOLID;
int gCurrBrushStyleSel  = ID_BRUSHSTYLE_SOLID;

LOGPEN gLogPen;
LOGBRUSH gLogBrush;
LOGBRUSH gBrcube;



BOOL CALLBACK
AboutDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	

	switch( msg )
	{
		// so we just return true.
	case WM_INITDIALOG:
		return true;
		// We learned in the last chapter that a WM_COMMAND
		// message is sent when the user selects a menu item
		// from the menu. In addition to that, a WM_COMMAND
		// message is also sent when the user presses a
		// button control.
	case WM_COMMAND:
		// The low 16-bits of the wParam stores the resource
		// ID of the button control the user pressed. So from
		// that information, we can determine which button was
		// pressed.
		switch(LOWORD(wParam))
		{
			// Did the user press the OK button (resource ID = IDOK)?
			// If so, close the dialog box.
		case IDOK:
			EndDialog(
				hDlg, // Handle to dialog to end.
				0); // Return code--generally always zero.
			return true;
		}
		break;
	}
	return false;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Object for the painting

	


	gBrcube.lbColor = WHITE;
	gBrcube.lbStyle = BS_NULL;

	//HDC hdc;  // handle for device context
	 // paint stuff

	POINT p0;
	POINT p1;

	switch(msg)
	{
	case WM_CREATE:
		CheckMenuItem(ghMenu,gCurrPrimSel,MF_CHECKED);
		CheckMenuItem(ghMenu,gCurrPenColSel,MF_CHECKED);
		CheckMenuItem(ghMenu,gCurrPenStyleSel,MF_CHECKED);
		CheckMenuItem(ghMenu,gCurrBrushColSel,MF_CHECKED);
		CheckMenuItem(ghMenu,gCurrBrushStyleSel,MF_CHECKED);

		gBackBuffer = new BackBuffer(
			hWnd,
			640,
			480);

				

		return 0;

	case WM_COMMAND:
	
		switch(LOWORD(wParam))
		{
			//FILE menu
		case ID_FILE_EXIT:
			DestroyWindow(ghMainWnd);
			return 0;
			// Primitive Shapes
		case ID_PRIMITIVE_LINE:
			CheckMenuItem(ghMenu,gCurrPrimSel, MF_UNCHECKED);
			gCurrPrimSel = ID_PRIMITIVE_LINE;
			CheckMenuItem(ghMenu,gCurrPrimSel, MF_CHECKED);
			return 0;
		case ID_PRIMITIVE_RECTANGLE:
			CheckMenuItem(ghMenu,gCurrPrimSel, MF_UNCHECKED);
			gCurrPrimSel = ID_PRIMITIVE_RECTANGLE;
			CheckMenuItem(ghMenu,gCurrPrimSel, MF_CHECKED);
			return 0;
		case ID_PRIMITIVE_ELLIPSE:
			CheckMenuItem(ghMenu,gCurrPrimSel, MF_UNCHECKED);
			gCurrPrimSel = ID_PRIMITIVE_ELLIPSE;
			CheckMenuItem(ghMenu,gCurrPrimSel, MF_CHECKED);
			return 0;
		case ID_PRIMITIVE_CUBE:
			CheckMenuItem(ghMenu,gCurrPrimSel, MF_UNCHECKED);
			gCurrPrimSel = ID_PRIMITIVE_CUBE;
			CheckMenuItem(ghMenu,gCurrPrimSel, MF_CHECKED);
			return 0;
		// Pen colors

		case ID_PENCOLOR_BLACK:
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_UNCHECKED);
			gCurrPenColSel = ID_PENCOLOR_BLACK;
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_CHECKED);
			gLogPen.lopnColor = BLACK;
			return 0;
		case ID_PENCOLOR_WHITE:
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_UNCHECKED);
			gCurrPenColSel = ID_PENCOLOR_WHITE;
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_CHECKED);
			gLogPen.lopnColor = WHITE;
			return 0;
		case ID_PENCOLOR_RED:
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_UNCHECKED);
			gCurrPenColSel = ID_PENCOLOR_RED;
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_CHECKED);
			gLogPen.lopnColor = RED;
			return 0;
		case ID_PENCOLOR_GREEN:
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_UNCHECKED);
			gCurrPenColSel = ID_PENCOLOR_GREEN;
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_CHECKED);
			gLogPen.lopnColor = GREEN;
			return 0;
		case ID_PENCOLOR_BLUE:
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_UNCHECKED);
			gCurrPenColSel = ID_PENCOLOR_BLUE;
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_CHECKED);
			gLogPen.lopnColor = BLUE;
			return 0;
		case ID_PENCOLOR_YELLOW:
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_UNCHECKED);
			gCurrPenColSel = ID_PENCOLOR_YELLOW;
			CheckMenuItem(ghMenu, gCurrPenColSel, MF_CHECKED);
			gLogPen.lopnColor = YELLOW;
			return 0;
			// BRUSH COLOR
		case ID_BRUSHCOLOR_BLACK:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_BRUSHCOLOR_BLACK;
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_CHECKED);
			gLogBrush.lbColor = BLACK;
			return 0;
		case ID_BRUSHCOLOR_WHITE:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_BRUSHCOLOR_WHITE;
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gLogBrush.lbColor = WHITE;
			return 0;
		case ID_BRUSHCOLOR_RED:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_BRUSHCOLOR_RED;
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gLogBrush.lbColor = RED;
			return 0;
		case ID_BRUSHCOLOR_GREEN:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_BRUSHCOLOR_GREEN;
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gLogBrush.lbColor = GREEN;
			return 0;
		case ID_BRUSHCOLOR_BLUE:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_BRUSHCOLOR_BLUE;
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gLogBrush.lbColor = BLUE;
			return 0;
		case ID_BRUSHCOLOR_YELLOW:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_BRUSHCOLOR_YELLOW;
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gLogBrush.lbColor = YELLOW;
			return 0;
		// Pen Styles
		case ID_PENSTYLE_SOLID:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_PENSTYLE_SOLID;
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_CHECKED);
			gLogPen.lopnStyle = PS_SOLID;
			return 0;
		case ID_PENSTYLE_DOTTED:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_PENSTYLE_DOTTED;
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_CHECKED);
			gLogPen.lopnStyle = PS_DOT;
			return 0;
		case ID_PENSTYLE_DASHED:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_PENSTYLE_DASHED;
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_CHECKED);
			gLogPen.lopnStyle = PS_DASH;
			return 0;
		// Brush Styles
		case ID_BRUSHSTYLE_SOLID:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_BRUSHSTYLE_SOLID;
			CheckMenuItem(ghMenu,gCurrBrushColSel, MF_CHECKED);
			gLogBrush.lbStyle = BS_SOLID;
			return 0;
		case ID_BRUSHSTYLE_NULL:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_BRUSHSTYLE_NULL;
			CheckMenuItem(ghMenu,gCurrBrushColSel, MF_CHECKED);
			gLogBrush.lbStyle = BS_NULL;
			return 0;
		case ID_BRUSHSTYLE_DIAGONAL:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_BRUSHSTYLE_DIAGONAL;
			CheckMenuItem(ghMenu,gCurrBrushColSel, MF_CHECKED);
			gLogBrush.lbStyle = BS_HATCHED;
			gLogBrush.lbHatch = HS_BDIAGONAL;
			return 0;
		case ID_BRUSHSTYLE_CROSS:
			CheckMenuItem(ghMenu, gCurrBrushColSel, MF_UNCHECKED);
			gCurrBrushColSel = ID_BRUSHSTYLE_CROSS;
			CheckMenuItem(ghMenu,gCurrBrushColSel, MF_CHECKED);
			gLogBrush.lbStyle = BS_HATCHED;
			gLogBrush.lbHatch = HS_CROSS;
			return 0;
			}
	case WM_LBUTTONDOWN:

		SetCapture(hWnd); // Capture the mouse even after the mouse cursor moves off the screen
		gMouseDown = true;

		temp1.x = p0.x = LOWORD(lParam);
		temp1.y = p0.y = HIWORD(lParam);

		temp2.x = temp1.x + 50;
		temp2.y = temp1.y + 50;

		p1.x = 0;
		p1.y = 0;

		switch( gCurrPrimSel )
		{
		case ID_PRIMITIVE_LINE:
			gShape = new LineShape(p0, p1, gLogPen, gLogBrush);
			break;
		case ID_PRIMITIVE_RECTANGLE:
			gShape = new RectShape(p0, p1, gLogPen, gLogBrush);
			break;
		case ID_PRIMITIVE_ELLIPSE:
			gShape = new EllipseShape(p0, p1, gLogPen, gLogBrush);
			break;
		case ID_PRIMITIVE_CUBE:
			POINT c0,c1;
			c0.x = p0.x + 50;
			c0.y = p0.y + 50;
			c1.x = p1.x + 50;
			c1.y = p1.y + 50;
			gCube[0] = new RectShape(p0, p1, gLogPen, gBrcube);
			gCube[1] = new RectShape(c0, c1, gLogPen, gBrcube);
			gCube[2] = new LineShape(p0, c0, gLogPen, gLogBrush);
			gCube[5] = new LineShape(p1, c1, gLogPen, gLogBrush);
			c0.x = p1.x;
			c0.y = p0.y;
			c1.x = c0.x+50;
			c1.y = c0.y+50;
			gCube[3] = new LineShape(c0, c1, gLogPen, gLogBrush);
			c0.x = p0.x;
			c0.y = p1.y;
			c1.x = c0.x+50;
			c1.y = c0.y+50;
			gCube[4] = new LineShape(c0, c1, gLogPen, gLogBrush);
			break;
		};
//InvalidateRect(hWnd, 0, true);
		return 0;

	case WM_MOUSEMOVE:
		if( gMouseDown )
		{
			// Current mouse position is stored in the lParam 
			p1.x = LOWORD(lParam);
			p1.y = HIWORD(lParam);
				
			POINT c,t;
			if (gCurrPrimSel == ID_PRIMITIVE_CUBE)
			{
				gCube[0]->setEndPt(p1);
				c.x = p1.x + 50;
				c.y = p1.y + 50;
				gCube[1]->setEndPt(c);
				gCube[2]->setStartPt(temp1);
				gCube[2]->setEndPt(temp2);

				gCube[5]->setStartPt(p1);
				gCube[5]->setEndPt(c);
				t.x = p1.x;
				t.y = temp1.y;
				gCube[3]->setStartPt(t);
				t.x += 50;
				t.y += 50; 
				gCube[3]->setEndPt(t);
				t.x = temp1.x;
				t.y = p1.y;
				gCube[4]->setStartPt(t);
				t.x += 50;
				t.y += 50;
				gCube[4]->setEndPt(t);
			}
			else
				gShape->setEndPt(p1);


			InvalidateRect(hWnd, 0, true);
		}
//InvalidateRect(hWnd, 0, true);
		return 0;
	case WM_LBUTTONUP:
			//Release the captured mouse when the left mouse
			// is shifted.
			ReleaseCapture();
			gMouseDown = false;

			//Current mouse position is stored in the lParam
			p1.x = LOWORD(lParam);
			p1.y = HIWORD(lParam);

			// Update the end point
			POINT c,t;
			if (gCurrPrimSel == ID_PRIMITIVE_CUBE)
			{
				gCube[0]->setEndPt(p1);
				c.x = p1.x + 50;
				c.y = p1.y + 50;
				gCube[1]->setEndPt(c);
				gCube[2]->setStartPt(temp1);
				gCube[2]->setEndPt(temp2);

				gCube[5]->setStartPt(p1);
				gCube[5]->setEndPt(c);
				t.x = p1.x;
				t.y = temp1.y;
				gCube[3]->setStartPt(t);
				t.x += 50;
				t.y += 50; 
				gCube[3]->setEndPt(t);
				t.x = temp1.x;
				t.y = p1.y;
				gCube[4]->setStartPt(t);
				t.x += 50;
				t.y += 50;
				gCube[4]->setEndPt(t);
				gShapes.push_back(gCube[0]);
				gShapes.push_back(gCube[1]);
				gShapes.push_back(gCube[2]);
				gShapes.push_back(gCube[3]);
				gShapes.push_back(gCube[4]);
				gShapes.push_back(gCube[5]);

			}
			else
			{
				gShape->setEndPt(p1);
				gShapes.push_back( gShape );
			}
			InvalidateRect(hWnd, 0, true);

			return 0;

	
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
	
			HDC bbDC = gBackBuffer->getDC();
	
			bbDC = BeginPaint(hWnd, &ps);
			
	
			// Draw the permanent stuff
			for (unsigned int  i = 0; i < gShapes.size() ; ++i)
				gShapes[i]->draw(bbDC);

	
			if ( gMouseDown )
				if (gCurrPrimSel == ID_PRIMITIVE_CUBE)
				{
					gCube[0]->draw(bbDC);
					gCube[1]->draw(bbDC);
					gCube[2]->draw(bbDC);
					gCube[3]->draw(bbDC);
					gCube[4]->draw(bbDC);
					gCube[5]->draw(bbDC);
				}
				else
					gShape->draw(bbDC);
	
	
			EndPaint (hWnd, &ps);
			Sleep(50);
			InvalidateRect(hWnd, 0, true);		
		
		}
		// handle key down message
		//return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE )
			DestroyWindow(ghMainWnd);
		else if (wParam == 'Z')
		{
			if (gShapes.size())
			gShapes.pop_back();

		//	InvalidateRect(hWnd, 0, true);
		}

		else if (wParam == 'A')
		{
			DialogBox(
				ghAppInst, // Application instance.
				MAKEINTRESOURCE(IDD_DIALOG1), // Dialog resource ID.
				hWnd, // Parent window of dialog box.
				AboutDlgProc); // Ptr to dialog box window procedure.
			return 0;
		}

		else if (wParam == 'Q')
		{
			MessageBox(0 , L"HELLO, THERE- THIS IS MADE BY NAMAN GUPTA.",L"HELLO", MB_OK);
			return 0;
		}

		return 0;

	case WM_DESTROY:
		delete gBackBuffer;
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Main for the program		

INT WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int showCmd)
{
	ghAppInst = hInstance;

	WNDCLASS wc;
	wc.style		= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc  = WndProc;
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= ghAppInst;
	wc.hIcon		= ::LoadIcon(0,IDI_APPLICATION);
	wc.hCursor		= ::LoadCursor(0, IDC_ARROW);
	wc.hbrBackground=(HBRUSH)::GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName= L"MyWndClassName";

	RegisterClass( &wc );

	ghMenu = LoadMenu(ghAppInst, MAKEINTRESOURCE(IDR_MENU1));
	ghMainWnd = ::CreateWindow(L"MyWndClassName", L"Naman's Photoshop Program",
		WS_OVERLAPPEDWINDOW, 200, 200, 640, 480, 0, ghMenu, ghAppInst, 0);

	if (ghMainWnd == 0)
	{
		::MessageBox(0, L"CreateWindow - Failed",0 , 0);
		return false;
	}

	ShowWindow(ghMainWnd, showCmd);
	UpdateWindow(ghMainWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while(msg.message != WM_QUIT)
	{
		// IF there is a Windows message then process it.
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		//	InvalidateRect(ghMainWnd, 0, true);
		}
		else
		{
			
			gBackBuffer->present();
			//Sleep(20000000);
			
		}

	}

	for (unsigned int  i = 0; i < gShapes.size(); i++)
		delete gShapes[i];

return (int)msg.wParam;
}

	
