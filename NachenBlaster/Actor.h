#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld; 

class Actor:public GraphObject {
	//Actor is abstract, will not be possible to construct
public:
	Actor(int imageID, double startX, double startY, Direction dir = 0, double size = 1.0, unsigned int depth = 0)
	: GraphObject(imageID, startX, startY, dir, size, depth), //simple constructor
	m_alive(true)
	{	}

	virtual void doSomething() = 0;
	bool isAlive() { return m_alive; }
	void setAlive(bool alive) { m_alive = alive; }
	virtual bool isProjectile() = 0;
	virtual bool isBackground() = 0;
	virtual bool isHuman() = 0; 
	virtual bool isGoodie() = 0;

private:
	bool m_alive;


};

class Star : public Actor {
public:
	Star(int imageID, double startX, double startY, Direction dir = 0, double size = 1.0, unsigned int depth = 0)
		: Actor(imageID, startX, startY, dir, size, depth)
	{//Stars only exist
	}

	virtual void doSomething() {
		double X = getX();
		double Y = getY();
		X = X - 1; //move to th left each tick
		moveTo(X, Y);

	}
	bool isProjectile() { return false; }
	virtual bool isBackground() { return true; }
	virtual bool isHuman() {return false;}
	virtual bool isGoodie() { return false; }
private:
};

class CollideableActor : public Actor {
public:
	CollideableActor(int imageID, double startX, double startY, Direction dir, double size, unsigned int depth)
		:Actor(imageID, startX, startY, dir, size, depth)
	{

	}
	virtual bool isBackground() { return false; }


private:



};

class ShootingActor : public CollideableActor {
public: 
	ShootingActor(int imageID, double startX, double startY, int maxHp, Direction dir, double size, unsigned int depth ,  int initSpecAmm, int initCommAmm)
		:CollideableActor(imageID, startX, startY, dir, size, depth),
		m_maxHP(maxHp),
		m_HP(maxHp),
		m_specialAmmo(initSpecAmm),
		m_commonAmmo(initCommAmm)
	{

	}

	bool isProjectile() { return false; }
	bool isGoodie() { return false; }




private:
	int m_maxHP;
	int m_HP;
	int m_specialAmmo; //Torpedos 
	int m_commonAmmo; //Cabbages

};

class NonPlayerShootingActor : public ShootingActor {
public: 
	NonPlayerShootingActor(int imageID, double startX, double startY, int maxHp, Direction dir, double size, unsigned int depth, int initSpecAmm, int initCommAmm, int flgtPthLgth, int speed)
		:ShootingActor( imageID,  startX,  startY, maxHp, dir, size, depth, initSpecAmm, initCommAmm),
		m_flightPathLength(flgtPthLgth),
		m_travelSpeed(speed)
	{

	}

	int getNPCSpeed() {
		return m_travelSpeed;
	}
	void setNPCSpeed(int newSpeed) {
		m_travelSpeed = newSpeed;
	}
	int getNPCPathLength() {
		return m_flightPathLength;
	}
	void setNPCPAthLength(int newLength) {
		m_flightPathLength = newLength;
	}

	bool checkFlownOffLeft(int x);



private: 
	int m_flightPathLength;
	int m_travelSpeed;
};


class NachenBlaster : public ShootingActor {
	//The Player Character
public:
	NachenBlaster(int imageID, double startX, double startY, StudentWorld* thisGameWorld)
		: ShootingActor(imageID, startX, startY, 50, 0, 1, 0, 0, 100),
		m_gameWorld(thisGameWorld)
		{}
	virtual void doSomething();
	virtual bool isHuman() { return true; }
private:
	StudentWorld* m_gameWorld; 
};

class Smallgon : public NonPlayerShootingActor {
public:
	Smallgon(double startX, double startY, int maxHp, Direction dir=0, double size=1.5, unsigned int depth=1, int initSpecAmm=255, int initCommAmm=255, int flgtPthLgth=0, int speed= 2.0)
		:NonPlayerShootingActor(IID_SMALLGON, startX, startY, maxHp, dir, size, depth, initSpecAmm, initCommAmm, flgtPthLgth, speed)
	{ //Allow for short function call by default variables
			//But also allows for potential 'Boss Smallgon' by slightly altering parameters

	}
	virtual bool isHuman() { return false; }
	virtual void doSomething();


private:



};

class Projectile : public CollideableActor {
public:
	Projectile(int imageID, double startX, double startY, Direction dir, double size , unsigned int depth )
		: CollideableActor(imageID, startX, startY, dir, size, depth)
	{

	}

	bool isProjectile() { return true; }
	virtual bool isBackground() { return false; }
	virtual bool isHuman() { return false; }
	virtual bool isGoodie() { return false; }


private:

};




class Cabbage : public Projectile {
public:
	Cabbage(int imageID, double startX, double startY, Direction dir = 0, double size = 0.5, unsigned int depth = 1)
	: Projectile(imageID, startX, startY, dir, size, depth)
{//Stars only exist
}

		virtual void doSomething() {
			double X = getX();
			double Y = getY();
			X = X + 1; //move to the right each tick
			moveTo(X, Y);


		}


private:



};



#endif // ACTOR_H_
