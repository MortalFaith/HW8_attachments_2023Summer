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

	default:
		break;
	}
	m_world->SetFunction(FunctionName::None);
}


void Seed::OnClickTemplt(FunctionName functionname)
{
	if (int result = m_world->GetSun() - m_price; result >= 0 && m_world->GetFunction() == FunctionName::None)
	{
		m_world->SetSun(result);
		m_world->AddObject(std::make_shared<CoolDown>(GetX(), GetY(), m_CoolTime));
		m_world->SetFunction(functionname);
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

void Plant::Update()
{
	if (m_HP <= 0)
	{
		ChangeStatus();
		return;
	}
}

void Plant::OnClick()
{
	return;
}

int Plant::Getm_HP() const {
	return m_HP;
}

void SunFlower::Update()
{
	Plant::Update();
	if (m_CoolTime > 0)
	{
		m_CoolTime--;
	} 
	else
	{
		m_CoolTime = SunFlowerInterval;
		m_world->AddObject(std::make_shared<SunOfFlower>(GetX(), GetY(), m_world));
	}
}

void Peashooter::Update()
{
	Plant::Update();
	if (m_CoolTime > 0)
	{
		m_CoolTime--;
	}
	else
	{
		if (m_world->existZombie(GetX(),GetY()) == true)
		{
			m_world->AddObject(std::make_shared<Pea>(GetX()+ PeaCreateOffsetX, GetY() + PeaCreateOffsetY, m_world));
			m_CoolTime = PeashooterInterval;
		}
	}
}


void Pea::Update()
{
	int speed = 8;
	MoveTo(GetX() + speed, GetY());
	if (GetX() > WINDOW_WIDTH)
	{
		ChangeStatus();
	}
}

void Zombie::Update() 
{
	if (m_HP <= 0)
	{
		ChangeStatus();
		return;
	}
}

void Zombie::Collide()
{
	//TODO
	return;
}


void Regular_Zombie::Update()
{
	Zombie::Update();
	MoveTo(GetX() - 1, GetY());
}

void Regular_Zombie::Collide()
{
	Zombie::Collide();
}

void Bucket_Head_Zombie::Update()
{
	Zombie::Update();
	MoveTo(GetX() - 1, GetY());
	if (Getm_HP() < 200) {
		ChangeImage(IMGID_REGULAR_ZOMBIE);
	}
}

void Bucket_Head_Zombie::Collide()
{
	Zombie::Collide();
}

void Pole_Vaulting_Zombie::Update()
{
	Zombie::Update();
	MoveTo(GetX() - 1, GetY());
}

void Pole_Vaulting_Zombie::Collide()
{
	Zombie::Collide();
}