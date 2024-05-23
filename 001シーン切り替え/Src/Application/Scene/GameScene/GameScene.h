#pragma once
#include"../BaseScene/BaseScene.h"
class GameScene:public BaseScene
{
public:
	//コンストラクタ
	GameScene() { Init(); };
	//デストラクタ
	~GameScene() { Release(); };
	//関数
	void Init()override;
	void Draw()override;
	void Update()override;
	void Release()override;
private:
	KdTexture m_playerTex;
	Math::Vector3 m_pos;
	Math::Matrix m_mat;

};