#include "Zombie.hpp"

void Zombie::Update()
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
	else if (num_plant == 0 && GetCurrentAnimation() != ANIMID_WALK_ANIM)
	{
		PlayAnimation(ANIMID_WALK_ANIM);
		m_speed = speed;
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