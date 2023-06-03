#include "GameObject.hpp"

void Sun::Update()
{
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
	int speed = 4;
	const int acrate = -1;
	if (m_falltime > 1)
	{
		m_falltime--;
		MoveTo(GetX() + speed, GetY() - 1);
		speed -= acrate;
	}
	Sun::Update();
}

void SunSky::Update()
{
	if (m_falltime > 1)
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

	case FunctionName::PlantWallnut:
		m_world->AddObject(std::make_shared<Wallnut>(GetX(), GetY(), m_world));
		break;

	case FunctionName::PlantCherry:
		m_world->AddObject(std::make_shared<Cherry>(GetX(), GetY(), m_world));
		break;

	case FunctionName::PlantRepeater:
		m_world->AddObject(std::make_shared<Repeater>(GetX(), GetY(), m_world));
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


void Seed::OnClickTemplt(FunctionName functionname)
{
	if (int result = m_world->GetSun() - m_price; result >= 0 && m_world->GetFunction() == FunctionName::None)
	{
		m_world->SetSun(result);
		m_world->AddObject(std::make_shared<CoolDown>(GetX(), GetY(), m_CoolTime, functionname,m_price ,m_world));
		m_world->SetFunction(functionname);
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
	if (m_world->GetFunction() == m_covered)
	{
		ChangeStatus();
		m_world->SetSun(m_world->GetSun() + m_CoveredPrice);
		m_world->SetFunction(FunctionName::None);
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
	if (m_world->GetFunction() == FunctionName::Shovel)
	{
		ChangeStatus();
		m_world->SetFunction(FunctionName::None);
	}
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
	if (m_CoolTime > 1)
	{
		m_CoolTime--;
	}
	else
	{
		if (m_world->existZombie(GetY()) == true)
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

void Wallnut::Update()
{
	Plant::Update();
	if (!m_isCracked && m_HP < WallnutChangeHP)
	{
		ChangeImage(IMGID_WALLNUT_CRACKED);
		m_isCracked = true;
	}
}

void Cherry::Update()
{
	Plant::Update();  // unnecessary
	if (m_BoomTime > 1)
	{
		m_BoomTime--;
	}
	else
	{
		ChangeStatus();
		m_world->AddObject(std::make_shared<Boom>(GetX(), GetY(), m_world));
	}
}

void Boom::Update()
{
	if (m_time > 0)
	{
		m_time--;
	}
	else
	{
		ChangeStatus();

	}
}

void Repeater::Update()
{
	if (m_ShootCoolTime > 0)
	{
		m_ShootCoolTime--;
	}
	else if(m_ShootCoolTime < 0)
	{
		if (m_ShootCoolTime >= PeaInterval)
		{
			m_ShootCoolTime--;
		}
		else if (m_ShootCoolTime < PeaInterval)
		{
			m_world->AddObject(std::make_shared<Pea>(GetX() + RepeaterOffsetX, GetY() + RepeaterOffsetY, m_world));
			m_ShootCoolTime = RepeaterInterval;
		}
	}
	else if (m_ShootCoolTime == 0)
	{
		m_world->AddObject(std::make_shared<Pea>(GetX() + RepeaterOffsetX, GetY() + RepeaterOffsetY, m_world));
		m_ShootCoolTime--;
	}
}