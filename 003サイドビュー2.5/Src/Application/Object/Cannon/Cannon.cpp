#include "Cannon.h"

void Cannon::DrawLit()
{
	//表示
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}

void Cannon::Init()
{
	m_model = std::make_shared< KdModelData>();
	//データ読み込み
	m_model->Load("Asset/Models/Cannon2/Cannon.gltf");
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(-1, -4, 0);
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(1,1,1);
	Math::Matrix rotMat;
	rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));

	m_mWorld = scaleMat * rotMat*transMat;
	//当たり判定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("CannonCollison",m_model,KdCollider::TypeGround);
}
