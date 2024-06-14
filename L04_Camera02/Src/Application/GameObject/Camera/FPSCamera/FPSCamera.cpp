#include "FPSCamera.h"

void FPSCamera::Init()
{
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, 0.f);

	m_FixMousePos.x = 640;
	m_FixMousePos.y = 320;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void FPSCamera::Update()
{
	Math::Matrix _targetMat = Math::Matrix::Identity;

	const std::shared_ptr<const KdGameObject>_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	m_mWorld = m_mRotation * m_mLocalPos * _targetMat;


	UpdateRotateByMouse();
	m_mWorld = m_mRotation * m_mLocalPos * _targetMat;

	CameraBase::Update();
}

void FPSCamera::PreDraw()
{
	CameraBase::PreDraw();
}
