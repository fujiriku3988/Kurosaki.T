#pragma once

class back :public KdGameObject
{
public:
	back() { Init(); }
	~back(){}
	void Init()override;
	void DrawUnLit()override;
private:
	KdSquarePolygon m_polygon;

};