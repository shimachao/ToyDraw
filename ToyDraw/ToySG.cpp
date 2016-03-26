#include "stdafx.h"
#include "ToySG.h"
#include "Transform.h"
#include <string>
using std::string;
using namespace ToySG;


//本文件专用函数

CGraph::CGraph():m_IsSelected(false),m_LineWidth(1)
{}

COLORREF CGraph::GetLineColor()
{
	return m_LineColor;
}

Gdiplus::DashStyle CGraph::GetLineType()
{
	return m_LineType;
}

int CGraph::GetLineWidth()
{
	return m_LineWidth;
}

void CGraph::SetLineColor(COLORREF color)
{
	m_LineColor = color;
}

void CGraph::SetLineType(Gdiplus::DashStyle lineType)
{
	m_LineType = lineType;
}

void CGraph::SetLineWidth(int width)
{
	m_LineWidth = width;
}

void CGraph::SetAttributes(TiXmlElement *pEliment)
{
	//设置颜色
	string strcolor = pEliment->Attribute("stroke");
	int r,g,b,width;
	sscanf(strcolor.c_str(),"rgb(%d,%d,%d)",&r,&g,&b);
	m_LineColor = RGB(r,g,b);
	//设置线宽
	pEliment->Attribute("stroke-width",&width);
	m_LineWidth = width;
	//设置线型
	const char *cstrdashStyle = pEliment->Attribute("stroke-dasharray");
	string dashStyle;
	if (cstrdashStyle != NULL)
	{
		dashStyle = cstrdashStyle;
	}
	//根据字符串中逗号的个数来判断线型
	int len = dashStyle.length();
	int count = 0;//逗号个数
	for (int i = 0; i < len; i++)
	{
		if (dashStyle[i] == ',')
		{
			++count;
		}
	}
	switch(count)
	{
	case 0:
		m_LineType = DashStyleSolid;
		break;

	case 1:
		int dash,gap;
		sscanf(dashStyle.c_str(),"%d,%d",&dash,&gap);
		if (dash == gap)
		{
			m_LineType = DashStyleDot;
		}
		else
		{
			m_LineType = DashStyleDash;
		}

		break;

	case 3:
		m_LineType = DashStyleDashDot;
		break;

	case 5:
		m_LineType = DashStyleDashDotDot;
		break;
	}
}

void CGraph::SetDashGap(TiXmlElement *pNode)
{
	char gashGap[32];
	switch (m_LineType)
	{
	case DashStyleDash:
		sprintf(gashGap,"%d,%d",3*m_LineWidth,m_LineWidth);
		break;
	case DashStyleDot:
		sprintf(gashGap,"%d,%d",m_LineWidth,m_LineWidth);
		break;
	case DashStyleDashDot:
		sprintf(gashGap,"%d,%d,%d,%d",3*m_LineWidth,m_LineWidth,m_LineWidth,m_LineWidth);
		break;
	case DashStyleDashDotDot:
		sprintf(gashGap,"%d,%d,%d,%d,%d,%d",3*m_LineWidth,m_LineWidth,m_LineWidth,m_LineWidth,m_LineWidth,m_LineWidth);
		break;
	}
	if (m_LineType != DashStyleSolid)
	{
		pNode->SetAttribute("stroke-dasharray",gashGap);
	}
}

CLine::CLine(POINT start,POINT end):m_start(start),m_end(end)
{
}

CLine::CLine(TiXmlElement*pElement)
{
	int x1,y1,x2,y2;
	pElement->Attribute("x1",&x1);
	pElement->Attribute("y1",&y1);
	pElement->Attribute("x2",&x2);
	pElement->Attribute("y2",&y2);
	
	m_start.x = x1;
	m_start.y = y1;
	m_end.x = x2;
	m_end.y = y2;
}

void CLine::Draw(Graphics *pGraphics)
{
	Pen pen(Color(GetRValue(m_LineColor),GetGValue(m_LineColor),GetBValue(m_LineColor)),m_LineWidth);
	pen.SetDashStyle(m_LineType);
	pGraphics->DrawLine(&pen,m_start.x,m_start.y,m_end.x,m_end.y);
}

