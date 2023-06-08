#include "GameWorld.hpp"

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init() {
  // YOUR CODE HERE
	SetSun(InitSun);
	SetWave(InitWave);
	std::srand(time(NULL));

	m_objects.emplace_front(std::make_shared<Background>());
	m_objects.emplace_front(std::make_shared<SunFlowerSeed>(shared_from_this()));
	m_objects.emplace_front(std::make_shared<PeaSeed>(shared_from_this()));
	m_objects.emplace_front(std::make_shared<WallnutSeed>(shared_from_this()));
	m_objects.emplace_front(std::make_shared<CherrySeed>(shared_from_this()));
	m_objects.emplace_front(std::make_shared<RepeaterSeed>(shared_from_this()));
	m_objects.emplace_front(std::make_shared<Shovel>(shared_from_this()));

	m_objects.emplace_front(std::make_shared<ZombieSeed>(shared_from_this()));

	for (int i = 0; i < GAME_ROWS; i++)
	{
		for (int j = 0; j < GAME_COLS; j++)
		{
			m_objects.emplace_front(std::make_shared<PlantSpot>(FIRST_COL_CENTER + LAWN_GRID_WIDTH * j, FIRST_ROW_CENTER + LAWN_GRID_HEIGHT * i,shared_from_this()));
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
		if (GameObject::ObjectType::Zombie == (*item)->GetType())
		{
			for (auto other = m_objects.begin(); other != m_objects.end(); other++)
			{
				if ((*other)->GetType() != GameObject::ObjectType::Others && (*other)->GetType() != GameObject::ObjectType::Zombie)
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

	for (auto item = m_objects.begin(); item != m_objects.end(); item++)
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
		if (y == (*item)->GetY() && (*item)->GetType() == GameObject::ObjectType::Zombie && ((*item)->GetX() + (*item)->GetWidth() / 2) > x)
		{
			return true;
		}
	}
	return false;
}


bool GameWorld::isCollide(pGameObject object1, pGameObject object2)
{
	if (object1->GetX() <= object2->GetX())
	{
		if (object1->GetRightEdge() > object2->GetLetfEdge() && object1->GetLetfEdge() < object2->GetRightEdge())
		{
			return true;
		}
	}
	else
	{
		if (object2->GetRightEdge() > object1->GetLetfEdge() && object2->GetLetfEdge() < object1->GetRightEdge())
		{
			return true;
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