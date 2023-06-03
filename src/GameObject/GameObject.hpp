#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"
#include "GameWorld.hpp"
enum class FunctionName;


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
	  AffectWorld,
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

class ObjectAffectWorld : public GameObject
{
public:
	ObjectAffectWorld(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, pGameWorld thisworld) : GameObject(imageID, x, y, layer, width, height, animID, ObjectType::AffectWorld), m_world(thisworld) {};

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

	Sun(int init_x, int init_y, int falltime, pGameWorld thisworld) : ObjectAffectWorld(IMGID_SUN, init_x, init_y, LAYER_SUN, SunWidth, SunHeight, ANIMID_IDLE_ANIM, thisworld), m_falltime(falltime) {};
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
	static inline int const MaxFallTime = 263;
	static inline int const MinFallTime = 63;
	static inline int const MinX = 75;
	static inline int const MaxX = WINDOW_WIDTH - 75;

	SunSky(int init_x, int init_y, int falltime, pGameWorld thisworld) : Sun(init_x, init_y, falltime, thisworld) { ; };

	void Update();
};

class PlantSpot : public ObjectAffectWorld  // option<>
{
public:
	static inline const int PlantSpotWidth = 60, PlantSpotHeight = 80;

	PlantSpot(int x, int y, pGameWorld thisworld) : ObjectAffectWorld(IMGID_NONE, x, y, LAYER_UI, PlantSpotWidth, PlantSpotHeight, ANIMID_NO_ANIMATION, thisworld) {};
	virtual void OnClick();
	virtual void Update() {};

};

class Shovel : public ObjectAffectWorld
{
public:
	static inline const int ShovelX = 600, ShovelY = (WINDOW_HEIGHT - 40), ShovelWidth = 50, ShovelHeight = 50;

	Shovel(pGameWorld thisworld) : ObjectAffectWorld(IMGID_SHOVEL, ShovelX, ShovelY, LAYER_UI, ShovelWidth, ShovelHeight, ANIMID_NO_ANIMATION, thisworld) {};

	virtual void Update() {};
	virtual void OnClick() ;

};

class Seed : public ObjectAffectWorld
{
public:
	static inline const int SeedXStart = 130, SeedXInterval = 60, SeedY = WINDOW_HEIGHT - 44, SeedWidth = 50, SeedHeight = 70;

	Seed(ImageID imageID, int x_index, int price, int cooltime, pGameWorld thisworld) : ObjectAffectWorld(imageID, SeedXStart + x_index * SeedXInterval,SeedY, LAYER_UI, SeedWidth, SeedHeight, ANIMID_NO_ANIMATION, thisworld), m_price(price), m_CoolTime(cooltime) {};

	void OnClickTemplt(FunctionName);

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
	virtual void OnClick() { Seed::OnClickTemplt(FunctionName::PlantSunflower); };
};

class PeaSeed : public Seed
{
public:
	static inline const int PeaSeedPosition = 1, PeaSeedValue = 100, PeaSeedCoolTime = 240;

	PeaSeed(pGameWorld thisworld) : Seed(IMGID_SEED_PEASHOOTER, PeaSeedPosition, PeaSeedValue, PeaSeedCoolTime, thisworld) {};
	virtual void Update() {};
	virtual void OnClick() { Seed::OnClickTemplt(FunctionName::PlantPea); };

};

class WallnutSeed : public Seed
{
public:
	static inline const int WallnutSeedPosition = 2, WallnutSeedValue = 50, WallnutSeedCoolTime = 900;

	WallnutSeed(pGameWorld thisworld) : Seed(IMGID_SEED_WALLNUT,WallnutSeedPosition, WallnutSeedValue, WallnutSeedCoolTime, thisworld) {};
	virtual void Update() {};
	virtual void OnClick() { Seed::OnClickTemplt(FunctionName::PlantWallnut); };

};

class CherrySeed : public Seed
{
public:
	static inline const int CherrySeedPosition = 3, CherrySeedValue = 150, CherrySeedCoolTime = 1200;

	CherrySeed(pGameWorld thisworld) : Seed(IMGID_SEED_CHERRY_BOMB, CherrySeedPosition, CherrySeedValue, CherrySeedCoolTime, thisworld) {};
	virtual void Update() {};
	virtual void OnClick() { Seed::OnClickTemplt(FunctionName::PlantCherry); };

};

class RepeaterSeed : public Seed
{
public:
	static inline const int RepeaterSeedPosition = 4, RepeaterSeedValue = 200, RepeaterSeedCoolTime = 240;

