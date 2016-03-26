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
	CGraph* IsHit(POINT);				//��굥�����Ƿ�ѡ��ĳ��ͼ�Σ�ѡ�еĻ����ظ�ͼ�Σ����򷵻�null
	void	Draw(Graphics*pGraphics);	//��������ͼ��
	void	MoveSelectGraph(int dx,int dy);
	void	ScaleGraph(float f);
	void	SelectNo();
	CGraph*	GetSelectedGraph();
	SIZE	GetCanvasSize();

	SIZE m_CanvasSize;
private:
	list<CGraph*>	m_Graphs;
	CGraph*			m_pGraphSelected;//��ѡ�е�ͼ�Σ�һ��ֻ��ѡ��һ��ͼ�Σ����������

	
};

