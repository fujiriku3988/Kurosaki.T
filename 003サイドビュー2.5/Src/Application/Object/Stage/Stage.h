﻿#pragma once

class Stage:public KdGameObject
{
public:
	Stage() { Init(); };
	~Stage()override {};

	void DrawLit()override;
	void Init()override;
private:

	std::shared_ptr<KdModelData> m_model;
};

