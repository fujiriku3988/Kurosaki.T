#pragma once
class Player :public KdGameObject
{
public:
	Player() { Init(); }
	~Player() {}

	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void Init()override;

private:
	KdSquarePolygon m_polygon;
	Math::Vector3 m_pos;
	Math::Vector3 m_move;
	float m_anime;
	float m_gravity = 0;
};