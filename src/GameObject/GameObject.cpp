#include "GameObject.hpp"

void Sun::Update()
{
	if(!(m_falltime < -300))
	{
		m_falltime--;
	}
	else
	{
		ChangeStatus();
	}
}

void Sun::OnClick()
{
	ChangeStatus();
	m_world->SetSun(m_world->GetSun() + SunValue);
}

void SunOfFlower::Update()
{
	int speed = 4;
	const int acrate = -1;
	if (m_falltime >= 0)
	{
		m_falltime--;
		MoveTo(GetX() + speed, GetY() - 1);
		speed -= acrate;
	}
	Sun::Update();
}

void SunSky::Update()
{
	if (m_falltime >= 0)
	{
		m_falltime--;
		MoveTo(GetX(), GetY() - 2);
	}
	Sun::Update();
}


void Seed::OnClickTemplt()
{
	if (int result = m_world->GetSun() - m_price; result >= 0)
	{
		m_world->SetSun(result);
		m_world->AddObject(std::make_shared<CoolDown>(GetX(), GetY(), m_CoolTime));
	}
}

void CoolDown::Update()
{
	if (m_cooltime > 0)
	{
		m_cooltime--;
	}
	else
	{
		ChangeStatus();
	}
}



