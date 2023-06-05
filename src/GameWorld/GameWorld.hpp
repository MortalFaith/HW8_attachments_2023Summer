#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>
#include <random>

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
	Spade,
};

#include "GameObject.hpp"


class GameObject;
using pGameObject = std::shared_ptr<GameObject>;


class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld> {
public:
  // Use shared_from_this() instead of "this".
	static inline int const SunStartCount = 180;
	static inline int const SunCountInterval = 300;
	static inline int const InitSun = 50;
	static inline int const InitWave = 8;
	static inline int const ZombieStartCount = 120;

  GameWorld();
  virtual ~GameWorld();

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;

  void AddObject(pGameObject object) { m_objects.emplace_front(object); };

  FunctionName GetFunction() { return m_function; };
  void SetFunction(FunctionName functionname) { m_function = functionname; };
<<<<<<< HEAD
  bool existZombie(int x, int y) { return true; };
=======
  
  bool existZombie(int x, int y) {};
>>>>>>> e4835511c521a865fd3e56d5574bccaca28f7df4

private: 

	std::list<pGameObject> m_objects{};
	unsigned int m_SunCountDown{ SunStartCount };
	unsigned int m_ZombieCountDown{ ZombieStartCount };
	FunctionName m_function{ FunctionName::None };
};

#endif // !GAMEWORLD_HPP__
