#include "CameraBase.h"

void CameraBase::Init()
{
	if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}
}

void CameraBase::Update()
{
	if (!m_spCamera)return;

	m_spCamera->SetCameraMatrix(m_mWorld);
}

void CameraBase::PreDraw()
{
	if (!m_spCamera)return;

	m_spCamera->SetToShader();
}

void CameraBase::UpdateRotateByMouse()
{
	POINT nowPos;
	GetCursorPos(&nowPos);

	POINT mouseMove{};
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	m_DegAng.x += mouseMove.y * 0.15f;
	m_DegAng.y += mouseMove.x * 0.15f;
	if (m_DegAng.x > 90)
		m_DegAng.x = 90;

	if (m_DegAng.x < -90)
		m_DegAng.x = -90;

	m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_DegAng.x)) * Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_DegAng.y));
}
