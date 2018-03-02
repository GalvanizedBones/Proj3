#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld; 

class Actor :public GraphObject {
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
	virtual void increaseHealth(double heal) {}; //Default do nothing
	virtual void addSpecAmmo(double sAmmoPickup) {}; //Default do nothing
	bool isAlive() { return m_alive; }
	void setAlive(bool alive) { m_alive = alive; }
	bool Frednly() { return m_frendly; }
	void setFrendly(bool frendOrFoe) { m_frendly = frendOrFoe; }
	virtual bool isProjectile() = 0;
	virtual bool isBackground() = 0;
	virtual bool isHuman() = 0;
	virtual bool isGoodie() = 0;
	virtual bool isAlien() = 0;
	virtual bool isOnTimer() = 0;

	virtual ~Actor() {}

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
	virtual bool isProjectile() { return false; }
	virtual bool isBackground() { return true; }
	virtual bool isHuman() {return false;}
	virtual bool isGoodie() { return false; }
	virtual bool isAlien() { return false; }
	virtual bool isOnTimer() { return false; }


	virtual ~Star() {}

private:
};

class OnTimerActor : public Actor {
public:
	OnTimerActor(int imageID, double startX, double startY, Direction dir, double size, unsigned int depth)
		:Actor(imageID, startX, startY, dir, size, depth),
		m_onTimer(false),
		m_timeLeft(0)
	{

	}

	void setTimeLeft(int timer) { m_timeLeft = timer; }
	void decTimeLeft() { m_timeLeft--; }
	int getTimeLeft() { return m_timeLeft; }

	void setOnTimer(bool onOroff) { m_onTimer = onOroff; }
	virtual bool isOnTimer() {return m_onTimer;}
	virtual bool isProjectile() { return false; }
	virtual bool isBackground() { return true; }
	virtual bool isHuman() { return false; }
	virtual bool isGoodie() { return false; }
	virtual bool isAlien() { return false; }


	virtual ~OnTimerActor() {}
private:
	bool m_onTimer;
	int m_timeLeft;

};

class Explosion : public OnTimerActor {
public:
	Explosion(int imageID, double startX, double startY, Direction dir=0, double size=1, unsigned int depth=0)
		:OnTimerActor(imageID, startX, startY, dir, size, depth),
		m_explosionSize(size)
	{
		setOnTimer(true);
		setTimeLeft(4); //4 tick lifespan
	}

	virtual void doSomething() {
		//Increase in size 1.5 times
		//Reduce timer life by 1
			//Out of initial of 4
		if (getTimeLeft() > 0) { //Still have time left
			setSize(m_explosionSize);
			m_explosionSize = m_explosionSize * 1.5;
			decTimeLeft();
		}
		else {
			setAlive(false);
		}
	}

	virtual ~Explosion() {}

private:
	double m_explosionSize;


};

class CollideableActor : public OnTimerActor {
public:
	CollideableActor(StudentWorld* thisGameWorld, int imageID, double startX, double startY, double damage, Direction dir, double size, unsigned int depth)
		:OnTimerActor(imageID, startX, startY, dir, size, depth),
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

	virtual ~CollideableActor() {}

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

	virtual void increaseHealth(double heal) {
		m_HP = m_HP + heal;
		if (m_HP > m_maxHP) {
			m_HP = m_maxHP; //No overheals
		}
	}

	double getHealth() {
		return m_HP;
	}



