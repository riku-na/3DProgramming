#include "TrackingCamera.h"

void TrackingCamera::Init()
{
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 6.f, -5.f);

	m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));

	CameraBase::Init();
}

void TrackingCamera::Update()
{
	Math::Matrix _targetMat = Math::Matrix::Identity;

	const std::shared_ptr<const KdGameObject>_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	m_mWorld = m_mRotation * m_mLocalPos * _targetMat;


	CameraBase::Update();
}

void TrackingCamera::PreDraw()
{
	CameraBase::PreDraw();
}
