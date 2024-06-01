#include "Player.h"
#include"../../Scene/SceneManager.h"

void Player::Update()
{
	//移動処理
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		//0.1だけだったらdouble型として認識される
		//ので、末尾に℉をつける
		m_pos.x -= 0.1f;
		m_anime += 0.1;

	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 0.1f;
		m_anime += 0.1;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_gravity = -0.1f;
	}
	//重力を反映
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;
	//アニメーション
	int Run[4] = { 24,25,24,26 };
	//m_anime+= 0.1;
	m_polygon.SetUVRect(Run[(int)m_anime]);
	if (m_anime >= 4)
	{
		m_anime = 0;
	}
}

void Player::PostUpdate()
{
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
	ray.m_type = KdCollider::TypeGround;

	//レイに当たったオブジェクト情報
	std::list<KdCollider::CollisionResult> retRayList;
	//レイと当たり判定＜ここ大切＞
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
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
	_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _transMat;

}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::Init()
{
	m_polygon.SetMaterial("Asset/Textures/char.png");
	m_pos = {-55,0,0};
	//画像分割
	m_polygon.SetSplit(6, 6);
	//原点変更
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