	void addCommAmmo(double cAmmo) {
		m_commonAmmo = m_commonAmmo + cAmmo;
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

	void addSpecAmmo(double sAmmoPickup) {
		m_specialAmmo = m_specialAmmo + sAmmoPickup;
		//No upper limit!
			//Asking for an overflow....

	}
	double getSpecAmmoSupply() {
		return m_specialAmmo;
	}

	virtual void collide(double damage);
	virtual void postDeath() = 0;
	virtual bool isAlien() = 0;

	virtual ~ShootingActor() {}


private:
	int m_maxHP;
	int m_HP;
	int m_specialAmmo; //Torpedos 
	int m_commonAmmo; //Cabbages

};

class NonPlayerShootingActor : public ShootingActor {
public:
	NonPlayerShootingActor(StudentWorld* thisGameWorld, int imageID, double startX, double startY, int maxHp, double damage, Direction dir, double size, unsigned int depth, double flgtPthLgth, double speed)
		:ShootingActor(thisGameWorld, imageID, startX, startY, maxHp, damage, dir, size, depth, 255, 255),
		m_flightPathLength(flgtPthLgth),
		m_travelSpeed(speed),
		m_orientation(0)
	{	}

	virtual void doSomething(); 
	virtual bool doSomethingSpecialNPC() = 0; 

	void setOrientation(int orient) {m_orientation = orient;}

	int getOrientation() {
		return m_orientation;
		//1: Up and Left
		//0: Due Left
		//-1: Down and Left
	}

	int getNPCSpeed() {	return m_travelSpeed;}
	void setNPCSpeed(int newSpeed) {m_travelSpeed = newSpeed;}


	int getNPCPathLength() {return m_flightPathLength;}
	void setNPCPAthLength(int newLength) {m_flightPathLength = newLength;}
	void decFlightPath() { m_flightPathLength--; }

	bool checkFlownOffLeft(int x);
	bool checkTopOrBottom(int y);
	bool isAlien() {return true;}

	virtual ~NonPlayerShootingActor() {}



private: 
	double m_flightPathLength;
	double m_travelSpeed;
	int m_orientation; 
};


class NachenBlaster : public ShootingActor {
	//The Player Character
public:
	NachenBlaster(StudentWorld* thisGameWorld, int imageID, double startX, double startY)
		: ShootingActor(thisGameWorld, imageID, startX, startY,  50,  5000, 0, 1, 0, 0, 30)
															//Coll Dam    //dir  //depth //initComm(30Cabb)
																     //HP    //Size //initSpec(0Torp)
		{}
	virtual void doSomething();
	virtual bool isHuman() { return true; }
	virtual bool isAlien() { return false; }
	virtual void postDeath() {};
	virtual void refillCommAmmo() {
		if (getCommAmmoSupply() < 30) {
			addCommAmmo(1); //Only add ammo if not topped off
		}
	}

	virtual ~NachenBlaster() {  }

private:

};

class Smallgon : public NonPlayerShootingActor {
public:
	Smallgon(StudentWorld* thisGameWorld, double startX, double startY, int maxHp, Direction dir=0, double size=1.5, unsigned int depth=1, double flgtPthLgth=0, double speed= 2.0)
		:NonPlayerShootingActor(thisGameWorld, IID_SMALLGON, startX, startY, maxHp, 5, dir, size, depth, flgtPthLgth, speed)
	{ //Allow for short function call by default variables
			//But also allows for potential 'Boss Smallgon' by slightly altering parameters
		setFrendly(false);
	}
	virtual bool isHuman() { return false; }
	virtual bool doSomethingSpecialNPC();
	virtual void postDeath(); 

	virtual ~Smallgon() {}

private:
};

class Smoregon : public NonPlayerShootingActor {
public:
	Smoregon(StudentWorld* thisGameWorld, double startX, double startY, int maxHp, Direction dir = 0, double size = 1.5, unsigned int depth = 1, double flgtPthLgth = 0, double speed = 2.0)
		:NonPlayerShootingActor(thisGameWorld, IID_SMOREGON, startX, startY, maxHp, 5, dir, size, depth, flgtPthLgth, speed)
	{
		setFrendly(false);
	}
	virtual bool isHuman() { return false; };
	virtual bool doSomethingSpecialNPC();
	virtual void postDeath();

