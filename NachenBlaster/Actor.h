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
		m_alive(true),
		m_frendly(true)
	{	}

	virtual void doSomething() = 0;
	virtual void collide(double dam) {}; //Default do nothing
	virtual double getDamage() { return 0; };//Default do nothing
	bool isAlive() { return m_alive; }
	void setAlive(bool alive) { m_alive = alive; }
	bool Frednly() { return m_frendly;  }
	void setFriendly(bool frendOrFoe) { m_frendly = frendOrFoe; }
	virtual bool isProjectile() = 0;
	virtual bool isBackground() = 0;
	virtual bool isHuman() = 0; 
	virtual bool isGoodie() = 0;

private:
	bool m_alive;
	bool m_frendly;


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
	CollideableActor(StudentWorld* thisGameWorld, int imageID, double startX, double startY, double damage, Direction dir, double size, unsigned int depth)
		:Actor(imageID, startX, startY, dir, size, depth),
		m_gameWorld(thisGameWorld),
		m_collisionDamage(damage)
	{
	}

	virtual bool isBackground() { return false; }


	//Able to call StudentWorld's Collide function 
	StudentWorld* thisGameWorld() {
		return m_gameWorld;
	}

	double getDamage() {
		return m_collisionDamage;
	}

	virtual void collide(double damage) = 0; //ensure astract class



private:
	StudentWorld* m_gameWorld;
	double m_collisionDamage; 



};

class ShootingActor : public CollideableActor {
public: 
	ShootingActor(StudentWorld* thisGameWorld, int imageID, double startX, double startY, int maxHp, double damage, Direction dir, double size, unsigned int depth,   int initSpecAmm, int initCommAmm)
		:CollideableActor(thisGameWorld, imageID, startX, startY, damage, dir,   size, depth),
		m_maxHP(maxHp),
		m_HP(maxHp),
		m_specialAmmo(initSpecAmm),
		m_commonAmmo(initCommAmm)
	{

	}

	bool isProjectile() { return false; }
	bool isGoodie() { return false; }

	//virtual void collide(double damage) = 0; //Reminder, on collision -- need to affect health

	void subractHealth(double damage) {
		m_HP = m_HP - damage;
		if (m_HP < 0) {
			setAlive(false);
		}
	}

	double getHealth() {
		return m_HP;
	}

	void subractCommAmmo(double cAmmoUsed) {
		m_commonAmmo = m_commonAmmo - cAmmoUsed;
		if (m_commonAmmo < 0) {
			m_commonAmmo = 0; //no such thing as bullet debt
		}
	}
	double getCommAmmoSupply() {
		return m_commonAmmo;
	 }

	void subractSpecAmmo(double sAmmoUsed) {
		m_specialAmmo = m_specialAmmo - sAmmoUsed;
		if (m_specialAmmo < 0) {
			m_specialAmmo = 0; //no such thing as bullet debt
		}
	}
	double getSpecAmmoSupply() {
		return m_specialAmmo;
	}

	virtual void collide(double damage) {
		subractHealth(damage);
		//Incurring damage! 
		//Either by a torpedo collision
		//or a collision with another ship!
		if (getHealth() < 0) {
			setAlive(false);
		}
	}




private:
	int m_maxHP;
	int m_HP;
	int m_specialAmmo; //Torpedos 
	int m_commonAmmo; //Cabbages

};

class NonPlayerShootingActor : public ShootingActor {
public: 
	NonPlayerShootingActor(StudentWorld* thisGameWorld, int imageID, double startX, double startY, int maxHp, double damage, Direction dir, double size, unsigned int depth, int initSpecAmm, int initCommAmm, int flgtPthLgth, int speed)
		:ShootingActor(thisGameWorld, imageID, startX, startY, maxHp, damage, dir, size, depth, initSpecAmm, initCommAmm),
		m_flightPathLength(flgtPthLgth),
		m_travelSpeed(speed),
		m_orientation(0)
	{

	}

	void setOrientation(int orient) {
		m_orientation = orient;
	}

	int getOrientation() {
		return m_orientation;
		//1: Up and Left
		//0: Due Left
		//-1: Down and Left
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
	bool checkTopOrBottom(int y);
	void decFlightPath() { m_flightPathLength--; }



private: 
	int m_flightPathLength;
	int m_travelSpeed;
	int m_orientation; 
};


class NachenBlaster : public ShootingActor {
	//The Player Character
public:
	NachenBlaster(StudentWorld* thisGameWorld, int imageID, double startX, double startY)
		: ShootingActor(thisGameWorld, imageID, startX, startY,  500,  50, 0, 1, 0, 0, 30)
															//Coll Dam    //dir  //depth //initComm(30Cabb)
																     //HP    //Size //initSpec(0Torp)
		{}
	virtual void doSomething();
	virtual bool isHuman() { return true; }



private:

};

class Smallgon : public NonPlayerShootingActor {
public:
	Smallgon(StudentWorld* thisGameWorld, double startX, double startY, int maxHp, Direction dir=0, double size=1.5, unsigned int depth=1, int initSpecAmm=255, int initCommAmm=255, int flgtPthLgth=0, int speed= 2.0)
		:NonPlayerShootingActor(thisGameWorld, IID_SMALLGON, startX, startY, maxHp, 5, dir, size, depth, initSpecAmm, initCommAmm, flgtPthLgth, speed)
	{ //Allow for short function call by default variables
			//But also allows for potential 'Boss Smallgon' by slightly altering parameters
		setFriendly(false);
	}
	virtual bool isHuman() { return false; }
	virtual void doSomething();


private:



};

class Projectile : public CollideableActor {
public:
	Projectile(StudentWorld* thisGameWorld, int imageID, double startX, double startY, double damage, Direction dir, double size , unsigned int depth )
		: CollideableActor(thisGameWorld, imageID, startX, startY, damage, dir, size, depth)
	{

	}

	bool isProjectile() { return true; }
	virtual bool isBackground() { return false; }
	virtual bool isHuman() { return false; }
	virtual bool isGoodie() { return false; }

	virtual void collide(double damage) {
		setAlive(false); //Cabbages are very weak
	}


private:

};




class Cabbage : public Projectile {
public:
	Cabbage(StudentWorld* thisGameWorld, int imageID, double startX, double startY, double damage = 2, Direction dir = 0, double size = 0.5, unsigned int depth = 1)
	: Projectile(thisGameWorld, imageID, startX, startY, damage, dir, size, depth)
{//Stars only exist
}

	virtual void doSomething();

	virtual void collide(double damage) {
			setAlive(false); //Cabbages are very weak
		}
private:

};

class Turnip: public Projectile {
public:
	Turnip(StudentWorld* thisGameWorld, int imageID, double startX, double startY, double damage = 2, Direction dir = 0, double size = 0.5, unsigned int depth = 1)
		: Projectile(thisGameWorld, imageID, startX, startY, damage, dir, size, depth)
	{//Stars only exist
		setFriendly(false);
	}

	virtual void doSomething();


private:

};



#endif // ACTOR_H_
