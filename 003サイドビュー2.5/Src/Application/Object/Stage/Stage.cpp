#include "Stage.h"

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}

void Stage::Init()
{
	//データ読み込み
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/SideViewMap/SideViewMap.gltf");
	Math::Matrix scaleMat = Math::Matrix::CreateScale(5, 1, 1);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0,-2,0);
	//Math::Matrix scaleMat = Math::Matrix::CreateTranslation();
	m_mWorld = scaleMat* transMat;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageCollision", m_model, KdCollider::TypeGround);
}
