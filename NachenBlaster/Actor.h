#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor:public GraphObject {
	//Actor is abstract, will not be possible to construct
public:
	Actor(int imageID, double startX, double startY, Direction dir = 0, double size = 1.0, unsigned int depth = 0)
	: GraphObject(imageID, startX, startY, dir, size, depth), //simple constructor
	m_alive(true)
	{	}

	virtual void doSomething() = 0;
	virtual bool isAlive() { return m_alive; }

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
private:
};


class NachenBlaster : public Actor {
	//The Player Character
public:
	NachenBlaster(int imageID, double startX, double startY)
		: Actor(imageID, startX, startY),
		m_HP(50),
		m_maxHP(50),
		m_torpedos(0),
		m_ammo(100)
		{}

	virtual void doSomething() {
		//do nothing
	}

private:
	int m_maxHP;
	int m_HP; 
	int m_torpedos;
	int m_ammo;
};

#endif // ACTOR_H_
