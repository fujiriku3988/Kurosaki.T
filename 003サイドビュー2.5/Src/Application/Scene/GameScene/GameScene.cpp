#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Stage/Stage.h"
#include"../../Object/Player/Player.h"

void GameScene::Event()
{
	/*if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}*/

	//プレイヤーの座標が必要
	//①ObjListからプレイヤーの情報をもらう
	//②プレイヤー情報はゲームシーンが持っておく
	//今回は②で実装します。


	//カメラ処理
	Math::Vector3 playerPos;
	//m_playerに代入されてるアドレス先はありますか？
	//expired 有効期限
	//true消えてる、false消えてない
	if (m_player.expired() == false) { playerPos = m_player.lock()->GetPos(); }

	m_camera = std::make_unique<KdCamera>();
	Math::Vector3 cameraPos = { 2.5f,1.5f,-5.0f };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(cameraPos + playerPos);
	m_camera->SetCameraMatrix(transMat);

}

void GameScene::Init()
{
	//m_camera->SetProjectionMatrix(60);

	//ポインタを作って実体化
	std::shared_ptr<Stage>stage = std::make_shared<Stage>();
	//stage->Init();
	m_objList.push_back(stage);
	
	//プレイヤー
	std::shared_ptr<Player>player = std::make_shared<Player>();
	//m_player->Init();
	m_objList.push_back(player);
	m_player = player;
}
