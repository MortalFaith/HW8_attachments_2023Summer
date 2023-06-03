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

	for (int i = 0; i < GAME_ROWS; i++)
	{
		for (int j = 0; j < GAME_COLS; j++)
		{
			m_objects.emplace_front(std::make_shared<PlantSpot>(FIRST_COL_CENTER + LAWN_GRID_WIDTH * j, FIRST_ROW_CENTER + LAWN_GRID_HEIGHT * i,shared_from_this()));
			//m_objects.emplace_front(std::make_shared<SunFlower>(FIRST_COL_CENTER + LAWN_GRID_WIDTH * j, FIRST_ROW_CENTER + LAWN_GRID_HEIGHT * i,shared_from_this()));
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

	m_ZombieCountDown--;
	if (m_ZombieCountDown == 0)
	{
		m_ZombieCountDown = 150 > 600 - 20 * m_Wave ? 150 : 600 - 20 * m_Wave;
		static int ZombieNum = (15 + m_Wave) / 10;
		
		while (ZombieNum > 0) {
			ZombieNum--;

			static int const ProbabilityRegular_Zombie = 20;
			static int ProbabilityPole_Vaulting_Zombie = 2 * (m_Wave - 8 > 0 ? m_Wave - 8 : 0);
			static int ProbabilityBucket_Head_Zombie = 3 * (m_Wave - 15 > 0 ? m_Wave - 15 : 0);
			
			//TODO: calculate possibility of each zombie.

			m_objects.emplace_front(std::make_shared<Regular_Zombie>(randInt(Regular_Zombie::MinX, Regular_Zombie::MaxX), Regular_Zombie::PossibleY[randInt(0,0)], shared_from_this()));
		}
	}

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  // YOUR CODE HERE
	m_objects.clear();
}

