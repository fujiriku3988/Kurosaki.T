#pragma once
class Player:public KdGameObject
{
public:
	Player() { Init(); };
	~Player()override {};

	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void Init()override;


private:
	KdSquarePolygon m_polygon;
	Math::Vector3 m_pos;
	float m_anime = 0;
	float m_gravity = 0;
};

