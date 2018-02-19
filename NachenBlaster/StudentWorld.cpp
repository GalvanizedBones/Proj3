#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <stdlib.h> 
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
	: GameWorld(assetDir)
	//List defailt makes actorList empty
{
}

int StudentWorld::init()
{
	Actor* player = new NachenBlaster(IID_NACHENBLASTER, 10, VIEW_HEIGHT / 2);
	m_player = player;
	m_actorList.push_back(player);

	//Generate random star background
	int numberOfInitStars = 30;
	for (int i = 0; i < numberOfInitStars; i++) {
		double randx = rand() % VIEW_WIDTH;
		double randy = rand() % VIEW_HEIGHT;
		double randsize = ((double)(rand() % 45) / 100) + .05;

		Actor* bkgrndStar = new Star(IID_STAR, randx, randy, 0, randsize, 3);
		m_actorList.push_back(bkgrndStar);
	}



	//number of ships needed to pass level
		//get level
			//check with formula


	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit enter.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	
	//int StudentWorld::move()
	//{
	//	// The term "actors" refers to all aliens, the NachenBlaster, goodies,
	//	// stars, explosions, projectiles, stars, etc.
	//	// Give each actor a chance to do something, incl. the NachenBlaster
	//	for each of the actors in the game world
	//	{
	//		if (actor[i] is still active / alive)
	//		{
	//			// tell each actor to do something (e.g. move)
	//			actor[i]->doSomething();
	//			if (theNachenBlasterDiedDuringThisTick())
	//				return GWSTATUS_PLAYER_DIED;
	//			if (theNachenBlasterCompletedTheCurrentLevel())
	//			{
	//				increaseScoreAppropriately();
	//				return GWSTATUS_FINISHED_LEVEL;
	//			}
	//		}
	//	}
	//		// Remove newly-dead actors after each tick
	//	removeDeadGameObjects(); // delete dead game objects
	//							 // Update the Game Status Line
	//	updateDisplayText(); // update the score/lives/level text at screen top
	//						 // the player hasn’t completed the current level and hasn’t died, so
	//						 // continue playing the current level
	//	return GWSTATUS_CONTINUE_GAME;
	//}



	std::list<Actor*>::iterator doer; //Create an iterator for the actors list
	doer = m_actorList.begin();

	while (doer != m_actorList.end()) { //Check for end of list
		if ((*doer)->isAlive()) { //Check actor is still alive
			(*doer)->doSomething(); //Perform action
			if (!m_player->isAlive()) { //Check if player is still alive
				return GWSTATUS_PLAYER_DIED;
			}
			//If level completed
		}
		doer++;
	}

    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	std::list<Actor*>::iterator cleaner;
	cleaner = m_actorList.begin();
	while (cleaner != m_actorList.end()) {
		cleaner = m_actorList.erase(cleaner);
	}


}
