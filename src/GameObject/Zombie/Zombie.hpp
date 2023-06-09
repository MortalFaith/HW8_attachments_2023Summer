#ifndef ZOMBIE_HPP__
#define ZOMBIE_HPP__

#include <memory>
#include <vector>
#include "ObjectBase.hpp"
#include "GameWorld.hpp"

class Zombie : public ObjectAffectWorld
{
public:
	static inline const int ZombieWidth = 20, ZombieHeight = 80, ZombieGamage = 3;
	static inline int const MinX = WINDOW_WIDTH - 40;
	static inline int const MaxX = WINDOW_WIDTH - 1;
	static inline int const PossibleY[5] = { 75, 175, 275, 375, 475 };
	Zombie(ImageID imageID, int x, int y, int HP, int speed, AnimID animID, pGameWorld thisworld) : ObjectAffectWorld(imageID, x, y, LAYER_ZOMBIES, ZombieWidth, ZombieHeight, animID, thisworld, ObjectType::Zombie), m_HP(HP), m_speed(speed) {};

	virtual void Update();
	virtual void OnClick() {};
	virtual int GetDamage() { return ZombieGamage; };
	virtual void Colliding() {};
	virtual void Colliding(int speed);



protected:
	int m_HP;
	int m_speed;
};

class RegularZombie : public Zombie
{
public:
	static inline const int RegularZombieHP = 200, RegularZombieSpeed = 1;

	RegularZombie(int x, int y, pGameWorld thisworld) : Zombie(IMGID_REGULAR_ZOMBIE, x, y, RegularZombieHP, RegularZombieSpeed, ANIMID_WALK_ANIM, thisworld) {};

	virtual void Update() { Zombie::Update(); };
	virtual void OnClick() {};
	virtual void Colliding() { Zombie::Colliding(RegularZombieSpeed); };

};

class BucketZombie : public Zombie
{
public:
	static inline const int BucketZombieHP = 1300, ZombieHP = 200, BucketZombieSpeed = 1;

	BucketZombie(int x, int y, pGameWorld thisworld) : Zombie(IMGID_BUCKET_HEAD_ZOMBIE, x,y, BucketZombieHP, BucketZombieSpeed,ANIMID_WALK_ANIM ,thisworld) {};

	virtual void Update();
	virtual void OnClick() {};
	virtual void Colliding() { Zombie::Colliding(BucketZombieSpeed); };

};

class PoleZombie : public Zombie
{
public :
	static inline const int PoleZombieHP = 340, PoleZombieRunSpeed = 2, PoleZombieWalkSpeed = 1, JumpTestX = 40, PoleZombieAnimPlaytime = 42, PoleZombieJumpX = 150;;

	PoleZombie(int x, int y, pGameWorld thisworld) : Zombie(IMGID_POLE_VAULTING_ZOMBIE, x, y, PoleZombieHP, PoleZombieRunSpeed, ANIMID_RUN_ANIM, thisworld) {};

	virtual void Update();
	virtual void OnClick() {};
	virtual void Colliding();
	virtual int GetLeftEdge();
	virtual int GetRightEdge();

private :
	bool m_isRunning{true};
	int m_AnimPlayingtime{ PoleZombieAnimPlaytime };
};

#endif