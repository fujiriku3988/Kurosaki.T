#pragma once

class Stage:public KdGameObject
{
public:
	Stage() { Init(); };
	~Stage()override {};

	void DrawLit()override;
	void Init()override;

	void SetPosS(const Math::Vector3& pos) { m_pos = pos; }
private:
	Math::Vector3 m_pos;
	std::shared_ptr<KdModelData> m_model;
};

