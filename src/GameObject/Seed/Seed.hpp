#ifndef SEED_HPP__
#define SEED_HPP__

#include <memory>
#include <vector>
#include "ObjectBase.hpp"
#include "GameWorld.hpp"

class Seed : public ObjectAffectWorld
{
public:
	static inline const int SeedXStart = 130, SeedXInterval = 60, SeedY = WINDOW_HEIGHT - 44, SeedWidth = 50, SeedHeight = 70;

	Seed(ImageID imageID, int x_index, int price, int cooltime, pGameWorld thisworld) : ObjectAffectWorld(imageID, SeedXStart + x_index * SeedXInterval,SeedY, LAYER_UI, SeedWidth, SeedHeight, ANIMID_NO_ANIMATION, thisworld, ObjectType::Others), m_price(price), m_CoolTime(cooltime) {};

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

class ZombieSeed : public Seed
{
public:
	ZombieSeed(pGameWorld thisworld) :Seed(IMGID_SEED_CHERRY_BOMB, 6, 0, 0, thisworld) {};
	virtual void Update() {};
	virtual void OnClick() { Seed::OnClickTemplt(FunctionName::TestZombie); };
};

#endif