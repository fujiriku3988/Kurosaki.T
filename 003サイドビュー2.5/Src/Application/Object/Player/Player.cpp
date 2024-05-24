#include "Player.h"
#include"../../Scene/SceneManager.h"

void Player::Update()
{
	//移動処理
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 0.1f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 0.1f;
	}

	//アニメーション
	int Run[4] = { 24,25,24,26 };
	m_polygon.SetUVRect(Run[(int)m_anime]);
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_pos.x -= 0.1f;
		m_anime += 0.05;
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_pos.x += 0.1f;
		m_anime += 0.05;
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}

	//int型でキャストすることで小数点を切り捨てるから
	//アニメーションがゆっくりになる	
	//m_polygon.SetUVRect((int)m_anime);
	//m_polygon.SetUVRect(0);

	//座標更新
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::PostUpdate()
{
	//===========================//
	//当たり判定（レイ判定）
	//===========================//

	//レイ判定用の変数を作成
	KdCollider::RayInfo ray;
	//レイの発射位置（座標）を指定
	ray.m_pos = m_pos;
	//レイの発射方法
	ray.m_dir = { 0,-1,0 };//真下
	//当たり判定したいタイプを設定
	ray.m_type = KdCollider::TypeGround;
	//レイに当たったオブジェクト情報
	std::list<KdCollider::CollisionResult>retRayList;
	//レイと当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retRayList);
	}
	//レイリストから一番近いオブジェクトを検出
	float maxOverLap = 0;
	Math::Vector3 hitPos;
	bool ishit = false;
	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			ishit = true;
		}
	}
	if (ishit)
	{
		//当たっている
	}
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::Init()
{
	m_polygon.SetMaterial("Asset/Textures/char.png");
	m_pos = {};
	m_anime = 0;
	//画像分割
	m_polygon.SetSplit(6, 6);
}
