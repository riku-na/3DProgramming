#include "HamuHamu.h"

HamuHamu::HamuHamu()
{
}

HamuHamu::~HamuHamu()
{
}

void HamuHamu::Init()
{
	//===================================================================
	// ハムスター初期化
	//===================================================================
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}

void HamuHamu::Update()
{
	//ハム太郎の更新
	{
		float moveSpd = 0.05f;
		Math::Vector3 nowPos = m_mWorld.Translation();

		Math::Vector3 moveVec = Math::Vector3::Zero;

		if (GetAsyncKeyState('W') & 0x8000)
			moveVec.z = 1.0f;

		if (GetAsyncKeyState('S'))
			moveVec.z = -1.0f;

		if (GetAsyncKeyState('A'))
			moveVec.x = -1.0f;

		if (GetAsyncKeyState('D'))
			moveVec.x = 1.0f;

		moveVec.Normalize();
		moveVec *= moveSpd;
		nowPos += moveVec;

		Math::Matrix _hamuTransMat = Math::Matrix::CreateTranslation(nowPos.x, nowPos.y, nowPos.z);

		m_mWorld = _hamuTransMat;
	}
}

void HamuHamu::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}
