#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>
#include <random>

#include "WorldBase.hpp"
#include "utils.hpp"

#include "GameObject.hpp"
class GameObject;
using pGameObject = std::shared_ptr<GameObject>;

class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld> {
public:
  // Use shared_from_this() instead of "this".
	static inline int const SunStartCount = 180;
	static inline int const SunCountInterval = 300;
	static inline int const InitSun = 50;
	static inline int const InitWave = 200;

  GameWorld();
  virtual ~GameWorld();

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;

  void AddObject(pGameObject object) { m_objects.push_front(object); };

private: 

	std::list<pGameObject> m_objects{};
	unsigned int m_SunCountDown{ SunStartCount };

};

#endif // !GAMEWORLD_HPP__
