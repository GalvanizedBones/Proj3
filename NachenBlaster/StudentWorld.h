#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp


class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();


	void buryTheDead();
	bool checkInBounds(Actor* perp);
	void addActor(Actor* newActor);
	bool checkPotentialActorMoveInBounds(double x, double y);
	bool collisionCheck(Actor* hitter);
	double eucledianDist(Actor* source, Actor* target);
	int getPlayerX() { return m_player->getX(); }
	int getPlayerY() { return m_player->getY();  }




private:

	std::list<Actor*> m_actorList;//The list of actors *Game foundation*
	Actor* m_player;//The pointer to the player

};

#endif // STUDENTWORLD_H_
