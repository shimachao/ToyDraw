/*
图元的定义，类或结构体
*/
#pragma once
#include <WinDef.h>
#include "tinyxml.h"

namespace ToySG
{
	////直线
	//struct Line{
	//	POINT	start;
	//	POINT	end;
	//};
	////长方形和正方形
	//struct Rectangle{
	//	POINT	top_left;
	//	POINT	bottom_right;
	//};
	////椭圆和圆
	//struct Ellipse{
	//	POINT	top_left;
	//	POINT	bottom_right;
	//};
	////多边形
	//struct Polygon{
	//	int	num;
	//	POINT*	pPointArray;
	//};
	////贝塞尔曲线
	//struct BezierCurve{
	//	POINT	first_end;
	//	POINT	second_end;
	//	POINT	first_control;
	//	POINT	second_control;
	//};

	enum Direction{Left,Right,Up,Down};	//方向
	enum Coordinate{X,Y};//坐标轴
	class CGraph:public CObject{
	public:
		CGraph();
		virtual void Move(int dx,int dy)=0;			//移动
		virtual	void Rotate(POINT,Direction,int degree)=0;//旋转
		virtual void Mirror(Coordinate,int c)=0;	//对称变换
		virtual void Scale(float f)=0;	//缩放
		virtual	void Draw(Graphics *pGraphics)=0;	//绘制自己
		virtual void DrawHit(Graphics *pGraphics)=0;//绘制自己选中的状态
		virtual bool IsHit(POINT)=0;				//是否选中
		virtual void Save(TiXmlElement *pParent)=0;
		

		void SetLineType(Gdiplus::DashStyle);		//设置线型
		void SetLineWidth(int);						//设置线宽
		void SetLineColor(COLORREF);				//设置颜色
		void SetAttributes(TiXmlElement *pEliment);	//设置各种属性，包括上面的颜色、线宽、线型
		

		Gdiplus::DashStyle GetLineType();
		int GetLineWidth();
		COLORREF GetLineColor();

	protected:
		Gdiplus::DashStyle	m_LineType;	//线型
		int			m_LineWidth;//线宽
		COLORREF	m_LineColor;//颜色

		bool		m_IsSelected;//是否被选中
		//工具函数,保存到svg文件时设置线型
		void SetDashGap(TiXmlElement *pNode);
	};

	class CLine :public CGraph{
	public:
		CLine(POINT start,POINT end);
		CLine(TiXmlElement*pElement);

		void Move(int dx,int dy);
		void Rotate(POINT,Direction,int degree);
		void Scale(float f);	//缩放
		void Mirror(Coordinate,int c);
		void Draw(Graphics *pGraphics);
		void DrawHit(Graphics *pGraphics);
		bool IsHit(POINT);
		void Save(TiXmlElement *pParent);
	private:
		POINT	m_start;
		POINT	m_end;
	};

	class CRectangle:public CGraph{
	public:
		CRectangle(POINT top_left,POINT bottom_right);
		CRectangle(TiXmlElement*pElement);

		void Move(int dx,int dy);
		void Rotate(POINT,Direction,int degree);
		void Scale(float f);	//缩放
		void Mirror(Coordinate,int c);
		void Draw(Graphics *pGraphics);
		void DrawHit(Graphics *pGraphics);
		bool IsHit(POINT);
		void Save(TiXmlElement *pParent);
	private:
		POINT	m_top_left;
		POINT	m_bottom_right;
	};

	class CEllipse:public CGraph{
	public:
		CEllipse(POINT top_left,POINT bottom_right);
		CEllipse(TiXmlElement*pElement);

		void Move(int dx,int dy);
		void Rotate(POINT,Direction,int degree);
		void Scale(float f);	//缩放
		void Mirror(Coordinate,int c);
		void Draw(Graphics *pGraphics);
		void DrawHit(Graphics *pGraphics);
		bool IsHit(POINT);
		void Save(TiXmlElement *pParent);
	private:
		POINT	m_top_left;
		POINT	m_bottom_right;
	};

	class CPolygon:public CGraph{
	public:
		CPolygon(int num=0,Point* pPointArray=NULL);
		CPolygon(TiXmlElement*pElement);
		~CPolygon();

		void Move(int dx,int dy);
		void Rotate(POINT,Direction,int degree);
		void Scale(float f);	//缩放
		void Mirror(Coordinate,int c);
		void Draw(Graphics *pGraphics);
		void DrawHit(Graphics *pGraphics);
		bool IsHit(POINT);
		void Save(TiXmlElement *pParent);
	private:
		int		m_num;
		Gdiplus::Point*	m_pPointArray;
	};

	class CBezierCurve:public CGraph{
	public:
		CBezierCurve(POINT	first_end,
							POINT	second_end,
							POINT	first_control,
							POINT	second_control);
		CBezierCurve(TiXmlElement*pElement);

		void Move(int dx,int dy);
		void Rotate(POINT,Direction,int degree);
		void Scale(float f);	//缩放
		void Mirror(Coordinate,int c);
		void Draw(Graphics *pGraphics);
		void DrawHit(Graphics *pGraphics);
		bool IsHit(POINT);
		void Save(TiXmlElement *pParent);
	private:
		POINT	m_first_end;
		POINT	m_second_end;
		POINT	m_first_control;
		POINT	m_second_control;
	};
}

//文件中的图元类型标志
typedef char SGType;
const char LINE = 1;
const char RECTANGLE = 2;
const char ELLIPSE = 3;
const char POLYGON = 4;
const char BEZIER = 5;
