#include "Plant.hpp"
//#include "GameObject.hpp"
//#include "ObjectBase.hpp"

using pGameWorld = std::shared_ptr<GameWorld>;

/*void PlantSpot::OnClick()
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
}*/

void Plant::Update()
{
	GameObject::Update();
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

void Plant::Colliding()
{
	for (auto item = collidedBegin(); item != collidedEnd(); item++)
	{
		m_HP -= (*item)->GetDamage();
		if (m_HP <= 0)
		{
			return;
		}
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
		if (m_world->existZombie(GetX(), GetY()) == true)
		{
			m_world->AddObject(std::make_shared<Pea>(GetX()+ PeaCreateOffsetX, GetY() + PeaCreateOffsetY, m_world));
			m_CoolTime = PeashooterInterval;
		}
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
	if (m_BoomTime > 0)
	{
		m_BoomTime--;
	}
	else
	{
		ChangeStatus();
		m_world->AddObject(std::make_shared<Boom>(GetX(), GetY(), m_world));
	}
}

void Repeater::Update()
{
	if (m_ShootCoolTime > 0)
	{
		m_ShootCoolTime--;
	}
	else if(m_ShootCoolTime == 0 && m_world->existZombie(GetX(), GetY()))
	{
		m_world->AddObject(std::make_shared<Pea>(GetX() + RepeaterOffsetX, GetY() + RepeaterOffsetY, m_world));
		m_ShootCoolTime--;
	}
	else if (m_ShootCoolTime < 0)
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
}
