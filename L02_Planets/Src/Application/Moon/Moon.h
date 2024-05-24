#pragma once

class Moon
{
public:
	Moon();
	~Moon();

	void Update();
	void Draw();
private:
	float m_spinRadian = 0.0f;		//自転角度
	float m_revolutionRadian = 0.0f;	//公転角度

	static constexpr float SPIN_SPEED = DirectX::XMConvertToRadians(5);		//自転速度
	static constexpr float REVOLUTION_SPEED = DirectX::XMConvertToRadians(1);	//公転速度
	static constexpr float REVOLUTION_RADIUS =3;								//公転半径

	Math::Matrix m_mat;
	std::shared_ptr<KdModelData> m_model;
};