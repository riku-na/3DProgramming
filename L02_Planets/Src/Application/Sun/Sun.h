#pragma once

class Sun
{
public:
	Sun();
	~Sun();

	void Draw();
private:
	std::shared_ptr<KdModelData> m_model;
};