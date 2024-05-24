#include "Earth.h"

Earth::Earth()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Data/LessonData/Planets/earth.gltf");
}

Earth::~Earth()
{
}

void Earth::Update()
{
	m_spinRadian += SPIN_SPEED;
	m_revolutionRadian += REVOLUTION_SPEED;

	m_mat = Math::Matrix::CreateRotationY(m_spinRadian);
	m_mat *= Math::Matrix::CreateTranslation(REVOLUTION_RADIUS, 0, 0);
	m_mat *= Math::Matrix::CreateRotationY(m_revolutionRadian);
}

void Earth::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mat);
}
