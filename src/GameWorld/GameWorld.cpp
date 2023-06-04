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
	for (auto item = m_objects.begin(); item != m_objects.end(); item ++)
	{
		(*item)->Update();
		if (GameObject::Status::Dead == (*item)->GetStatus())
		{
			item = m_objects.erase(item);
		}
	}
	m_SunCountDown--;
	if (m_SunCountDown == 0)
	{
		m_SunCountDown = SunCountInterval;

		m_objects.emplace_front(std::make_shared<SunSky>(randInt(SunSky::MinX, SunSky::MaxX), WINDOW_HEIGHT - 1, randInt(SunSky::MinFallTime, SunSky::MaxFallTime),shared_from_this()));
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

std::optional<const Plant> GameWorld::isCollidedForZombie(Zombie& zombie)
{
	for (auto item = m_objects.begin(); item != m_objects.end(); item++)
	{
		if ((*item)->GetY() == zombie.GetY())
		{
			if ((*item)->GetType() == GameObject::ObjectType::Plant)
			{
				if (zombie.GetLetfEdge() < (*item)->GetRightEdge() && zombie.GetRightEdge() > (*item)->GetLetfEdge())
				{
					return ;
				}
			}
		}
	}
	return std::nullopt;
}