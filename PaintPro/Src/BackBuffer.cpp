// BackBuffer.cpp -- Naman Gupta 2010

#include "../Inc/BackBuffer.h"

BackBuffer::BackBuffer(HWND hWnd, int width, int height)
{
	// Save a copy of the main window handle.
	mhWnd = hWnd;

	// Get a handle to the device context associated with
	// the window.
	HDC hWndDC = GetDC(hWnd);

	// Save the backbuffer dimensions.
	mWidth  = width;
	mHeight = height;

	// Create system memory device context that is compatible 
	// with the window one.
	mhDC = CreateCompatibleDC(hWndDC);

	// Create the backbuffer surface bitmap that is compatible
	// with the window device context bitmap format.  That is
	// the surface we will render onto.
	mhSurface = CreateCompatibleBitmap(
		hWndDC, width, height);

	// Done with window DC.
	ReleaseDC(hWnd, hWndDC);

	// At this point, the back buffer surface is uninitialized,
	// so lets clear it to some non-zero value.  Note that it
	// needs to be non-zero.  If it is zero then it will mess
	// up our sprite blending logic.  

	// Select the backbuffer bitmap into the DC.
	mhOldObject = (HBITMAP)SelectObject(mhDC, mhSurface);

	// Select a white brush.
	HBRUSH white    = (HBRUSH)GetStockObject(WHITE_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mhDC, white);

	// Clear the backbuffer rectangle.
	Rectangle(mhDC, 0, 0, mWidth, mHeight);

	// Restore the original brush.
	SelectObject(mhDC, oldBrush);
}

BackBuffer::~BackBuffer()
{
	SelectObject(mhDC, mhOldObject);
	DeleteObject(mhSurface);
	DeleteDC(mhDC);
}

HDC BackBuffer::getDC()
{
	return mhDC;
}

int BackBuffer::width()
{
	return mWidth;
}

int BackBuffer::height()
{
	return mHeight;
}

void BackBuffer::present()
{
	// Get a handle to the device context associated with
	// the window.
	HDC hWndDC = GetDC(mhWnd);

	// Copy the backbuffer contents over to the 
	// window client area.
	BitBlt(hWndDC, 0, 0, mWidth, mHeight, 
			mhDC, 0, 0, SRCCOPY);

	// Always free window DC when done.
	ReleaseDC(mhWnd, hWndDC);
}