void CLine::DrawHit(Graphics *pGraphics)
{
	Draw(pGraphics);

	Pen pen(Color(255,0,0),2);
	//pen.SetDashStyle(DashStyleDot);
	pGraphics->DrawRectangle(&pen,m_start.x-m_LineWidth,m_start.y-m_LineWidth,
		m_LineWidth*2,m_LineWidth*2);
	pGraphics->DrawRectangle(&pen,m_end.x-m_LineWidth,m_end.y-m_LineWidth,
		m_LineWidth*2,m_LineWidth*2);
}

bool CLine::IsHit(POINT point)
{
	/*if (m_start.x <= m_start.x)
	{
		if (m_start.y <= m_end.y)
		{
			return (m_start.x <= point.x && point.x <= m_end.x
				&& m_start.y <= point.y && point.y <= m_end.y);
		}
		else
		{
			return (m_start.x <= point.x && point.x <= m_end.x
				&& m_start.y >= point.y && point.y >= m_end.y);
		}
	}
	else
	{
		if (m_start.y <= m_end.y)
		{
			return (m_start.x >= point.x && point.x >= m_end.x
				&& m_start.y <= point.y && point.y <= m_end.y);
		}
		else
		{
			return (m_start.x >= point.x && point.x >= m_end.x
				&& m_start.y >= point.y && point.y >= m_end.y);
		}
	}*/
	long aa = (m_start.x - m_end.x)*(m_start.x - m_end.x)/4+(m_start.y-m_end.y)*(m_start.y-m_end.y)/4;//a的平方
	long bb = aa/8;//b的平方,b为a的1/3~1/2

	int x = point.x - (m_start.x + m_end.x)/2;
	int y = point.y - (m_start.y + m_end.y)/2;

	if (x*x*aa + y*y*bb < aa*bb)
	{
		return true;
	}

	return false;
}

void CLine::Move(int dx,int dy)
{
	ToySG::Move(m_start,dx,dy);
	ToySG::Move(m_end,dx,dy);
}

void CLine::Scale(float f)
{
	POINT org;
	org.x = (m_start.x+m_end.x)/2;
	org.y = (m_start.y+m_end.y)/2;

	ToySG::Scale(org,m_start,f);
	ToySG::Scale(org,m_end,f);
}

void CLine::Mirror(Coordinate conrdinate,int c)
{
	ToySG::Mirror(m_start,conrdinate,c);
	ToySG::Mirror(m_end,conrdinate,c);
}

void CLine::Rotate(POINT,Direction direction,int degree)
{
	POINT o;
	o.x = (m_start.x + m_end.x)/2;
	ToySG::Rotate(o,m_start,direction,degree);
	ToySG::Rotate(o,m_end,direction,degree);
}

void CLine::Save(TiXmlElement *pParent)
{
	TiXmlElement *pLine = new TiXmlElement("line");
	pLine->SetAttribute("x1",m_start.x);
	pLine->SetAttribute("y1",m_start.y);
	pLine->SetAttribute("x2",m_end.x);
	pLine->SetAttribute("y2",m_end.y);
	char strcolor[16];
	sprintf(strcolor,"rgb(%d,%d,%d)",GetRValue(m_LineColor),GetGValue(m_LineColor),GetBValue(m_LineColor));
	pLine->SetAttribute("stroke",strcolor);
	pLine->SetAttribute("stroke-width",m_LineWidth);
	//设置线型
	SetDashGap(pLine);
	//添加得到svg父节点
	pParent->LinkEndChild(pLine);
}

CRectangle::CRectangle(POINT top_left,POINT bottom_right)
	:m_top_left(top_left),m_bottom_right(bottom_right)
{
}

