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
	bool checkPotentialNPCMoveInBounds(double x, double y);


	bool collisionCheck(Actor* hitter);
	double eucledianDist(Actor* source, Actor* target);
	int getPlayerX() { return m_player->getX(); }
	int getPlayerY() { return m_player->getY();  }


	int getNPC_ScreenMax() { return m_npcScreenMax; }
	void setNPC_ScreenMax(int levelNPCScreenMax) { m_npcScreenMax = levelNPCScreenMax; }


	int getPlayerKillCount() { return m_playerKillCount; }
	void incPlayerKillCount() { m_playerKillCount++; }
	void resetPlayerKillCount() { m_playerKillCount = 0; }


	int getNPC_Count() { return m_npcCount; }
	void incNPC_Count() { m_npcCount++; }
	void decNPC_Count() { m_npcCount--; }


	void resetNPC_Count() { m_npcCount = 0; }
	int getLevelGoal() { return m_levelKillGoal; }
	void setLevelGoal(int newLevelGoal) { m_levelKillGoal = newLevelGoal; }





private:

	std::list<Actor*> m_actorList;//The list of actors *Game foundation*
	Actor* m_player;//The pointer to the player
	int m_npcScreenMax; 
	int m_playerKillCount;
	int m_levelKillGoal;
	int m_npcCount;

};

#endif // STUDENTWORLD_H_
