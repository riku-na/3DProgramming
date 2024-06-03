﻿#include "Terrain.h"

void Terrain::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Data/LessonData/Terrain/Terrain.gltf");

		//当たり判定用のコライダーを作成
		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("StageCollision", m_spModel, KdCollider::TypeGround);
	}
}

void Terrain::Update()
{
}

void Terrain::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel);
}