CRectangle::CRectangle(TiXmlElement*pElement)
{
	int x,y,width,height;
	pElement->Attribute("x",&x);
	pElement->Attribute("y",&y);
	pElement->Attribute("width",&width);
	pElement->Attribute("height",&height);

	m_top_left.x = x;
	m_top_left.y = y;
	m_bottom_right.x = x+width;
	m_bottom_right.y = y+height;
}

void CRectangle::Draw(Graphics *pGraphics)
{
	Pen pen(Color(GetRValue(m_LineColor),GetGValue(m_LineColor),GetBValue(m_LineColor)),m_LineWidth);
	pen.SetDashStyle(m_LineType);
	pGraphics->DrawRectangle(&pen,m_top_left.x,m_top_left.y,
		m_bottom_right.x - m_top_left.x,m_bottom_right.y - m_top_left.y);
}

void CRectangle::DrawHit(Graphics *pGraphics)
{
	Draw(pGraphics);

	Pen pen(Color(255,0,0),2);
	//pen.SetDashStyle(DashStyleDot);
	pGraphics->DrawRectangle(&pen,m_top_left.x-m_LineWidth,
		m_top_left.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);

	pGraphics->DrawRectangle(&pen,m_bottom_right.x-m_LineWidth,
		m_bottom_right.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);

	pGraphics->DrawRectangle(&pen,m_bottom_right.x-m_LineWidth,
		m_top_left.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);

	pGraphics->DrawRectangle(&pen,m_top_left.x-m_LineWidth,
		m_bottom_right.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);
}

bool CRectangle::IsHit(POINT point)
{
	return (m_top_left.x <= point.x && m_top_left.y <= point.y &&
		point.x <= m_bottom_right.x && point.y <= m_bottom_right.y);
}

void CRectangle::Move(int dx,int dy)
{
	ToySG::Move(m_top_left,dx,dy);
	ToySG::Move(m_bottom_right,dx,dy);
}

void CRectangle::Scale(float f)
{
	POINT org;
	org.x = (m_top_left.x + m_bottom_right.x)/2;
	org.y = (m_top_left.y + m_bottom_right.y)/2;

	ToySG::Scale(org,m_top_left,f);
	ToySG::Scale(org,m_bottom_right,f);
}

void CRectangle::Rotate(POINT,Direction dir,int degree)
{
	POINT o;
	o.x = (m_top_left.x + m_bottom_right.x)/2;
	o.y = (m_top_left.y + m_bottom_right.y)/2;

	ToySG::Rotate(o,m_top_left,dir,degree);
	ToySG::Rotate(o,m_bottom_right,dir,degree);
}

void CRectangle::Mirror(Coordinate coo,int c)
{
	ToySG::Mirror(m_top_left,coo,c);
	ToySG::Mirror(m_bottom_right,coo,c);
}

void CRectangle::Save(TiXmlElement *pParent)
{
	TiXmlElement *pRect = new TiXmlElement("rect");
	pRect->SetAttribute("x",m_top_left.x);
	pRect->SetAttribute("y",m_top_left.y);
	pRect->SetAttribute("width",m_bottom_right.x-m_top_left.x);
	pRect->SetAttribute("height",m_bottom_right.y-m_top_left.y);
	pRect->SetAttribute("fill","none");
	char strcolor[16];
	sprintf(strcolor,"rgb(%d,%d,%d)",GetRValue(m_LineColor),GetGValue(m_LineColor),GetBValue(m_LineColor));
	pRect->SetAttribute("stroke",strcolor);
	pRect->SetAttribute("stroke-width",m_LineWidth);
	SetDashGap(pRect);
	
	pParent->LinkEndChild(pRect);
}

CEllipse::CEllipse(POINT top_left,POINT bottom_right)
	:m_top_left(top_left),m_bottom_right(bottom_right)
{
}

CEllipse::CEllipse(TiXmlElement*pElement)
{
	int cx,cy,rx,ry;
	pElement->Attribute("cx",&cx);
	pElement->Attribute("cy",&cy);
	pElement->Attribute("rx",&rx);
	pElement->Attribute("ry",&ry);

	m_top_left.x = cx - rx;
	m_top_left.y = cy - ry;
	m_bottom_right.x = cx + rx;
	m_bottom_right.y = cy + ry;
}

