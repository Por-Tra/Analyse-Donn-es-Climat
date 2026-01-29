#pragma once


class Cpoint
{
public:
	Cpoint();
	Cpoint(float x, float y);
	Cpoint(const Cpoint& other);

	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }

private:
		float m_x;
		float m_y;

}