	RepeaterSeed(pGameWorld thisworld) : Seed(IMGID_SEED_REPEATER, RepeaterSeedPosition, RepeaterSeedValue, RepeaterSeedCoolTime, thisworld) {};
	virtual void Update() {};
	virtual void OnClick() { Seed::OnClickTemplt(FunctionName::PlantRepeater); };

};

class CoolDown : public ObjectAffectWorld
{
public:
	static inline const int CoolDownWidth = 50, CoolDownHeight = 70;

	CoolDown(int x, int y, int cooltime, FunctionName covered, int price, pGameWorld thisworld) : ObjectAffectWorld(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, CoolDownWidth, CoolDownHeight, ANIMID_NO_ANIMATION, thisworld), m_cooltime(cooltime),m_CoveredPrice(price), m_covered(covered) {};

	virtual void Update();
	virtual void OnClick();

private:
	int m_cooltime;
	FunctionName m_covered;
	int m_CoveredPrice;
};



class Plant : public ObjectAffectWorld
{
public:
	static inline const int PlantWidth = 60, PlandHeight = 80;
	
	Plant(ImageID imageID, int x, int y, int HP, pGameWorld thisworld) : ObjectAffectWorld(imageID, x, y, LAYER_PLANTS, PlantWidth, PlandHeight, ANIMID_IDLE_ANIM, thisworld), m_HP(HP) {};
	virtual void Update() = 0;
	virtual void OnClick() = 0;


protected:
	int m_HP;
};

class SunFlower : public Plant
{
public:
	static inline const int SunFlowerHP = 300, SunFlowerInterval = 600;

	SunFlower(int x, int y, pGameWorld thisworld) : Plant(IMGID_SUNFLOWER, x, y, SunFlowerHP, thisworld) {};
	virtual void Update();
	virtual void OnClick() { Plant::OnClick(); };

private:
	int m_CoolTime{randInt(30, 600)};
};

class Peashooter : public Plant
{
public:
	static inline const int PeashooterHP = 300, PeashooterInterval = 30, PeaCreateOffsetX = 30, PeaCreateOffsetY = 20;

	Peashooter(int x, int y, pGameWorld thisworld) : Plant(IMGID_PEASHOOTER, x, y, PeashooterHP, thisworld) {};

	virtual void Update();
	virtual void OnClick() { Plant::OnClick(); };

private:
	int m_CoolTime{0};
};

class Pea : public ObjectAffectWorld
{
public :
	static inline const int PeaWidth = 28, PeaHeight = 28, PeaDamage = 20;

	Pea(int x, int y, pGameWorld thisworld) : ObjectAffectWorld(IMGID_PEA, x, y, LAYER_PROJECTILES, PeaWidth, PeaHeight, ANIMID_NO_ANIMATION, thisworld) {};

	virtual void Update();
	virtual void OnClick() {};

};


class Wallnut : public Plant
{
public:
	static inline const int WallnutHP = 3000, WallnutChangeHP = 1000;

	Wallnut(int x, int y, pGameWorld thisworld) : Plant(IMGID_WALLNUT, x, y, WallnutHP, thisworld) {};

	virtual void Update();
	virtual void OnClick() { Plant::OnClick(); };

private:
	bool m_isCracked{false};
};

class Cherry : public Plant
{
public:
	static inline const int CherryHP = 4000, CherryBoomTime = 15;

	Cherry(int x, int y, pGameWorld thisworld) : Plant(IMGID_CHERRY_BOMB, x, y, CherryHP, thisworld) {};

	virtual void Update();
	virtual void OnClick() { Plant::OnClick(); };

private:
	int m_BoomTime{CherryBoomTime};

};

class Boom : public ObjectAffectWorld
{
public:
	static inline const int BoomTime = 3, BoomWidth = 3 * LAWN_GRID_WIDTH, BoomHeight = 3 * LAWN_GRID_HEIGHT;

	Boom(int x, int y, pGameWorld thisworld) : ObjectAffectWorld(IMGID_EXPLOSION, x, y, LAYER_PROJECTILES, BoomWidth, BoomHeight, ANIMID_NO_ANIMATION, thisworld) {};

	virtual void Update();
	virtual void OnClick() {};

private:
	int m_time{BoomTime};
};


class Repeater : public Plant
{
public:
	static inline const int RepeaterHP = 300, RepeaterInterval = 25, PeaInterval = -5, RepeaterOffsetX = 30, RepeaterOffsetY = 20;

	Repeater(int x, int y, pGameWorld thisworld) : Plant(IMGID_REPEATER, x, y, RepeaterHP, thisworld) {};

	virtual void Update();
	virtual void OnClick() { Plant::OnClick(); };

private:
	int m_ShootCoolTime{0};
};

#endif // !GAMEOBJECT_HPP__
