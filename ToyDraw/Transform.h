#pragma once
namespace ToySG{
	//��һϵ�е��ƶ�x��y����
	void Move(POINT points[],int num,int dx,int dy);
	void Move(Point points[],int num,int dx,int dy);
	//����point�ƶ�x��y����
	void Move(POINT &point,int dx,int dy);

	//����һ����
	void Scale(POINT &org,POINT &p,float f);
	//����һϵ�е�
	void Scale(POINT &org,POINT points[],int num,float f);
	void Scale(POINT &org,Point points[],int num,float f);

	//��һϵ�е�points��originΪԭ�㣬��direction����ѡ��degree��
	void Rotate(POINT origin,POINT points[],int num,Direction direction,int degree);
	void Rotate(POINT origin,Point points[],int num,Direction direction,int degree);
	//����point��originΪԭ�㣬��direction����ѡ��degree��
	void Rotate(POINT origin,POINT &point,Direction direction,int degree);

	//��һϵ�е�points��x=c��y=cΪ�Գ������ԳƱ任
	void Mirror(POINT points[],int num,Coordinate,int c);
	void Mirror(Point points[],int num,Coordinate,int c);
	//����point��x=c��y=cΪ�Գ������ԳƱ任
	void Mirror(POINT &point,Coordinate,int c);
}
