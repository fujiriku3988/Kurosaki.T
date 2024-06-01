#include "GameScene.h"
#include"../SceneManager.h"
#include"Application/Object/Stage/Stage.h"
#include"Application/Object/Player/Player.h"
#include"Application/Object/Cannon/Cannon.h"
#include"Application/Object/Back/back.h"

void GameScene::Event()
{
	//プレイヤーの座標
	//一つ目①オブジェクトリストからプレイヤー情報を取得
	//二つ目②プレイヤー情報はゲームシーンが持っておく
	//今回は②で実装する
	  
	//カメラの処理
	Math::Vector3 playerPos;
	//m_playerに代入されているアドレス先はまだありますか？
	//expired 有効期限　yesORno
	if (m_player.expired() == false)
	{
		playerPos = m_player.lock()->GetPos();
	}
	Math::Vector3 cameraPos = { 3, 1.5f, -5.0f };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(cameraPos+ playerPos);
	m_camera->SetCameraMatrix(transMat);

}

void GameScene::Init()
{
	//カメラの実体化
	//unique_ptr コピーできない
	m_camera=std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(60);

	//ステージ===========================================
	//ポインタを作る（作っただけで使い物にならない）
	//ステージクラスを実体化（実体化させたアドレスをポインター）
	std::shared_ptr<Stage> _Stage = std::make_shared<Stage>();
	_Stage->Init();
	//オブジェクトリストに登録
	m_objList.push_back(_Stage);
	//キャノン
	std::shared_ptr<Cannon> _canoon = std::make_shared<Cannon>();
	m_objList.push_back(_canoon);
	//背景
	std::shared_ptr<back> _back = std::make_shared<back>();
	m_objList.push_back(_back);
	//プレイヤー===========================================
	std::shared_ptr<Player> _player = std::make_shared<Player>();
	m_objList.push_back(_player);
	m_player =_player;
}
