#pragma once
#include <list>
#include <string>
#include "ToySG.h"
using std::list;
using std::string;

using ToySG::CGraph;
class CGraphList
{
public:
	CGraphList(void);
	~CGraphList(void);

	void Save(string fileName);
	void Load(string fileName);
	
	void AddGraph(CGraph*);
	void DeleteSelectedGraph();
	CGraph* IsHit(POINT);				//鼠标单击后是否选中某个图形，选中的话返回该图形，否则返回null
	void	Draw(Graphics*pGraphics);	//绘制所有图形
	void	MoveSelectGraph(int dx,int dy);
	void	ScaleGraph(float f);
	void	SelectNo();
	CGraph*	GetSelectedGraph();
	SIZE	GetCanvasSize();

	SIZE m_CanvasSize;
private:
	list<CGraph*>	m_Graphs;
	CGraph*			m_pGraphSelected;//被选中的图形，一次只能选着一个图形，并对其操作

	
};

