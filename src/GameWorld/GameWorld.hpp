#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>
#include<optional>
#include "WorldBase.hpp"
#include "utils.hpp"

enum class FunctionName
{
	None,
	PlantSunflower,
	PlantPea,
	PlantWallnut,
	PlantCherry,
	PlantRepeater,
	Shovel,
	TestZombie,
};

#include "GameObject.hpp"


class GameObject;
using pGameObject = std::shared_ptr<GameObject>;


class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld> {
public:
  // Use shared_from_this() instead of "this".
	static inline int const SunStartCount = 180;
	static inline int const SunCountInterval = 300;
	static inline int const InitSun = 5000;
	static inline int const InitWave = 0;
	static inline int const ZombieStartCount = 1200;

  GameWorld();
  virtual ~GameWorld();

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;

  void AddObject(pGameObject object) { m_objects.emplace_front(object); };

  FunctionName GetFunction() { return m_function; };
  void SetFunction(FunctionName functionname) { m_function = functionname; };

  bool existZombie(int x, int y); //{ return true; };
  bool isCollide(pGameObject left, pGameObject right);

  void EraseDead();

private: 

	std::list<pGameObject> m_objects{};
	unsigned int m_SunCountDown{ SunStartCount };
	unsigned int m_ZombieCountDown{ ZombieStartCount };
	FunctionName m_function{ FunctionName::None };
};

#endif // !GAMEWORLD_HPP__
