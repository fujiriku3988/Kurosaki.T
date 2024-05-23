#pragma once
#include"BaseScene/BaseScene.h"
class SceneManager
{
public:

	enum SceneType
	{
		Title,
		Game
	};

	//関数
	void PreUpdate();//更新処理の前にやりたい処理
	void Update();
	void Draw();
	

	//次のシーンを設定する関数
	//セッター
	void SetNextScene(SceneType _sceneType) { m_nextSceneType = _sceneType; }

	//次のシーンを取得する関数
	//ゲッター
	SceneType GetCurrentSceneType() { return m_currentSceneType; }
	//int GetCurrentSceneType() { return m_currentSceneType; }

	

private:

	void Init();
	void Release();
	//シーンを切り替える関数
	void ChangeScene(SceneType _sceneType);
	//変数

	//現在のシーンを管理しているポインタ
	std::shared_ptr<BaseScene> m_currentScene;

	//現在のしーんを管理している変数
	SceneType m_currentSceneType = SceneType::Title;

	//次のシーンを管理している変数
	SceneType m_nextSceneType = m_currentSceneType;

	//シングルトンパターン===============
	//そのクラスのインスタンスが１つしか生成されないことを保証するデザインパターン
private:

	SceneManager() { Init(); }
	~SceneManager() { Release(); }

public:

	static SceneManager& Instansce()
	{
		static SceneManager instance;//実体化
		return instance;
	}
};