#include "GameWorld.hpp"

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

int CreateRandom(int min, int max)
{

	int gap = std::abs(max - min);

	int result = std::rand()%gap + min;

	return result;
}

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

		m_objects.emplace_front(std::make_shared<SunSky>(CreateRandom(SunSky::MinX, SunSky::MaxX), WINDOW_HEIGHT - 1, CreateRandom(SunSky::MinFallTime, SunSky::MaxFallTime),shared_from_this()));
	}

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  // YOUR CODE HERE
	m_objects.clear();
}

