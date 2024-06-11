#include "GameScene.h"
#include"../SceneManager.h"
#include"Application/Object/Stage/Stage.h"
#include"Application/Object/Player/Player.h"
#include"Application/Object/Cannon/Cannon.h"
#include"Application/Object/Back/back.h"
#include"Application/Object/Enemy/Enemy.h"

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
	Math::Matrix transMat = Math::Matrix::CreateTranslation(cameraPos + playerPos);
	m_camera->SetCameraMatrix(transMat);

	//被写界深度
	//m_camera->SetFocus(5, 1, 8);

	//ブルーム(ちょっとぼかす加算合成)
	//KdShaderManager::Instance().m_postProcessShader.SetBrightThreshold(0.7);
}

void GameScene::Init()
{
	//カメラの実体化
	//unique_ptr コピーできない
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(60);

	//影の方向を変えたいときは触る
	//平行光（ディレクショナルライト）								↓方向↓色
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({0,-30,0.1f}, {3,3,3});

	//KdShaderManager::Instance().WorkAmbientController().

	//画面全体が暗いときに触る
	//環境光（アンビエントライト）
	//デフォルトは0.3
	//KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 1,1,1,1 });

	//フォグ（霧）													距離	高さ
	//KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
	//距離フォグ														↓霧の色	↓密度
	KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 1,1,1 }, 0.01);
	//高さフォグ														↓色	↓上↓下↓カメラとの距離
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1,1,1 }, 0, -2, 0);

	//ステージ===========================================
	//ポインタを作る（作っただけで使い物にならない）
	//ステージクラスを実体化（実体化させたアドレスをポインター）
	//奥に５つ
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<Stage> stage = std::make_shared<Stage>();
		stage->Init();
		stage->SetPos({ 0.0f, -2.0f, i * 3.0f });
		//オブジェクトリストに登録
		m_objList.push_back(stage);
		//for (int j = 0; j < 5; j++)
		//{
		//	std::shared_ptr<Stage> stage = std::make_shared<Stage>();
		//	stage->Init();
		//	stage->SetPos({ 0.0f, -2.0f + j * 5.0f, 0.0f });
		//	//オブジェクトリストに登録
		//	m_objList.push_back(stage);
		//}
	}
	//縦に５つ
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<Stage> stage = std::make_shared<Stage>();
		stage->Init();
		stage->SetPos({ 0.0f, -2.0f + i * 5.0f, 0.0f });
		//オブジェクトリストに登録
		m_objList.push_back(stage);
	}
	//キャノン
	std::shared_ptr<Cannon> _canoon = std::make_shared<Cannon>();
	m_objList.push_back(_canoon);
	//背景
	std::shared_ptr<back> _back = std::make_shared<back>();
	m_objList.push_back(_back);
	//プレイヤー===========================================
	std::shared_ptr<Player> _player = std::make_shared<Player>();
	m_objList.push_back(_player);
	m_player = _player;
	//エネミー
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<Enemy>enemy = std::make_shared<Enemy>();
		enemy->SetPosE(Math::Vector3(-25 + i, 0, 0));
		AddObject(enemy);
	}
}
