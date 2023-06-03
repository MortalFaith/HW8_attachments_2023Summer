#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"
#include "GameWorld.hpp"

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;


class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject> {
public:
  using std::enable_shared_from_this<GameObject>::shared_from_this; // Use shared_from_this() instead of "this".
 enum class Status
  {
	  Alive,
	  Dead,
  };

  enum class ObjectType
  {
	  UnDefine,
	  NoInteract,
	  AffectSun,
	  ConditionInteract,
  };  
  
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, ObjectType type = ObjectType::UnDefine) : ObjectBase(imageID, x, y, layer, width, height, animID), m_type(type) {};

 

  void ChangeStatus() { m_status = Status::Dead; };
  Status GetStatus() { return m_status; };

  ObjectType GetType() { return m_type; };

private:

	Status m_status{ Status::Alive };
	ObjectType m_type{ ObjectType::UnDefine };
};



class Background : public GameObject
{
public : 
	Background() :GameObject(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, ANIMID_NO_ANIMATION, ObjectType::NoInteract) {};
	~Background() = default;

	virtual void Update() final override {};
	virtual void OnClick() final override {};
};

// Declares the class name GameWorld so that its pointers can be used.

class ObjectAffectSun : public GameObject
{
public:
	ObjectAffectSun(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, pGameWorld thisworld) : GameObject(imageID, x, y, layer, width, height, animID, ObjectType::AffectSun), m_world(thisworld) {};

protected:
	pGameWorld m_world;
};



class Sun : public ObjectAffectSun  // abstract
{

public:
	static inline int const SunWidth = 80;
	static inline int const SunHeight = 80;
	static inline int const FallFlower = 12;
	static inline int const SunValue = 114514114514;

	Sun(int init_x, int init_y, int falltime, pGameWorld thisworld) : ObjectAffectSun(IMGID_SUN, init_x, init_y, LAYER_SUN, SunWidth, SunHeight, ANIMID_IDLE_ANIM, thisworld), m_falltime(falltime) {};
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
};


class SunSky : public Sun
{
public:
	static inline int const MaxFallTime = 263 * 2;
	static inline int const MinFallTime = 63;
	static inline int const MinX = 75;
	static inline int const MaxX = WINDOW_WIDTH - 75;

	SunSky(int init_x, int init_y, int falltime, pGameWorld thisworld) : Sun(init_x, init_y, falltime, thisworld) {};

	void Update();
};


class Seed : public ObjectAffectSun
{
public:
	static inline const int SeedXStart = 130, SeedXInterval = 60, SeedY = WINDOW_HEIGHT - 44, SeedWidth = 50, SeedHeight = 70;

	Seed(ImageID imageID, int x_index, int price, int cooltime, pGameWorld thisworld) : ObjectAffectSun(imageID, SeedXStart + x_index * SeedXInterval,SeedY, LAYER_UI, SeedWidth, SeedHeight, ANIMID_NO_ANIMATION, thisworld), m_price(price), m_CoolTime(cooltime) {};

	void OnClickTemplt();

	int GetCoolTime() { return m_CoolTime; };

private:
	const int m_price;
	const int m_CoolTime;
};

class SunFlowerSeed : public Seed
{
public:
	static inline const int SunFlowerSeedPosition = 0, SunFlowerSeedValue = 50, SunFlowereedCoolTime = 240;

	SunFlowerSeed(pGameWorld thisworld) : Seed(IMGID_SEED_SUNFLOWER, SunFlowerSeedPosition, SunFlowerSeedValue, SunFlowereedCoolTime, thisworld) {};
	virtual void Update() {};
	virtual void OnClick() { Seed::OnClickTemplt(); };
};

class PeaSeed : public Seed
{
public:
	static inline const int PeaSeedPosition = 1, PeaSeedValue = 100, PeaSeedCoolTime = 240;

	PeaSeed(pGameWorld thisworld) : Seed(IMGID_SEED_PEASHOOTER, PeaSeedPosition, PeaSeedValue, PeaSeedCoolTime, thisworld) {};
	virtual void Update() {};
	virtual void OnClick() { Seed::OnClickTemplt(); };

};

class WallnutSeed : public Seed
{
public:
	static inline const int WallnutSeedPosition = 2, WallnutSeedValue = 50, WallnutSeedCoolTime = 900;

	WallnutSeed(pGameWorld thisworld) : Seed(IMGID_SEED_WALLNUT,WallnutSeedPosition, WallnutSeedValue, WallnutSeedCoolTime, thisworld) {};
	virtual void Update() {};
	virtual void OnClick() { Seed::OnClickTemplt(); };

};

class CherrySeed : public Seed
{
public:
	static inline const int CherrySeedPosition = 3, CherrySeedValue = 150, CherrySeedCoolTime = 1200;

	CherrySeed(pGameWorld thisworld) : Seed(IMGID_SEED_CHERRY_BOMB, CherrySeedPosition, CherrySeedValue, CherrySeedCoolTime, thisworld) {};
	virtual void Update() {};
	virtual void OnClick() { Seed::OnClickTemplt(); };

};

class RepeaterSeed : public Seed
{
public:
	static inline const int RepeaterSeedPosition = 4, RepeaterSeedValue = 200, RepeaterSeedCoolTime = 240;

	RepeaterSeed(pGameWorld thisworld) : Seed(IMGID_SEED_REPEATER, RepeaterSeedPosition, RepeaterSeedValue, RepeaterSeedCoolTime, thisworld) {};
	virtual void Update() {};
	virtual void OnClick() { Seed::OnClickTemplt(); };

};

class CoolDown : public GameObject
{
public:
	static inline const int CoolDownWidth = 50, CoolDownHeight = 70;

	CoolDown(int x, int y, int cooltime) : GameObject(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, CoolDownWidth, CoolDownHeight, ANIMID_NO_ANIMATION, ObjectType::NoInteract), m_cooltime(cooltime) {};

	virtual void Update();

	virtual void OnClick() {};

private:
	int m_cooltime;
};


class PlantSpot : public GameObject
{
public:
	static inline const int PlantSpotWidth = 60, PlantSpotHeight = 80;

	PlantSpot(int x, int y) : GameObject(IMGID_NONE, x, y, LAYER_UI, PlantSpotWidth, PlantSpotHeight, ANIMID_NO_ANIMATION, ObjectType::ConditionInteract) {};
	virtual void Update() {};
	virtual void OnClock();

};

#endif // !GAMEOBJECT_HPP__
