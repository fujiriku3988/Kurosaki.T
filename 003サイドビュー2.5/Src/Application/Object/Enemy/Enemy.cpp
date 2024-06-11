#include "Enemy.h"
#include"../../Scene/SceneManager.h"

void Enemy::Update()
{
	//ポイントライト（天光源）
	//最大１００個まで(もっと出したいなら先生に相談)
	//毎フレーム追加する必要がある（毎フレームリセットされるため）
	Math::Vector3 tmpPos = { 0,0.5,0 };
	//																	↓色、↓半径	↓座標
	KdShaderManager::Instance().WorkAmbientController().AddPointLight({ 3,3,3 }, 5, m_pos+tmpPos, true);

	if (m_goal >= 5)
	{
		m_goal = 0;
		m_dir *= -1;
	}
	m_pos.x += m_movePow * m_dir;
	m_goal += m_movePow;

	//重力を反映
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	//アニメーション
	int walk[4] = { 3,4,3,5 };
	m_anime+= 0.05f;
	m_polygon.SetUVRect(walk[(int)m_anime]);
	if (m_anime >= 4)
	{
		m_anime = 0;
	}
}

void Enemy::PostUpdate()
{
	//自分自身の当たり判定エリア
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3{ 0,0.5f,0 }, 0.2f, kGreenColor);


	//==========================================================
	//当たり判定ステージ（レイ判定）
	//==========================================================

	//レイ判定用の変数を作成
	KdCollider::RayInfo ray;//レイの情報
	//レイの発射位置（座標）を設定
	ray.m_pos = m_pos;//足元

	//レイの発射方向を設定
	//ray.m_dir = { 0,-1,0 };
	//Math::Vector3::Down=={ 0,-1,0 }
	ray.m_dir = Math::Vector3::Down;//真下

	//少し高いところから飛ばす
	ray.m_pos.y += 0.1f;

	//段差の許容範囲を設定
	float enableStepHigh = 0.2f;
	ray.m_pos.y += enableStepHigh;

	//レイの長さを設定
	ray.m_range = m_gravity + enableStepHigh;

	//当たり判定をしたい対応を設定
	ray.m_type = KdCollider::TypeGround ;

	//レイに当たったオブジェクト情報
	std::list<KdCollider::CollisionResult> retRayList;
	//レイと当たり判定＜ここ大切＞
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//自分とは当たり判定をしない
		if (obj.get() == this)
		{
			continue;
		}

		obj->Intersects(ray, &retRayList);
	}

	//デバッグ（レイを可視化）
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);//はじめ、終わり、長さ、色

	//レイリストから一番近いオブジェクトを検出
	float maxOverLap = 0;		//はみ出た例の長さ
	Math::Vector3 hitPos;		//レイが遮断された座標（当たった座標）
	bool ishit = false;			//当たっていたらレイ
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
		m_pos = hitPos + Math::Vector3(0, -0.1f, 0);
		m_gravity = 0.0f;
	}

	//==========================================================
	//球判定
	//==========================================================
	//球判定用の変数を作成
	KdCollider::SphereInfo sphere;//スフィア
	//球の中心位置を設定
	sphere.m_sphere.Center = m_pos + Math::Vector3{ 0,0.5,0 };
	//球の半径を設定
	sphere.m_sphere.Radius = 0.3f;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround;
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);
	//球が当たったオブジェクトの情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;
	//球と当たり判定！！！！！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(sphere, &retSphereList);
	}
	//球リストから一番近いオブジェクトを検出
	maxOverLap = 0;		//はみ出た例の長さ
	Math::Vector3 hitDir = {};		//レイが遮断された方向（当たった方向）
	ishit = false;			//当たっていたらレイ
	for (auto& ret : retSphereList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;//当たった方向
			ishit = true;
		}

	}
	if (ishit)
	{
		//z方向無効
		hitDir.z = 0;

		//方向ベクトルは長さ１にする必要がある 
		hitDir.Normalize();
		//押し戻し
		m_pos += hitDir * maxOverLap;
	}

	//座標更新
	Math::Matrix _transMat;
	Math::Matrix scaleMat;
	_transMat = Math::Matrix::CreateTranslation(m_pos);
	scaleMat = Math::Matrix::CreateScale(m_dir,1,1);
	m_mWorld = scaleMat * _transMat;
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon,m_mWorld);
}

void Enemy::Init()
{
	m_polygon.SetMaterial("Asset/Textures/char.png");
	m_pos = { -20,0,0 };
	//画像分割
	m_polygon.SetSplit(6, 6);
	//原点変更
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	m_movePow = 0.01f;
	//当たり判定を設定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyCollision", { 0,0.5f,0 }, 0.2f, KdCollider::TypeBump);
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