	virtual ~Smoregon() {}

private:
};

class Snagglegon : public NonPlayerShootingActor {
public:
	Snagglegon(StudentWorld* thisGameWorld, double startX, double startY, int maxHp, Direction dir = 0, double size = 1.5, unsigned int depth = 1, double flgtPthLgth = 0, double speed = 1.75)
		:NonPlayerShootingActor(thisGameWorld, IID_SNAGGLEGON, startX, startY, maxHp, 5, dir, size, depth, flgtPthLgth, speed)
	{
		setFrendly(false);
		setOrientation(-1); //Begin down and left
	}
	virtual bool isHuman() { return false; };
	virtual bool doSomethingSpecialNPC();
	virtual void postDeath();

	virtual ~Snagglegon() {}
	
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
	virtual bool isAlien() { return false; }

	virtual void collide(double damage) {
		setAlive(false); //Projectiles are very weak
	}

	virtual void doSomething();

	virtual void doSomethingSpecific() = 0;
	
	virtual ~Projectile() {}

private:

};




class Cabbage : public Projectile {
public:
	Cabbage(StudentWorld* thisGameWorld, int imageID, double startX, double startY, double damage = 2, Direction dir = 0, double size = 0.5, unsigned int depth = 1)
	: Projectile(thisGameWorld, imageID, startX, startY, damage, dir, size, depth)
{//Stars only exist
		setFrendly(true);
}

	virtual void doSomethingSpecific();
	
	virtual ~Cabbage() {}

private:

};

class Turnip: public Projectile {
public:
	Turnip(StudentWorld* thisGameWorld, int imageID, double startX, double startY, double damage = 2, Direction dir = 0, double size = 0.5, unsigned int depth = 1)
		: Projectile(thisGameWorld, imageID, startX, startY, damage, dir, size, depth)
	{//Stars only exist
		setFrendly(false);
	}
	virtual void doSomethingSpecific();

	virtual ~Turnip() {}

private:

};

class Torpedo : public Projectile {
public:
	Torpedo(bool frendOrfoe, StudentWorld* thisGameWorld, int imageID, double startX, double startY , Direction dir, double damage=8, double size = 0.5, unsigned int depth = 1)
		: Projectile(thisGameWorld, imageID, startX, startY, damage, dir, size, depth)
	{
		setFrendly(frendOrfoe);
	}

	virtual void doSomethingSpecific();

	virtual ~Torpedo() {}

private:
};














class Goodie : public CollideableActor {
public:
	Goodie(StudentWorld* thisGameWorld, int imageID, double startX, double startY, Direction dir, double size, unsigned int depth)
		:CollideableActor(thisGameWorld, imageID, startX, startY, 0 , dir, size, depth)
	{}
	virtual void doSomething();
	virtual bool doSomethingGood() = 0;

	virtual void collide(double damage) {};
	virtual bool isGoodie() { return true; }



private:

};


class ExtraLife : public Goodie {
public:
	ExtraLife(StudentWorld* thisGameWorld, int imageID, double startX, double startY, Direction dir=0, double size=.5, unsigned int depth=1)
		:Goodie(thisGameWorld, imageID, startX, startY, dir, size, depth)
	{}

	virtual bool doSomethingGood();

private:
};


class Repair : public Goodie {
public:
	Repair(StudentWorld* thisGameWorld, int imageID, double startX, double startY, Direction dir = 0, double size = .5, unsigned int depth = 1)
		:Goodie(thisGameWorld, imageID, startX, startY, dir, size, depth)
	{}

	virtual bool doSomethingGood();
private:
};


class SpecAmmo : public Goodie {
public:
	SpecAmmo(StudentWorld* thisGameWorld, int imageID, double startX, double startY, Direction dir = 0, double size = .5, unsigned int depth = 1)
		:Goodie(thisGameWorld, imageID, startX, startY, dir, size, depth)
	{}

	virtual bool doSomethingGood();
private:
};



#endif // ACTOR_H_
