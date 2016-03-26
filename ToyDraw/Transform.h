#pragma once
namespace ToySG{
	//将一系列点移动x，y距离
	void Move(POINT points[],int num,int dx,int dy);
	void Move(Point points[],int num,int dx,int dy);
	//将点point移动x，y距离
	void Move(POINT &point,int dx,int dy);

	//缩放一个点
	void Scale(POINT &org,POINT &p,float f);
	//缩放一系列点
	void Scale(POINT &org,POINT points[],int num,float f);
	void Scale(POINT &org,Point points[],int num,float f);

	//将一系列点points以origin为原点，向direction方向选择degree度
	void Rotate(POINT origin,POINT points[],int num,Direction direction,int degree);
	void Rotate(POINT origin,Point points[],int num,Direction direction,int degree);
	//将点point以origin为原点，向direction方向选择degree度
	void Rotate(POINT origin,POINT &point,Direction direction,int degree);

	//将一系列点points以x=c或y=c为对称轴作对称变换
	void Mirror(POINT points[],int num,Coordinate,int c);
	void Mirror(Point points[],int num,Coordinate,int c);
	//将点point以x=c或y=c为对称轴作对称变换
	void Mirror(POINT &point,Coordinate,int c);
}
