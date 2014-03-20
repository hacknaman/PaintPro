// Shape.h - Naman Gupta 2010

#pragma once
#include <Windows.h>

class Shape
{
public:
	Shape(const POINT u, const POINT v,
		const LOGPEN& lp, const LOGBRUSH& lb); // Passing Brush and Pen as Reference

	virtual~Shape(); // I Do know why Distructor is Virtual

	void setStartPt(const POINT& p0); // setting the start Point
	void setEndPt(const POINT& p1); // setting the end Point

	virtual void draw(HDC hdc) = 0;

protected:
	POINT mPt0;
	POINT mPt1;
	HPEN mhPen;
	HBRUSH mhBrush;

	HPEN mhOldPen;
	HBRUSH mhOldBrush;

public:
//	~Shape(void);
};

class LineShape : public Shape
{
public:
	LineShape(const POINT u, const POINT v,
		const LOGPEN& lp, const LOGBRUSH& lb);
	void draw(HDC hdc);
};


class RectShape : public Shape
{
public:
	RectShape(const POINT u, const POINT v,
		const LOGPEN& lp, const LOGBRUSH& lb);
	void draw(HDC hdc);
};


class EllipseShape : public Shape
{
public:
	EllipseShape(const POINT u, const POINT v,
		const LOGPEN& lp, const LOGBRUSH& lb);
	void draw(HDC hdc);
};
