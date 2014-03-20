//Shape.cpp - Naman Gupta 2010

#include "../Inc/Shape.h"

Shape::Shape(const POINT u, const POINT v
			 ,const LOGPEN& lp, const LOGBRUSH& lb) // Passing Brush and Pen as reference
{
	mPt0.x = u.x;
	mPt0.y = u.y;
	mPt1.x = u.x;
	mPt1.y = u.y;

	mhPen		 = CreatePenIndirect(&lp);
	mhBrush		 = CreateBrushIndirect(&lb);

	mhOldBrush	 = 0;
	mhOldPen	 = 0;
}

Shape::~Shape(void)
{
	DeleteObject(mhPen);
	DeleteObject(mhBrush);
}


void Shape::setStartPt(const POINT& p0)
{
	mPt0 = p0;
}

void Shape::setEndPt(const POINT& p1)
{
	mPt1 = p1;
}

LineShape::LineShape(const POINT u, const POINT v, 
					 const LOGPEN& lp, const LOGBRUSH& lb)
					 : Shape(u,v,lp,lb)
{}

void LineShape::draw(HDC hdc)
{
	//Select the current pen and brush
	mhOldPen = (HPEN)SelectObject(hdc, mhPen);
	mhOldBrush = (HBRUSH)SelectObject(hdc, mhBrush);

	// Draw the line
	MoveToEx(hdc, mPt0.x, mPt0.y, 0);
	LineTo(hdc,  mPt1.x, mPt1.y);

	//Restore the old pen and brush

	SelectObject(hdc, mhOldBrush);
	SelectObject(hdc, mhOldPen);
}

RectShape::RectShape(const POINT u, const POINT v, 
					 const LOGPEN& lp, const LOGBRUSH& lb)
					 : Shape(u,v,lp,lb)
{}


void RectShape::draw(HDC hdc)
{
	//Select the current pen and brush
	mhOldPen = (HPEN)SelectObject(hdc,mhPen);
	mhOldBrush = (HBRUSH)SelectObject(hdc,mhBrush);

	//Drawing the Rectangle
	Rectangle(hdc, mPt0.x, mPt0.y, mPt1.x, mPt1.y);

	//Restore the Old Pen and Brush
	SelectObject(hdc, mhOldPen);
	SelectObject(hdc, mhOldBrush);
}

EllipseShape::EllipseShape(const POINT u, const POINT v, 
					 const LOGPEN& lp, const LOGBRUSH& lb)
					 : Shape(u,v,lp,lb)
{}


void EllipseShape::draw(HDC hdc)
{
	//Select the current pen and brush
	mhOldPen = (HPEN)SelectObject(hdc,mhPen);
	mhOldBrush = (HBRUSH)SelectObject(hdc,mhBrush);

	//Drawing the Rectangle
	Ellipse(hdc, mPt0.x, mPt0.y, mPt1.x, mPt1.y);

	//Restore the Old Pen and Brush
	SelectObject(hdc, mhOldPen);
	SelectObject(hdc, mhOldBrush);
}