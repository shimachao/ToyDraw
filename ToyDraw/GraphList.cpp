#include "StdAfx.h"
#include "GraphList.h"

#define TIXML_USE_STL
#include "tinystr.h"
#include "tinyxml.h"

using namespace ToySG;

CGraphList::CGraphList(void):m_pGraphSelected(NULL)
{
	m_CanvasSize.cx = 400;
	m_CanvasSize.cy = 300;
}


CGraphList::~CGraphList(void)
{
	if (m_pGraphSelected != NULL)
	{
		delete m_pGraphSelected;
	}
}

void CGraphList::Save(string fileName)
{
	TiXmlDocument *pDoc = new TiXmlDocument;
	TiXmlDeclaration *pDec = new TiXmlDeclaration("1.0","UTF-8","no");

	pDoc->LinkEndChild(pDec);
	//添加根节点
	TiXmlElement *pRoot = new TiXmlElement("svg");
	pRoot->SetAttribute("width",m_CanvasSize.cx);//保存画布大小
	pRoot->SetAttribute("height",m_CanvasSize.cy);
	pRoot->SetAttribute("version","1.1");
	pRoot->SetAttribute("xmlns","http://www.w3.org/2000/svg");
	pDoc->LinkEndChild(pRoot);

	//依次保存各个图形到svg文件中
	for (list<CGraph*>::iterator it = m_Graphs.begin();it != m_Graphs.end();++it)
	{
		(*it)->Save(pRoot);
	}

	if (fileName.find(".svg") == string::npos)
	{
		fileName += ".svg";
	}
	
	pDoc->SaveFile(fileName);
}

void CGraphList::Load(string fileName)
{
	m_Graphs.clear();
	if (m_pGraphSelected != NULL)
	{
		delete m_pGraphSelected;
		m_pGraphSelected = NULL;
	}
	//遍历文档，依次创建所有图形
	TiXmlDocument *pDoc = new TiXmlDocument;
	pDoc->LoadFile(fileName);
	TiXmlNode *pRoot = pDoc->FirstChild("svg");

	if (pRoot == NULL)
	{
		return;
	}
	
	TiXmlElement *pSvg = pDoc->FirstChildElement("svg");
	if (pSvg != NULL)
	{
		int cx=0,cy=0;
		pSvg->Attribute("width",&cx);
		pSvg->Attribute("height",&cy);
		m_CanvasSize.cx = cx;
		m_CanvasSize.cy = cy;
	}
	else
	{
		AfxMessageBox(L"读取图行大小失败！");
	}

	TiXmlElement *pElement = NULL;

	for (pElement = pRoot->FirstChildElement(); pElement != NULL;
		pElement = pElement->NextSiblingElement())
	{//处理每个子元素，提取出属性值，创建图元类
		string graphName = pElement->ValueStr();
		CGraph *pGraph = NULL;
		
		if (graphName == "line")
		{
			pGraph = new CLine(pElement);
		}
		else if (graphName == "rect")
		{
			pGraph = new CRectangle(pElement);
		}
		else if (graphName == "ellipse")
		{
			pGraph = new CEllipse(pElement);
		}
		else if (graphName == "polygon")
		{
			pGraph = new CPolygon(pElement);
		}
		else if (graphName == "path")
		{//贝塞尔曲线需要特殊处理
			const char *cstrtype = pElement->Attribute("type");
			string type;
			if (cstrtype != NULL)
			{
				type = cstrtype;
			}
			if (type == "bezier")
			{//确实是贝塞尔曲线
				pGraph = new CBezierCurve(pElement);
			}
		}

		//读取成功就接着读取颜色、线宽、线型，然后添加到链表
		if (pGraph != NULL)
		{
			//设置颜色、线宽、线型
			pGraph->SetAttributes(pElement);
			//添加到链表
			m_Graphs.push_back(pGraph);
			pGraph = NULL;
		}
	}
}

void CGraphList::AddGraph(CGraph * pGraph)
{
	m_Graphs.push_back(pGraph);
}

void CGraphList::DeleteSelectedGraph()
{
	if (m_pGraphSelected != NULL)
	{
		delete m_pGraphSelected;
		m_pGraphSelected = NULL;
	}
}

CGraph* CGraphList::IsHit(POINT point)
{
	for (list<CGraph*>::iterator it = m_Graphs.begin();it != m_Graphs.end();++it)
	{
		if ((*it)->IsHit(point))
		{
			if (m_pGraphSelected != NULL)
			{
				m_Graphs.push_back(m_pGraphSelected);
			}
			m_pGraphSelected = *it;
			m_Graphs.erase(it);
			return m_pGraphSelected;
		}
	}
	if (m_pGraphSelected != NULL)
	{
		m_Graphs.push_back(m_pGraphSelected);
		m_pGraphSelected = NULL;
	}
	
	return m_pGraphSelected;
}

void CGraphList::Draw(Graphics*pGraphics)
{
	for (list<CGraph*>::iterator it = m_Graphs.begin();it != m_Graphs.end();++it)
	{
		(*it)->Draw(pGraphics);
	}
	if (m_pGraphSelected!=NULL)
	{
		m_pGraphSelected->DrawHit(pGraphics);
	}
}


void CGraphList::MoveSelectGraph(int dx,int dy)
{
	if (m_pGraphSelected != NULL)
	{
		m_pGraphSelected->Move(dx,dy);
	}
}


void CGraphList::ScaleGraph(float f)
{
	if (m_pGraphSelected != NULL)
	{
		m_pGraphSelected->Scale(f);
	}
}

void CGraphList::SelectNo()
{
	if (m_pGraphSelected != NULL)
	{
		m_Graphs.push_back(m_pGraphSelected);
		m_pGraphSelected = NULL;
	}
}


CGraph* CGraphList::GetSelectedGraph()
{
	return m_pGraphSelected;
}

SIZE CGraphList::GetCanvasSize()
{
	return m_CanvasSize;
}