void CEllipse::Draw(Graphics *pGraphics)
{
	Pen pen(Color(GetRValue(m_LineColor),GetGValue(m_LineColor),GetBValue(m_LineColor)),m_LineWidth);
	pen.SetDashStyle(m_LineType);
	pGraphics->DrawEllipse(&pen,m_top_left.x,m_top_left.y,
		m_bottom_right.x - m_top_left.x,m_bottom_right.y - m_top_left.y);
}

void CEllipse::DrawHit(Graphics *pGraphics)
{
	Draw(pGraphics);
	Pen pen(Color(255,0,0),2);
	pGraphics->DrawRectangle(&pen,m_top_left.x-m_LineWidth,
		m_top_left.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);

	pGraphics->DrawRectangle(&pen,m_bottom_right.x-m_LineWidth,
		m_bottom_right.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);

	pGraphics->DrawRectangle(&pen,m_bottom_right.x-m_LineWidth,
		m_top_left.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);

	pGraphics->DrawRectangle(&pen,m_top_left.x-m_LineWidth,
		m_bottom_right.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);
}

bool CEllipse::IsHit(POINT point)
{
	if(m_top_left.x <= point.x && m_top_left.y <= point.y &&
		point.x <= m_bottom_right.x && point.y <= m_bottom_right.y)
	{
		int a = (m_bottom_right.x - m_top_left.x)/2;
		int b = (m_bottom_right.y - m_top_left.y)/2;
		int x = point.x - (m_bottom_right.x + m_top_left.x)/2;
		int y = point.y - (m_bottom_right.y + m_top_left.y)/2;
		if (a*a*x*x + b*b*y*y < a*a*b*b)
		{
			return true;
		}
	}

	return false;
}

void CEllipse::Move(int dx,int dy)
{
	ToySG::Move(m_top_left,dx,dy);
	ToySG::Move(m_bottom_right,dx,dy);
}

void CEllipse::Scale(float f)
{
	POINT org;
	org.x = (m_top_left.x + m_bottom_right.x)/2;
	org.y = (m_top_left.y + m_bottom_right.y)/2;

	ToySG::Scale(org,m_top_left,f);
	ToySG::Scale(org,m_bottom_right,f);
}

void CEllipse::Rotate(POINT o,Direction dir,int degree)
{
	o.x = (m_top_left.x + m_bottom_right.x)/2;
	o.y = (m_top_left.y + m_bottom_right.y)/2;

	ToySG::Rotate(o,m_top_left,dir,degree);
	ToySG::Rotate(o,m_bottom_right,dir,degree);
}

void CEllipse::Mirror(Coordinate coo,int c)
{
	ToySG::Mirror(m_top_left,coo,c);
	ToySG::Mirror(m_bottom_right,coo,c);
}

void CEllipse::Save(TiXmlElement *pParent)
{
	TiXmlElement *pEllipse = new TiXmlElement("ellipse");
	pEllipse->SetAttribute("cx",(m_top_left.x+m_bottom_right.x)/2);
	pEllipse->SetAttribute("cy",(m_top_left.y+m_bottom_right.y)/2);
	pEllipse->SetAttribute("rx",(m_bottom_right.x-m_top_left.x)/2);
	pEllipse->SetAttribute("ry",(m_bottom_right.y-m_top_left.y)/2);
	pEllipse->SetAttribute("fill","none");
	char strcolor[16];
	sprintf(strcolor,"rgb(%d,%d,%d)",GetRValue(m_LineColor),GetGValue(m_LineColor),GetBValue(m_LineColor));
	pEllipse->SetAttribute("stroke",strcolor);
	pEllipse->SetAttribute("stroke-width",m_LineWidth);
	SetDashGap(pEllipse);
	pParent->LinkEndChild(pEllipse);
}

