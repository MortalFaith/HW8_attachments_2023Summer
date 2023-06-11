#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include <vector>
#include "ObjectBase.hpp"
#include "GameWorld.hpp"
enum class FunctionName;


// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject> {
public:
  using std::enable_shared_from_this<GameObject>::shared_from_this; // Use shared_from_this() instead of "this".
  using pGameObject = std::shared_ptr<GameObject>;
 enum class Status
  {
	  Alive,
	  Dead,
  };

  enum class ObjectType
  {
	  Plant,
	  PlantAttack,
	  Zombie,
	  Others,
  };  
  
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, ObjectType type) : ObjectBase(imageID, x, y, layer, width, height, animID), m_type(type) {};

  virtual void Update() { m_collided.clear(); };
  virtual void OnClick() {};

  void ChangeStatus() { m_status = Status::Dead; };
  Status GetStatus() { return m_status; };

  ObjectType GetType() { return m_type; };

  virtual int GetDamage() { return 0; };

//absolute position
  virtual int GetLeftEdge() { return GetX() - GetWidth() / 2; }; 

//absolute position
  virtual int GetRightEdge() { return GetX() + GetWidth() / 2; };
  int GetUpEdge() { return GetY() + GetHeight() / 2; };
  int GetDownEdge() { return GetY() - GetHeight() / 2; };

  virtual void addCollided(pGameObject object) { m_collided.push_back(object); };
  auto collidedBegin() { return m_collided.cbegin(); };
  auto collidedEnd() { return m_collided.cend(); };
  bool isCollideEmpty() { return m_collided.empty(); };

  virtual void Colliding() {};

  int GetAttackCount() { return m_attack; };
  void MinusAttackCount() { m_attack--; };
  void SetAttackCount(int count) { m_attack = count; };

private:

	Status m_status{ Status::Alive };
	ObjectType m_type;
	std::vector<pGameObject> m_collided{};
	int m_attack{ 0 };
};



class Background : public GameObject
{
public : 
	Background() :GameObject(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, ANIMID_NO_ANIMATION, ObjectType::Others) {};
	~Background() = default;

	void Update() {};
	void OnClick() {};
};

// Declares the class name GameWorld so that its pointers can be used.

class ObjectAffectWorld : public GameObject
{
public:
	ObjectAffectWorld(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, pGameWorld thisworld, ObjectType type) : GameObject(imageID, x, y, layer, width, height, animID, type), m_world(thisworld) {};

	virtual void Update() { GameObject::Update(); };
protected:
	pGameWorld m_world;
};



class Sun : public ObjectAffectWorld  // abstract
{

public:
	static inline int const SunWidth = 80;
	static inline int const SunHeight = 80;
	static inline int const FallFlower = 12;
	static inline int const SunValue = 25;
	static inline int const VanishTime = -300 + 1;

	Sun(int init_x, int init_y, int falltime, pGameWorld thisworld) : ObjectAffectWorld(IMGID_SUN, init_x, init_y, LAYER_SUN, SunWidth, SunHeight, ANIMID_IDLE_ANIM, thisworld, ObjectType::Others), m_falltime(falltime) {};
	virtual ~Sun() = default;

	virtual void Update() = 0;
	virtual void OnClick();


protected :
	int m_falltime;
};

class SunOfFlower : public Sun
{
public:

	SunOfFlower(int init_x, int init_y, pGameWorld thisworld) : Sun(init_x, init_y, FallFlower, thisworld) {};
	~SunOfFlower() = default;

	void Update();

private:
	int m_speed{ 4 };
};


class SunSky : public Sun
{
public:
	static inline int const MaxFallTime = 263;
	static inline int const MinFallTime = 63;
	static inline int const MinX = 75;
	static inline int const MaxX = WINDOW_WIDTH - 75;

	SunSky(int init_x, int init_y, int falltime, pGameWorld thisworld) : Sun(init_x, init_y, falltime, thisworld) { ; };

	void Update();
};

class PlantSpot : public ObjectAffectWorld
{
public:
	static inline const int PlantSpotWidth = 60, PlantSpotHeight = 80;

	PlantSpot(int x, int y, pGameWorld thisworld) : ObjectAffectWorld(IMGID_NONE, x, y, LAYER_UI, PlantSpotWidth, PlantSpotHeight, ANIMID_NO_ANIMATION, thisworld, ObjectType::Others) {};
	virtual void OnClick();
	virtual void Update() {};

};

class Shovel : public ObjectAffectWorld
{
public:
	static inline const int ShovelX = 600, ShovelY = (WINDOW_HEIGHT - 40), ShovelWidth = 50, ShovelHeight = 50;

	Shovel(pGameWorld thisworld) : ObjectAffectWorld(IMGID_SHOVEL, ShovelX, ShovelY, LAYER_UI, ShovelWidth, ShovelHeight, ANIMID_NO_ANIMATION, thisworld, ObjectType::Others) {};

	virtual void Update() {};
	virtual void OnClick() ;

};

class CoolDown : public ObjectAffectWorld
{
public:
	static inline const int CoolDownWidth = 50, CoolDownHeight = 70;

	CoolDown(int x, int y, int cooltime, FunctionName covered, int price, pGameWorld thisworld) : ObjectAffectWorld(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, CoolDownWidth, CoolDownHeight, ANIMID_NO_ANIMATION, thisworld, ObjectType::Others), m_cooltime(cooltime),m_CoveredPrice(price), m_covered(covered) {};

	virtual void Update();
	virtual void OnClick();

private:
	int m_cooltime;
	FunctionName m_covered;
	int m_CoveredPrice;
};


class Attack : public ObjectAffectWorld
{
public:
	Attack(ImageID imageID, int x, int y, int width, int height, pGameWorld thisworld) : ObjectAffectWorld(imageID, x, y, LAYER_PROJECTILES, width, height, ANIMID_NO_ANIMATION, thisworld, ObjectType::PlantAttack) {};
};


class Pea : public Attack
{
public :
	static inline const int PeaWidth = 28, PeaHeight = 28, PeaDamage = 20;

	Pea(int x, int y, pGameWorld thisworld) : Attack(IMGID_PEA, x, y, PeaWidth, PeaHeight, thisworld) { SetAttackCount(1); };

	virtual void Update();
	virtual void OnClick() {};
	virtual int GetDamage() { return PeaDamage; };
	virtual void Colliding();

};


class Boom : public Attack
{
public:
	static inline const int BoomTime = 3, BoomWidth = 3 * LAWN_GRID_WIDTH, BoomHeight = 3 * LAWN_GRID_HEIGHT, BoomDamage = 10000;

	Boom(int x, int y, pGameWorld thisworld) : Attack(IMGID_EXPLOSION, x, y, BoomWidth, BoomHeight, thisworld) { SetAttackCount(10000); };

	virtual void Update();
	virtual void OnClick() {};
	virtual int GetDamage() { return BoomDamage; };

private:
	int m_time{BoomTime};
};


#endif // !GAMEOBJECT_HPP__
