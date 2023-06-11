#include "GameWorld.hpp"
#include <cassert>
#include "Plant.hpp"
#include "Seed.hpp"
#include "Zombie.hpp"
//
GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init() {
  // YOUR CODE HERE
	SetSun(InitSun);
	SetWave(InitWave);

	//m_objects.emplace_back(std::make_shared<GameObject>(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, ANIMID_NO_ANIMATION, GameObject::ObjectType::Others));
	m_objects.emplace_back(std::make_shared<Background>());

	m_objects.emplace_front(std::make_shared<SunFlowerSeed>(shared_from_this()));
	m_objects.emplace_front(std::make_shared<PeaSeed>(shared_from_this()));
	m_objects.emplace_front(std::make_shared<WallnutSeed>(shared_from_this()));
	m_objects.emplace_front(std::make_shared<CherrySeed>(shared_from_this()));
	m_objects.emplace_front(std::make_shared<RepeaterSeed>(shared_from_this()));
	m_objects.emplace_front(std::make_shared<Shovel>(shared_from_this()));

	//m_objects.emplace_front(std::make_shared<ZombieSeed>(shared_from_this()));
	for (auto i = 0; i < GAME_COLS; i++)
	{
		for (auto j = 0; j < GAME_ROWS; j++)
		{
			m_objects.emplace_front(std::make_shared<PlantSpot>(FIRST_COL_CENTER + i * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + LAWN_GRID_HEIGHT * j, shared_from_this()));
		}
	}
}

LevelStatus GameWorld::Update() {
  // YOUR CODE HERE
	m_SunCountDown--;
	if (m_SunCountDown == 0)
	{
		m_SunCountDown = SunCountInterval;

		m_objects.emplace_front(std::make_shared<SunSky>(randInt(SunSky::MinX, SunSky::MaxX), WINDOW_HEIGHT - 1, randInt(SunSky::MinFallTime, SunSky::MaxFallTime), shared_from_this()));
	}
	
	m_ZombieCountDown--;
	if (m_ZombieCountDown == 0)
	{
		int ZombieCreateTime = 600 - 20 * GetWave();
		m_ZombieCountDown = ZombieMinCreateTime > ZombieCreateTime ? ZombieMinCreateTime : ZombieCreateTime;

		int ZombieNum = (15 + GetWave()) / 10;

		static int const ProbabilityRegular_Zombie = 20;
		int ProbabilityPole_Vaulting_Zombie = 2 * (GetWave() - 8 > 0 ? GetWave() - 8 : 0);
		int ProbabilityBucket_Head_Zombie = 3 * (GetWave() - 15 > 0 ? GetWave() - 15 : 0);

		while (ZombieNum > 0) {
			ZombieNum--;
			int m_Probability = randInt(0, ProbabilityRegular_Zombie + ProbabilityPole_Vaulting_Zombie + ProbabilityBucket_Head_Zombie);
			if (m_Probability <= ProbabilityRegular_Zombie) {
				m_objects.emplace_front(std::make_shared<RegularZombie>(randInt(Zombie::MinX, Zombie::MaxX), Zombie::PossibleY[randInt(0, 4)], shared_from_this()));
			}
			else if (m_Probability <= ProbabilityRegular_Zombie + ProbabilityPole_Vaulting_Zombie) {
				m_objects.emplace_front(std::make_shared<PoleZombie>(randInt(Zombie::MinX, Zombie::MaxX), Zombie::PossibleY[randInt(0, 4)], shared_from_this()));
			}
			else {
				m_objects.emplace_front(std::make_shared<BucketZombie>(randInt(Zombie::MinX, Zombie::MaxX), Zombie::PossibleY[randInt(0, 4)], shared_from_this()));
			}
		}
		SetWave(GetWave() + 1);
	}

	for (auto item = m_objects.begin(); item != m_objects.end();)
	{

		(*item)->Update();
		if (GameObject::Status::Dead == (*item)->GetStatus())
		{
			item = m_objects.erase(item);
		}
		else
		{
			item++;
		}
	}
	for (auto item = m_objects.begin(); item != m_objects.end(); item++)
	{
		if (GameObject::ObjectType::Zombie == (*item)->GetType() && (*item)->GetStatus() == GameObject::Status::Alive)
		{
			if ((*item)->GetX() <= 0)
			{
				return LevelStatus::LOSING;
			}
			for (auto other = m_objects.begin(); other != m_objects.end(); other++)
			{
				if ((*other)->GetType() != GameObject::ObjectType::Others && (*other)->GetType() != GameObject::ObjectType::Zombie && (*other)->GetStatus() == GameObject::Status::Alive)
				{
					if (isCollide((*other), (*item)))
					{
						(*item)->addCollided((*other));
						(*other)->addCollided((*item));
					}
				}
			}
		}
	}

	for (auto item = m_objects.cbegin(); item != m_objects.cend();item++)
	{
		(*item)->Colliding();
	}

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  // YOUR CODE HERE
	m_objects.clear();
}

bool GameWorld::existZombie(int x, int y)
{
	for (auto item = m_objects.begin(); item != m_objects.end(); item++)
	{
		if (y == (*item)->GetY() && (*item)->GetType() == GameObject::ObjectType::Zombie && (*item)->GetX() > x)
		{
			return true;
		}
	}
	return false;
}


bool GameWorld::isCollide(pGameObject object1, pGameObject object2)
{	
	if ((object1->GetUpEdge() > object2->GetDownEdge() && object1->GetDownEdge() < object2->GetUpEdge()) || (object2->GetUpEdge() > object1->GetDownEdge() && object2->GetDownEdge() < object1->GetUpEdge()))
	{
		if (object1->GetX() <= object2->GetX())
		{
			if (object1->GetRightEdge() > object2->GetLeftEdge() && object1->GetLeftEdge() < object2->GetRightEdge())
			{
				return true;
			}
		}
		else
		{
			if (object2->GetRightEdge() > object1->GetLeftEdge() && object2->GetLeftEdge() < object1->GetRightEdge())
			{
				return true;
			}

		}
	}
	return false;
}

void GameWorld::EraseDead()
{
	for (auto item = m_objects.begin(); item != m_objects.end();)
	{
		if (GameObject::Status::Dead == (*item)->GetStatus())
		{
			item = m_objects.erase(item);
		}
		else
		{
			item++;
		}
	}
}