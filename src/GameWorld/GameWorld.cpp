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
		
		m_ZombieCountDown = 150 /*> 600 - 20 * NowWave ? 150 : 600 - 20 * NowWave*/;
		m_ZombieCountDown /= 1;
		//NOTICE! "/10" is used for test!!!
		int ZombieNum = (15 + GetWave()) / 10;
		//NOTICE! "*10" is used for test!!!
		
		static int const ProbabilityRegular_Zombie = 20;
		int ProbabilityPole_Vaulting_Zombie = 2 * (GetWave() - 8 > 0 ? GetWave() - 8 : 0);
		int ProbabilityBucket_Head_Zombie = 3 * (GetWave() - 15 > 0 ? GetWave() - 15 : 0);

		while (ZombieNum > 0) {
			ZombieNum--;
			
			int m_Probability = randInt(0, ProbabilityRegular_Zombie + ProbabilityPole_Vaulting_Zombie + ProbabilityBucket_Head_Zombie);
			if (m_Probability < ProbabilityRegular_Zombie) {
				m_objects.emplace_front(std::make_shared<Regular_Zombie>(randInt(Zombie::MinX, Zombie::MaxX), Zombie::PossibleY[randInt(0, 4)], shared_from_this()));
			}
			else if (m_Probability < ProbabilityRegular_Zombie + ProbabilityPole_Vaulting_Zombie) {
				m_objects.emplace_front(std::make_shared<Pole_Vaulting_Zombie>(randInt(Zombie::MinX, Zombie::MaxX), Zombie::PossibleY[randInt(0, 4)], shared_from_this()));
			}
			else {
				m_objects.emplace_front(std::make_shared<Bucket_Head_Zombie>(randInt(Zombie::MinX, Zombie::MaxX), Zombie::PossibleY[randInt(0, 4)], shared_from_this()));
			}
		}
		SetWave(GetWave()+1);
	}

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  // YOUR CODE HERE
	m_objects.clear();
}

