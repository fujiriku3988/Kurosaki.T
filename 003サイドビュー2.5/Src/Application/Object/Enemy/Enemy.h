#pragma once
class Enemy :public KdGameObject
{
public:
	Enemy() { Init(); };
	~Enemy()override {};

	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void Init()override;
	void GenerateDepthMapFromLight()override;

	void SetPosE(const Math::Vector3& pos) { m_pos = pos; }

	void OnHit()override;

private:
	KdSquarePolygon m_polygon;
	Math::Vector3 m_pos;
	float m_anime = 0;
	float m_gravity = 0;
	float m_movePow;
	float m_goal = 0;
	int m_dir=1;
};

