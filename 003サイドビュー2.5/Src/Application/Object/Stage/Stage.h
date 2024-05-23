#pragma once

class Stage :public KdGameObject
{
public:
	Stage() { Init(); }
	~Stage() {}

	void DrawLit()override;
	void Init()override;

private:

	KdModelData m_model;
};