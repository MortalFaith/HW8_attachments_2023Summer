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
		m_world->AddObject(std::make_shared<RegularZombie>(GetX(), GetY(), m_world));
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

/*
void Seed::OnClickTemplt(FunctionName functionname)
{
	if (int result = m_world->GetSun() - m_price; result >= 0 && m_world->GetFunction() == FunctionName::None)
	{
		m_world->SetSun(result);
		m_world->AddObject(std::make_shared<CoolDown>(GetX(), GetY(), m_CoolTime, functionname,m_price ,m_world));
		m_world->SetFunction(functionname);
	}
}*/


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
/*
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
}*/


void Pea::Update()
{
	GameObject::Update();
	static int speed = 8;
	MoveTo(GetX() + speed, GetY());
	if (GetX() >= WINDOW_WIDTH)
	{
		ChangeStatus();
	}
}

void Pea::Colliding()
{
	for (auto item = collidedBegin(); item != collidedEnd(); item++)
	{
		if ((*item)->GetStatus() == GameObject::Status::Alive)
		{
			ChangeStatus();
			return;
		}
	}
}
/*
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
}*/

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
/*
void Repeater::Update()
{
	Plant::Update();
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
}*/


/* void Zombie::Update()
{
	GameObject::Update();
	if (m_HP <= 0 || GetX() <= 0)
	{
		ChangeStatus();
		return;
	}
	MoveTo(GetX() - m_speed, GetY());
	
}

void Zombie::Colliding(int speed)
{
	if (isCollideEmpty() && GetCurrentAnimation() != ANIMID_WALK_ANIM)
	{
		PlayAnimation(ANIMID_WALK_ANIM);
		m_speed = speed;
	}
	else if (!isCollideEmpty())
	{
		int num_plant = 0;
		for (auto item = collidedBegin(); item != collidedEnd(); item++)
		{
			m_HP -= (*item)->GetDamage();
			if (m_HP <= 0)
			{
				ChangeStatus();
				return;
			}
			if ((*item)->GetType() == ObjectType::Plant)
			{
				num_plant++;
			}
		}
		if (num_plant != 0 && GetCurrentAnimation() != ANIMID_EAT_ANIM)
		{
			PlayAnimation(ANIMID_EAT_ANIM);
			m_speed = 0;
		}
	}
}



void BucketZombie::Update()
{
	Zombie::Update();
	if (m_HP == ZombieHP)
	{
		ChangeImage(IMGID_REGULAR_ZOMBIE);
	}
}

void PoleZombie::Update()
{
	if(m_AnimPlayingtime == PoleZombieAnimPlaytime)
	{
		Zombie::Update();
	}
	else if(m_AnimPlayingtime != 0)
	{
		m_AnimPlayingtime--;
		GameObject::Update();
	}
	else if(m_AnimPlayingtime == 0)
	{
		GameObject::Update();
		m_speed = PoleZombieWalkSpeed;
		m_isRunning = false;
		m_AnimPlayingtime = PoleZombieAnimPlaytime;
		PlayAnimation(ANIMID_WALK_ANIM);
		MoveTo(GetX() - PoleZombieJumpX, GetY());
	}
}

int PoleZombie::GetLeftEdge()
{
	if (m_isRunning)
	{
		return GameObject::GetLeftEdge() - JumpTestX;
	}
	else
	{
		return GameObject::GetLeftEdge();
	}
}

int PoleZombie::GetRightEdge()
{
	if (m_isRunning)
	{
		return GameObject::GetRightEdge() - JumpTestX;
	}
	else
	{
		return GameObject::GetRightEdge();
	}
}

void PoleZombie::Colliding()
{
	if (m_isRunning)
	{
		int num_plant = 0;
		for(auto item = collidedBegin(); item != collidedEnd(); item ++)
		{
			m_HP -= (*item)->GetDamage();
			if (m_HP <= 0)
			{
				ChangeStatus();
				return;
			}
			if ((*item)->GetType() == ObjectType::Plant)
			{
				num_plant++;
			}
		}
		if (num_plant != 0 && m_AnimPlayingtime == PoleZombieAnimPlaytime)
		{
			m_speed = 0;
			m_AnimPlayingtime--;
			PlayAnimation(ANIMID_JUMP_ANIM);
		}
	}
	else
	{
		Zombie::Colliding(PoleZombieWalkSpeed);
	}
}
*/