#include "Moon.h"
#include "../main.h"
#include "../Earth/Earth.h"

Moon::Moon()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Data/LessonData/Planets/moon.gltf");
}

Moon::~Moon()
{
}

void Moon::Update()
{
	m_spinRadian += SPIN_SPEED;
	m_revolutionRadian += REVOLUTION_SPEED;

	m_mat = Math::Matrix::CreateRotationY(m_spinRadian);
	m_mat *= Math::Matrix::CreateTranslation(REVOLUTION_RADIUS, 0, 0);
	m_mat *= Math::Matrix::CreateRotationY(m_revolutionRadian);
	m_mat *= Application::Instance().GetEarth()->GetMatrix();
}

void Moon::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mat);
}