CPolygon::CPolygon(int num/* =0 */,Point* pPointArray/* =NULL */)
	:m_num(num),m_pPointArray(pPointArray)
{
}

CPolygon::CPolygon(TiXmlElement*pElement):m_num(0),m_pPointArray(NULL)
{
	string strpoints = pElement->Attribute("points");
	//统计逗号的个数来计算点的个数，一般点用两个数字表示(x,y),每个点用空格隔开
	int num = 0;
	int len = strpoints.length();
	for (int i = 0; i < len; i++)
	{
		if (strpoints[i] == ',')
		{
			++num;
		}
	}
	m_num = num;
	//统计出了点的个数，为点申请内存
	m_pPointArray = new Gdiplus::Point[num];
	//从字符串中输入各个坐标值，初始化所有点
	const char * cstrpoints = strpoints.c_str();
	for(int i = 0, j = 0; i < num && j < len; i++)
	{
		int x,y;
		sscanf(cstrpoints+j,"%d,%d",&x,&y);
		m_pPointArray[i].X = x;
		m_pPointArray[i].Y = y;

		while (cstrpoints[j] != ' ' && j < len)
		{
			++j;
		}
		++j;
	}
}

CPolygon::~CPolygon()
{
	if (m_pPointArray != NULL)
	{
		delete[] m_pPointArray;
		m_pPointArray = NULL;
	}
}

void CPolygon::Draw(Graphics *pGraphics)
{
	Pen pen(Color(GetRValue(m_LineColor),GetGValue(m_LineColor),GetBValue(m_LineColor)),m_LineWidth);
	pen.SetDashStyle(m_LineType);
	pGraphics->DrawPolygon(&pen,m_pPointArray,m_num);
}

void CPolygon::DrawHit(Graphics *pGraphics)
{
	Draw(pGraphics);
	
	Pen pen(Color(255,0,0),2);
	
	for (int i = 0; i < m_num; i++)
	{
		pGraphics->DrawRectangle(&pen,m_pPointArray[i].X-m_LineWidth,
			m_pPointArray[i].Y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);
	}
}

bool CPolygon::IsHit(POINT point)
{
	int maxx,minx,maxy,miny;
	maxx = minx = m_pPointArray[0].X;
	maxy = miny = m_pPointArray[0].Y;

	for (int i = 1; i < m_num; i++)
	{
		if (m_pPointArray[i].X < minx)
		{
			minx = m_pPointArray[i].X;
		}

		if (m_pPointArray[i].X > maxx)
		{
			maxx = m_pPointArray[i].X;
		}

		if (m_pPointArray[i].Y < miny)
		{
			miny = m_pPointArray[i].Y;
		}

		if (m_pPointArray[i].Y > maxy)
		{
			maxy = m_pPointArray[i].Y;
		}
	}

	return minx <= point.x && point.x <= maxx
		&& miny <= point.y && point.y <= maxy;
}

void CPolygon::Move(int dx,int dy)
{
	if (m_pPointArray != NULL)
	{
		ToySG::Move(m_pPointArray,m_num,dx,dy);
	}
}

void CPolygon::Scale(float f)
{
	POINT org;
	org.x = 0;
	org.y = 0;
	for (int i = 0; i < m_num; i++)
	{
		org.x += m_pPointArray[i].X;
		org.y += m_pPointArray[i].Y;
	}
	org.x /= m_num;
	org.y /= m_num;

	ToySG::Scale(org,m_pPointArray,m_num,f);
}

void CPolygon::Rotate(POINT,Direction dir,int degree)
{
	if (m_pPointArray != NULL)
	{
		POINT o;
		long temx=0,temy=0;
		for (int i = 0; i < m_num; i++)
		{
			temx += m_pPointArray[i].X;
			temy += m_pPointArray[i].Y;
		}
		o.x = temx/m_num;
		o.y = temy/m_num;
		
		ToySG::Rotate(o,m_pPointArray,m_num,dir,degree);
	}
}

