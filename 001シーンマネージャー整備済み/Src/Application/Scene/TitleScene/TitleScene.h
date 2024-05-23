#pragma once
//class BaseScene;
//継承にかぎり、includeしてもよい
#include"../BaseScene/BaseScene.h"

class TitleScene:public BaseScene
{
public:
	//コンストラクタ
	TitleScene() { Init(); };
	//デストラクタ
	~TitleScene() { Release(); };
	//関数
	void Init()override;
	void Draw()override;
	void Update()override;
	void Release()override;
private:
	//変数
	//テクスチャ（タイトル画面用）
	KdTexture m_titleTex;//キャメル型
	KdTexture m_startTex;
	//KdTexture m_title_tex;//スネーク型
	float m_a = 0.5f;
	float m_b = 0.01f;
};