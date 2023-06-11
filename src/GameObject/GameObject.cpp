#include "GameObject.hpp"
#include "Plant.hpp"
#include "Seed.hpp"
#include "Zombie.hpp"

void Sun::Update()
{
	GameObject::Update();
	if(!(m_falltime < VanishTime))
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
	const int acrate = -1;
	if (m_falltime > 1)
	{
		m_falltime--;
		MoveTo(GetX() - 1, GetY() + m_speed);
		m_speed += acrate;
	}
	else { Sun::Update(); }
}

void SunSky::Update()
{
	int speed = 2;
	if (m_falltime > 1)
	{
		m_falltime--;
		MoveTo(GetX(), GetY() - speed);
	}
	else
	{
		Sun::Update();
	}
}

void PlantSpot::OnClick()
{
	switch (m_world->GetFunction())
	{
	case FunctionName::PlantSunflower:
		m_world->AddObject(std::make_shared<SunFlower>(GetX(), GetY(), m_world));
		break;

	case FunctionName::PlantPea:
		m_world->AddObject(std::make_shared<Peashooter>(GetX(), GetY(), m_world));
		break;

	case FunctionName::PlantWallnut:
		m_world->AddObject(std::make_shared<Wallnut>(GetX(), GetY(), m_world));
		break;

	case FunctionName::PlantCherry:
		m_world->AddObject(std::make_shared<Cherry>(GetX(), GetY(), m_world));
		break;

	case FunctionName::PlantRepeater:
		m_world->AddObject(std::make_shared<Repeater>(GetX(), GetY(), m_world));
		break;

	case FunctionName::TestZombie:
		m_world->AddObject(std::make_shared<PoleZombie>(GetX(), GetY(), m_world));
		break;

	default:
		break;
	}
	m_world->SetFunction(FunctionName::None);
}


void Shovel::OnClick()
{
	if (m_world->GetFunction() == FunctionName::None)
	{
		m_world->SetFunction(FunctionName::Shovel);
	}
	else if (m_world->GetFunction() == FunctionName::Shovel)
	{
		m_world->SetFunction(FunctionName::None);
	}
}



void CoolDown::Update()
{
	if (m_cooltime > 1)
	{
		m_cooltime--;
	}
	else
	{
		ChangeStatus();
	}
}

void CoolDown::OnClick()
{
	/*if (m_world->GetFunction() == m_covered)
	{
		ChangeStatus();
		m_world->SetSun(m_world->GetSun() + m_CoveredPrice);
		m_world->SetFunction(FunctionName::None);
	}*/
}


void Pea::Update()
{
	GameObject::Update();
	int speed = 8;
	MoveTo(GetX() + speed, GetY());
	if (GetX() >= WINDOW_WIDTH)
	{
		ChangeStatus();
	}
}

void Pea::Colliding()
{
}


void Boom::Update()
{
	GameObject::Update();
	if (m_time > 0)
	{
		m_time--;
	}
	else
	{
		ChangeStatus();
	}
}