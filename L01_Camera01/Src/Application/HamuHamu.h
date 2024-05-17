﻿#pragma once

class HamuHamu :public KdGameObject
{
public: 
	HamuHamu();
	~HamuHamu()override;

public:
	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	//板ポリゴン
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;
	//Math::Matrix m_mHamuWorld = Math::Matrix::Identity;
	//Math::Vector3 m_HamuPos;
};