void CPolygon::Mirror(Coordinate coo,int c)
{
	if (m_pPointArray != NULL)
	{
		ToySG::Mirror(m_pPointArray,m_num,coo,c);
	}
}

void CPolygon::Save(TiXmlElement *pParent)
{
	TiXmlElement *pPolygon = new TiXmlElement("polygon");
	pPolygon->SetAttribute("fill","none");
	//设置各个点的xy坐标
	string strpoints;
	for (int i = 0; i < m_num; i++)
	{
		char strpoint[10]={'\0'};
		
		sprintf(strpoint,"%d,%d ",m_pPointArray[i].X,m_pPointArray[i].Y);
		
		strpoints += strpoint;
	}
	pPolygon->SetAttribute("points",strpoints);
	//设置颜色
	char strcolor[16];
	sprintf(strcolor,"rgb(%d,%d,%d)",GetRValue(m_LineColor),GetGValue(m_LineColor),GetBValue(m_LineColor));
	pPolygon->SetAttribute("stroke",strcolor);
	//设置线宽
	pPolygon->SetAttribute("stroke-width",m_LineWidth);
	//设置线型
	SetDashGap(pPolygon);
	pParent->LinkEndChild(pPolygon);
}

CBezierCurve::CBezierCurve(POINT first_end,
	POINT second_end,
	POINT first_control,
	POINT second_control)
	:m_first_end(first_end),m_second_end(second_end),
	m_first_control(first_control),m_second_control(second_control)
{
}

