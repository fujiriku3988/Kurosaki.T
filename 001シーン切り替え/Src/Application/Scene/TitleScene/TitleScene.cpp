#include "TitleScene.h"

void TitleScene::Init()
{
	//テクスチャ読み込み
	m_titleTex.Load("Asset/Textures/title.png");
	m_startTex.Load("Asset/Textures/start.png");
}

void TitleScene::Draw()
{
	//SHADERはマクロ定義されていた（１年）
	//SHADER.m_spriteShader.DrawTex();
	//2D描画はSetMatrixが不要
	//※回転させる場合は必要
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_titleTex, 0, 0);
	//					r,g,b,a
	Math::Color color = { 1,1,1,m_a };
	//Math::Color color = { 1,1,1,sin(DirectX::XMConvertToRadians(m_a)) };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_startTex, 0, -200, nullptr, &color);
}

void TitleScene::Update()
{
	m_a += m_b;
	if (m_a > 1)
	{
		m_a = 1.0f;
		m_b *= -1;
	}
	if (m_a < 0.3f)
	{
		m_a = 0.3f;
		m_b *= -1;
	}
	/*m_a += 1.0f;
	sin(DirectX::XMConvertToRadians(m_a)) * 300;
	if (m_a >= 360.0f)
	{
		m_a -= 360;
	}*/
}

void TitleScene::Release()
{
	m_titleTex.Release();
	m_startTex.Release();
}
