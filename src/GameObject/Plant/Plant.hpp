#ifndef PLANT_HPP__
#define PLANT_HPP__

#include <memory>
#include <vector>
#include "ObjectBase.hpp"
#include "GameWorld.hpp"
/*
class PlantSpot : public ObjectAffectWorld  // option<>
{
public:
	static inline const int PlantSpotWidth = 60, PlantSpotHeight = 80;

	PlantSpot(int x, int y, pGameWorld thisworld) : ObjectAffectWorld(IMGID_NONE, x, y, LAYER_UI, PlantSpotWidth, PlantSpotHeight, ANIMID_NO_ANIMATION, thisworld, ObjectType::Others) {};
	virtual void OnClick();
	virtual void Update() {};

};*/

class Plant : public ObjectAffectWorld
{
public:
	static inline const int PlantWidth = 60, PlandHeight = 80;
	
	Plant(ImageID imageID, int x, int y, int HP, pGameWorld thisworld) : ObjectAffectWorld(imageID, x, y, LAYER_PLANTS, PlantWidth, PlandHeight, ANIMID_IDLE_ANIM, thisworld, ObjectType::Plant), m_HP(HP) {};
	virtual void Update() = 0;
	virtual void OnClick() = 0;

	virtual void Colliding();

	int GetHP() { return m_HP; };
	void SetHP(int HP) { m_HP = HP; };


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

#endif