CBezierCurve::CBezierCurve(TiXmlElement*pElement)
{
	string dstr = pElement->Attribute("d");
	int x1,y1,x2,y2,x3,y3,x4,y4;
	sscanf(dstr.c_str(),"%M %d %d C %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);

	m_first_end.x = x1;
	m_first_end.y = y1;
	m_first_control.x = x2;
	m_first_control.y = y2;
	m_second_control.x = x3;
	m_second_control.y = y3;
	m_second_end.x = x4;
	m_second_end.y = y4;
}

void CBezierCurve::Draw(Graphics *pGraphics)
{
	Pen pen(Color(GetRValue(m_LineColor),GetGValue(m_LineColor),GetBValue(m_LineColor)),m_LineWidth);
	pen.SetDashStyle(m_LineType);
	pGraphics->DrawBezier(&pen,m_first_end.x,m_first_end.y,m_first_control.x,m_first_control.y,
		m_second_control.x,m_second_control.y,m_second_end.x,m_second_end.y);
}

void CBezierCurve::DrawHit(Graphics *pGraphics)
{
	Draw(pGraphics);
	Pen pen(Color(0,0,0),2);

	pGraphics->DrawRectangle(&pen,m_first_control.x-m_LineWidth,
		m_first_control.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);

	pGraphics->DrawRectangle(&pen,m_second_control.x-m_LineWidth,
		m_second_control.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);

	pen.SetColor(Color(255,0,0));
	pGraphics->DrawRectangle(&pen,m_first_end.x-m_LineWidth,
		m_first_end.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);

	pGraphics->DrawRectangle(&pen,m_second_end.x-m_LineWidth,
		m_second_end.y-m_LineWidth,m_LineWidth*2,m_LineWidth*2);

	pen.SetWidth(1);
	pen.SetColor(Color(0,0,0));
	pGraphics->DrawLine(&pen,m_first_end.x,m_first_end.y,m_first_control.x,m_first_control.y);
	pGraphics->DrawLine(&pen,m_second_end.x,m_second_end.y,m_second_control.x,m_second_control.y);
}

bool CBezierCurve::IsHit(POINT point)
{
	/*if (m_first_end.x <= m_second_end.x)
	{
	if (m_first_end.y <= m_second_end.y)
	{
	return (m_first_end.x <= point.x && point.x <= m_second_end.x &&
	m_first_end.y <= point.y && point.y <= m_second_end.y);
	}
	else
	{
	return (m_first_end.x <= point.x && point.x <= m_second_end.x &&
	m_first_end.y >= point.y && point.y >= m_second_end.y);
	}
	}
	else
	{
	if (m_first_end.y <= m_second_end.y)
	{
	return (m_first_end.x >= point.x && point.x >= m_second_end.x &&
	m_first_end.y <= point.y && point.y <= m_second_end.y);
	}
	else
	{
	return (m_first_end.x >= point.x && point.x >= m_second_end.x &&
	m_first_end.y >= point.y && point.y >= m_second_end.y);
	}
	}*/

	int c2 =  (m_first_end.x - m_second_end.x)*(m_first_end.x - m_second_end.x)/4+
		(m_first_end.y - m_second_end.y)*(m_first_end.y - m_second_end.y)/4;//c2为c的平方

	int d1 = sqrt((long double)((point.x - m_first_end.x)*(point.x - m_first_end.x) +
			(point.y - m_first_end.y)*(point.y - m_first_end.y)));//d1为point到第一个点的距离

	int d2 = sqrt((long double)((point.x - m_second_end.x)*(point.x - m_second_end.x) +
			(point.y - m_second_end.y)*(point.y - m_second_end.y)));//d2为point到第二个点的距离

	if ((d1+d2)*(d1+d2) < 5*c2)
	{
		return true;
	}
	return false;
}

void CBezierCurve::Move(int dx,int dy)
{
	ToySG::Move(m_first_end,dx,dy);
	ToySG::Move(m_second_end,dx,dy);
	ToySG::Move(m_first_control,dx,dy);
	ToySG::Move(m_second_control,dx,dy);
}

void CBezierCurve::Scale(float f)
{
	POINT org;
	org.x = (m_first_end.x + m_second_end.x)/2;
	org.y = (m_first_end.y + m_second_end.y)/2;

	ToySG::Scale(org,m_first_end,f);
	ToySG::Scale(org,m_second_end,f);
	ToySG::Scale(org,m_first_control,f);
	ToySG::Scale(org,m_second_control,f);
}

void CBezierCurve::Rotate(POINT,Direction dir,int degree)
{
	POINT o;
	o.x = (m_first_end.x + m_second_end.x)/2;
	o.y = (m_first_end.y + m_second_end.y)/2;

	ToySG::Rotate(o,m_first_end,dir,degree);
	ToySG::Rotate(o,m_second_end,dir,degree);
	ToySG::Rotate(o,m_first_control,dir,degree);
	ToySG::Rotate(o,m_second_control,dir,degree);
}

void CBezierCurve::Mirror(Coordinate coo,int c)
{
	ToySG::Mirror(m_first_end,coo,c);
	ToySG::Mirror(m_second_end,coo,c);
	ToySG::Mirror(m_first_control,coo,c);
	ToySG::Mirror(m_second_control,coo,c);
}

void CBezierCurve::Save(TiXmlElement *pParent)
{
	//用svg的路径命令d来实现贝塞尔曲线
	TiXmlElement *pBezierCurve = new TiXmlElement("path");
	//自定义一个属性，表示是贝塞尔曲线
	pBezierCurve->SetAttribute("type","bezier");
	//设置颜色
	char strcolor[16];
	sprintf(strcolor,"rgb(%d,%d,%d)",GetRValue(m_LineColor),GetGValue(m_LineColor),GetBValue(m_LineColor));
	pBezierCurve->SetAttribute("stroke",strcolor);
	pBezierCurve->SetAttribute("stroke-width",m_LineWidth);
	pBezierCurve->SetAttribute("fill","none");
	char strd[64];
	sprintf(strd,"M %d %d C %d %d %d %d %d %d",m_first_end.x,m_first_end.y,m_first_control.x,m_first_control.y,
		m_second_control.x,m_second_control.y,m_second_end.x,m_second_end.y);
	pBezierCurve->SetAttribute("d",strd);
	
	SetDashGap(pBezierCurve);

	pParent->LinkEndChild(pBezierCurve);
}

