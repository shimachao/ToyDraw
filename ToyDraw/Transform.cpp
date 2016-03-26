#include "stdafx.h"
#include "ToySG.h"
#define _USE_MATH_DEFINES
#include <math.h>
//using namespace ToySG;
namespace ToySG{

void Move(POINT points[],int num,int dx,int dy)
{
	for (int i = 0; i < num; i++)
	{
		points[i].x += dx;
		points[i].y += dy;
	}
}

void Move(Point points[],int num,int dx,int dy)
{
	for (int i = 0; i < num; i++)
	{
		points[i].X += dx;
		points[i].Y += dy;
	}
}

void Move(POINT &point,int dx,int dy)
{
	point.x += dx;
	point.y += dy;
}

//缩放一个点
void Scale(POINT &org,POINT &p,float f)
{
	p.x = f*p.x + org.x*(1-f);
	p.y = f*p.y + org.y*(1-f);
}

//缩放一系列点
void Scale(POINT &org,POINT points[],int num,float f)
{
	int xtem = org.x*(1-f);
	int ytem = org.y*(1-f);

	 for (int i = 0; i < num; i++)
	 {
		 points[i].x = f*points[i].x + xtem;
		 points[i].y = f*points[i].y + ytem;
	 }
}

void Scale(POINT &org,Point points[],int num,float f)
{
	int xtem = org.x*(1-f);
	int ytem = org.y*(1-f);

	for (int i = 0; i < num; i++)
	{
		points[i].X = f*points[i].X + xtem;
		points[i].Y = f*points[i].Y + ytem;
	}
}

void Rotate(POINT origin,POINT points[],int num,Direction direction,int degree)
{
	long double rad = degree/360*2*M_PI;
	long double r11 = cos(rad);
	long double r12 = -sin(rad);
	long double r21 = -r12;
	long double r22 = r11;
	LONG dx = origin.x*(1-r11) + origin.y*r21;
	LONG dy = origin.y*(1-r11) - origin.x*r21;

	for (int i = 0; i < num; i++)
	{
		int temx = points[i].x;
		points[i].x = temx*r11 + points[i].y*r12 + dx;
		points[i].y = temx*r12 + points[i].y*r22 +dy;
	}
}

void Rotate(POINT origin,Point points[],int num,Direction direction,int degree)
{
	long double rad = degree/360*2*M_PI;
	long double r11 = cos(rad);
	long double r12 = -sin(rad);
	long double r21 = -r12;
	long double r22 = r11;
	LONG dx = origin.x*(1-r11) + origin.y*r21;
	LONG dy = origin.y*(1-r11) - origin.x*r21;

	for (int i = 0; i < num; i++)
	{
		int temx = points[i].X;
		points[i].X = temx*r11 + points[i].Y*r12 + dx;
		points[i].Y = temx*r12 + points[i].Y*r22 +dy;
	}
}

void Rotate(POINT origin,POINT &point,Direction direction,int degree)
{
	long double rad = degree/360*2*M_PI;
	long double r11 = cos(rad);
	long double r12 = -sin(rad);
	long double r21 = -r12;
	long double r22 = r11;
	LONG dx = origin.x*(1-r11) + origin.y*r21;
	LONG dy = origin.y*(1-r11) - origin.x*r21;

	int temx = point.x;
	point.x = temx*r11 + point.y*r12 + dx;
	point.y = temx*r12 + point.y*r22 +dy;
}


void Mirror(POINT points[],int num,Coordinate coordinate,int c)
{
	if (coordinate == X)
	{//关于x=c对称
		for (int i = 0; i < num; i++)
		{
			points[i].x = 2*c - points[i].x;
		}
	}
	else if (coordinate == Y)
	{
		for (int i = 0; i < num; i++)
		{
			points[i].y = 2*c - points[i].y;
		}
	}
}

void Mirror(POINT &point,Coordinate coordinate,int c)
{
	if (coordinate == X)
	{//关于x=c对称
		point.x = 2*c - point.x;
	}
	else if (coordinate == Y)
	{
		point.y = 2*c - point.y;
	}
}

void Mirror(Point points[],int num,Coordinate coordinate,int c)
{
	if (coordinate == X)
	{//关于x=c对称
		for (int i = 0; i < num; i++)
		{
			points[i].X = 2*c - points[i].X;
		}
	}
	else if (coordinate == Y)
	{
		for (int i = 0; i < num; i++)
		{
			points[i].Y = 2*c - points[i].Y;
		}
	}
}

}
