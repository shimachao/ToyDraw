/*
ͼԪ�Ķ��壬���ṹ��
*/
#pragma once
#include <WinDef.h>
#include "tinyxml.h"

namespace ToySG
{
	////ֱ��
	//struct Line{
	//	POINT	start;
	//	POINT	end;
	//};
	////�����κ�������
	//struct Rectangle{
	//	POINT	top_left;
	//	POINT	bottom_right;
	//};
	////��Բ��Բ
	//struct Ellipse{
	//	POINT	top_left;
	//	POINT	bottom_right;
	//};
	////�����
	//struct Polygon{
	//	int	num;
	//	POINT*	pPointArray;
	//};
	////����������
	//struct BezierCurve{
	//	POINT	first_end;
	//	POINT	second_end;
	//	POINT	first_control;
	//	POINT	second_control;
	//};

	enum Direction{Left,Right,Up,Down};	//����
	enum Coordinate{X,Y};//������
	class CGraph:public CObject{
	public:
		CGraph();
		virtual void Move(int dx,int dy)=0;			//�ƶ�
		virtual	void Rotate(POINT,Direction,int degree)=0;//��ת
		virtual void Mirror(Coordinate,int c)=0;	//�ԳƱ任
		virtual void Scale(float f)=0;	//����
		virtual	void Draw(Graphics *pGraphics)=0;	//�����Լ�
		virtual void DrawHit(Graphics *pGraphics)=0;//�����Լ�ѡ�е�״̬
		virtual bool IsHit(POINT)=0;				//�Ƿ�ѡ��
		virtual void Save(TiXmlElement *pParent)=0;
		

		void SetLineType(Gdiplus::DashStyle);		//��������
		void SetLineWidth(int);						//�����߿�
		void SetLineColor(COLORREF);				//������ɫ
		void SetAttributes(TiXmlElement *pEliment);	//���ø������ԣ������������ɫ���߿�����
		

		Gdiplus::DashStyle GetLineType();
		int GetLineWidth();
		COLORREF GetLineColor();

	protected:
		Gdiplus::DashStyle	m_LineType;	//����
		int			m_LineWidth;//�߿�
		COLORREF	m_LineColor;//��ɫ

		bool		m_IsSelected;//�Ƿ�ѡ��
		//���ߺ���,���浽svg�ļ�ʱ��������
		void SetDashGap(TiXmlElement *pNode);
	};

	class CLine :public CGraph{
	public:
		CLine(POINT start,POINT end);
		CLine(TiXmlElement*pElement);

		void Move(int dx,int dy);
		void Rotate(POINT,Direction,int degree);
		void Scale(float f);	//����
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
		void Scale(float f);	//����
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
		void Scale(float f);	//����
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
		void Scale(float f);	//����
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
		void Scale(float f);	//����
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

//�ļ��е�ͼԪ���ͱ�־
typedef char SGType;
const char LINE = 1;
const char RECTANGLE = 2;
const char ELLIPSE = 3;
const char POLYGON = 4;
const char BEZIER = 5;
