#include "SceneManager.h"
#include"TitleScene/TitleScene.h"
#include"GameScene/GameScene.h"

void SceneManager::PreUpdate()
{
	//シーン切り替え
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void SceneManager::Release()
{

}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	//次のシーンを作成し、現在のシーンにする
	switch (_sceneType)
	{
	case SceneManager::Title:
		//タイトルシーンを実体化
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneManager::Game:
		//ゲームシーンを実体化
		m_currentScene = std::make_shared<GameScene>();
		break;
	}

	//シーン管理変数を更新
	m_currentSceneType = _sceneType;
}
