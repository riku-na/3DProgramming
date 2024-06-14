#pragma once

class CameraBase :public KdGameObject
{
public:
	CameraBase() {}
	~CameraBase()override {}

	void Init() override;
	void Update() override;
	void PreDraw() override;

	void SetTarget(std::shared_ptr<KdGameObject> _target)
	{
		m_wpTarget=_target;
	}

protected:
	void UpdateRotateByMouse();

	std::shared_ptr<KdCamera> m_spCamera;

	std::weak_ptr<KdGameObject> m_wpTarget;

	Math::Matrix m_mLocalPos;
	Math::Matrix m_mRotation;

	POINT m_FixMousePos;
	Math::Vector3 m_DegAng;
};