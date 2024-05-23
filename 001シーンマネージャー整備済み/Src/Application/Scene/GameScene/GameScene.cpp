#include "GameScene.h"

void GameScene::Init()
{
	m_pos = {};
	m_playerTex.Load("Asset/Textures/player.png");
}

void GameScene::Draw()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle rc;
	rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_playerTex,0,0,64,64,&rc);
}

void GameScene::Update()
{
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_pos.x += 5;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_pos.x -= 5;
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_pos.y += 5;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_pos.y -= 5;
	}

	Math::Matrix m_transMat;
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = m_transMat;
}

void GameScene::Release()
{
	m_playerTex.Release();
}
