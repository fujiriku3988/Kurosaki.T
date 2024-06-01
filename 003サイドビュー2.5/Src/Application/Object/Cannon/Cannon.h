#pragma once

class Cannon:public KdGameObject
{
public:
	Cannon() { Init(); };
	~Cannon()override {};

	void DrawLit()override;
	void Init()override;
private:

	std::shared_ptr<KdModelData> m_model;
};

