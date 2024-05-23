#pragma once

//シーンの基底クラス（親クラス）
class BaseScene
{
public:
	//関数
	//仮想関数
	virtual void Init();
	virtual void Draw();
	virtual void Update();
	virtual void Release();
private:
	Math::Matrix m_mat;
	KdTexture m_tex;
	Math::Vector3 m_pos;
	Math::Vector3 m_move;
};
