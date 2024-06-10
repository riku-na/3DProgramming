#pragma once

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;
	void DrawSprite()		override;

private:
	Math::Vector3 m_pos;
	Math::Vector3 m_nextPos;

	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;
	KdTexture m_tex;
	Math::Vector3 m_circlePos{};
};

static inline float Lerp(float a, float b, float t)
{
	return a + (t) * (b - a);
}