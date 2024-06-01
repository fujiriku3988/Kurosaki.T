#include "back.h"

void back::Init()
{
	m_polygon.SetMaterial("Asset/Textures/back.png");
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(0, 5, 50);
	Math::Matrix _scaleMat = Math::Matrix::CreateScale(300, 100, 1);
	m_mWorld = _scaleMat * _transMat;
}

void back::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
