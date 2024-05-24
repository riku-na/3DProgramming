#include "Sun.h"

Sun::Sun()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Data/LessonData/Planets/sun.gltf");
}

Sun::~Sun()
{
}

void Sun::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model);
}
