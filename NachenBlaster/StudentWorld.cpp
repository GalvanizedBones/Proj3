#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>

#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw

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
	resetNPC_Count();
	resetPlayerKillCount();
	setNPC_ScreenMax(5 + .5*getLevel()); //compiler always truncates -- in player favor -- cant have 1/2 an alien
	setLevelGoal(6 + (4 * getLevel()) );
	
	NachenBlaster* player = new NachenBlaster(this, IID_NACHENBLASTER, 0, 128);
	m_player = player;
	m_actorList.push_back(player);

	//Generate random star background
	int numberOfInitStars = 30;
	for (int i = 0; i < numberOfInitStars; i++) {
		double randx = randInt(0, VIEW_WIDTH - 1); //% VIEW_WIDTH;
		double randy = randInt(0, VIEW_HEIGHT - 1);// % VIEW_HEIGHT;
		double randsize = ((double)(randInt(0,45-1)) / 100) + .05;

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
	//						 // the player hasn�t completed the current level and hasn�t died, so
	//						 // continue playing the current level
	//	return GWSTATUS_CONTINUE_GAME;
	//}



	std::list<Actor*>::iterator doer; //Create an iterator for the actors list
	doer = m_actorList.begin();


//2) Have game objects doSomething
while (doer != m_actorList.end()) { //Check for end of list
	if ((*doer)->isAlive()) { //Check actor is still alive
		(*doer)->doSomething(); //Perform action

		if (!checkInBounds(*doer)) {
			//out of bounds, mark dead
			(*doer)->setAlive(false);
		}

		if (!m_player->isAlive()) { //Check if player is still alive
			decLives();
			return GWSTATUS_PLAYER_DIED;
		}
		if (getPlayerKillCount() >= getLevelGoal()) {
			//Beat the level!
			//advanceToNextLevel(); **not to be used by student
			playSound(SOUND_FINISHED_LEVEL);
			return GWSTATUS_FINISHED_LEVEL;
		}


	}

	//If level completed

	doer++;
}


//3) get rid of anything dead
buryTheDead();

//4)1/15 to make a new star
int newStar = randInt(0, 15-1); //% 15;
if (newStar == 7) { //Lucky number seven babyyyy
	int randY = randInt(0, VIEW_HEIGHT - 1); //% VIEW_HEIGHT;
	double randsize = ((double)(randInt(0,45-1)) / 100) + .05;
	Actor* bornStar = new Star(IID_STAR, VIEW_WIDTH - 1, randY, 0, randsize, 3);
	m_actorList.push_back(bornStar);
}


int D = getPlayerKillCount();
int T = getLevelGoal();
int R = T - D;
int M = getNPC_ScreenMax();
int min = 0;
(M > R) ? (min = R) : (min = M);
			//True		//False		//If equal
			//R smaller	//M Smallwe	//Doesn't matter, choose M
int C = getNPC_Count();

if (C < min) {

	//5) to make a new alien ship
	int S1 = 60; //60
	int S2 = 20 + getLevel() * 5; //20
	int S3 = 5 + getLevel() * 10;
	int S = S1 + S2 + S3;

	// S1/S chance for smallgon
	//int randS = rand() % S;
	int randS = randInt(0, S-1);
	if (randS < S1 ) {
		//Make new smallgon
		//int randSmlY = rand() % VIEW_HEIGHT;
		int randSmlY = randInt(0, VIEW_HEIGHT - 1);
		double smlHP = 5 * (1 + (getLevel() - 1)*.1);
		Actor* newSmallgon = new Smallgon(this, VIEW_WIDTH - 1, randSmlY, smlHP);
		m_actorList.push_back(newSmallgon);
		incNPC_Count();
	}

	//S2/S chance of smoregon
	else if (randS < (S1 + S2) && randS > S1) {
		//Make new smoregon
		//int randSmrY = rand() % VIEW_HEIGHT;
		int randSmrY = randInt(0, VIEW_HEIGHT - 1);
		double smrHP = 5 * (1 + (getLevel() - 1)*.1);
		Actor* newSmoregon = new Smoregon(this, VIEW_WIDTH - 1, randSmrY, smrHP);
		m_actorList.push_back(newSmoregon);
		incNPC_Count();
	}

	//S3/S chance for snagglegon
	else if (randS > (S1 + S2)) {
		//int randSngY = rand() % VIEW_HEIGHT;
		int randSngY = randInt(0, VIEW_HEIGHT - 1);
		double sngHP = 10 * (1 + (getLevel() - 1)*.1);
		Actor* newSnagglegon = new Snagglegon(this, VIEW_WIDTH - 1, randSngY, sngHP);
		m_actorList.push_back(newSnagglegon);
		incNPC_Count();
	}




}



//Update score board
updateScoreBoard();
return GWSTATUS_CONTINUE_GAME;
}


void StudentWorld::updateScoreBoard() {
	int lives = getLives();
	int health = m_player->getHealth()*2;
	int score = getScore();
	int level = getLevel();
	int curCab = m_player->getCommAmmoSupply()*100/30;
	int torpedos = m_player->getSpecAmmoSupply(); 


	ostringstream oss;
	oss << "Lives:" << setw(3) << lives << "  ";
	oss << "Health:" << setw(4) << health << "%" << "  ";
	oss << "Score:" << setw(6) << score << "  ";
	oss << "Level:" << setw(3) << level << "  ";
	oss << "Cabbages:" << setw(4) << curCab << "%"<< "  ";
	oss << "Torpedos:" << setw(3) << torpedos << "  ";

	string s = oss.str();

	setGameStatText(s);

}

void StudentWorld::cleanUp()
{
	std::list<Actor*>::iterator cleaner;
	cleaner = m_actorList.begin();
	while (cleaner != m_actorList.end()) {
		//(*cleaner)->setVisible(false);
		delete *cleaner; //Need to 'Delete' the dynamic memory we 'new'-ed in before
		//worried about messing up the list? 
			//List just removes pointer!
		cleaner = m_actorList.erase(cleaner);
	}


}

void StudentWorld::addActor(Actor* newActor) {
	m_actorList.push_back(newActor);
}

void StudentWorld::makeExplosion(int X, int Y) {
	Actor* expl = new Explosion(IID_EXPLOSION, X, Y);
	addActor(expl);
}


bool StudentWorld::checkInBounds(Actor* perp) {
	double X = perp->getX();
	double Y = perp->getY();
	if (X < VIEW_WIDTH && X >= 0) {
		//within X
		if (Y < VIEW_HEIGHT && Y >= 0) {
			//within Y
			return true;
		}
		else { return false; }
	}
	else { return false; }
}


bool StudentWorld::checkPotentialActorMoveInBounds(double x, double y) {

	if (x < VIEW_WIDTH && x >= 0) {
		//within X
		if (y < VIEW_HEIGHT && y >= 0) {
			//within Y
			return true;
		}
		else { return false; }
	}
	else { return false; }



}

bool StudentWorld::checkPotentialNPCMoveInBounds(double x, double y) {

	if (x < VIEW_WIDTH) {
		//within X
		//Nees to fly off screen to the left, allow crossing x=0
		if (y < VIEW_HEIGHT && y >= 0) {
			//within Y
			return true;
		}
		else { return false; }
	}
	else { return false; }



}


bool StudentWorld::checkPlayerCollision(Actor* perp) {
	double R1 = (*perp).getRadius();
	double R2 = (*m_player).getRadius();

	if ( eucledianDist(perp, m_player)  < .75 * (R1 + R2)) {
		//within range of each other
		return true;
	}
	else {
		return false;
	}
}

bool StudentWorld::collisionCheck(Actor* hitter) {

	//See if hitter is in a collideable distance to any other collideable actor
	std::list<Actor*> ::iterator it;
	it = m_actorList.begin();
	double R1 = (*hitter).getRadius();
	
	while (it != m_actorList.end() && (*hitter).isAlive()  ){
	//loop through every member of list
		if (!(**it).isBackground() && !(**it).isGoodie() && (**it).isAlive() && (*it)!=hitter )
		{//Only collideable objects
			double R2 = (**it).getRadius();
			if (eucledianDist(hitter, (*it)) < .75 * (R1 + R2)  ) 
			{
				//Within range of each other
				//Officially collided!
					//Call do damage to each function
				if ( (*hitter).Frednly() ) //If source is friend
				{
					if ( !(**it).Frednly() ) //and target is foe
					{
						if (!((*hitter).isProjectile() && (**it).isProjectile())) //Projectiles pass through each other
						{
							//Permit collision
							(*hitter).collide((**it).getDamage());
							(**it).collide((*hitter).getDamage()); //Netwons Third Law
							return true;
						}
						else { it++; }
					}
					else { it++; }
				}
				else { //If source if foe
					if ( (**it).Frednly() ) { //and target is friend
						if (!((*hitter).isProjectile() && (**it).isProjectile())) //Projectiles pass through each other
						{
							//Permit collision
							(*hitter).collide((**it).getDamage());
							(**it).collide((*hitter).getDamage()); //Netwons Third Law
							return true;
						}
						else { it++; }
					}
					else { it++; }
				 }



			}
			else {it++;	}

		}
		else
		{it++;
		} //Increment if not collideable
		
	}
	return false;
}




double StudentWorld::eucledianDist(Actor* source, Actor* target) {
	double x1 = (*source).getX();
	double y1 = (*source).getY();
	double x2 = (*target).getX();
	double y2 = (*target).getY();

	//Pythagoren Theorem
	//More at: http://rosalind.info/glossary/euclidean-distance/
	double t1 = x2 - x1;
	double t2 = y2 - y1;

	double eucDist = sqrt(t1*t1 + t2*t2);

	return eucDist;




}


void StudentWorld::buryTheDead() {
	std::list<Actor*>::iterator marker;
	marker = m_actorList.begin();
	while (marker != m_actorList.end()) {
			if (!(*marker)->isAlive())
			{
				//(*marker)->setVisible(false);		//delete
				if ((*marker)->isAlien()) {
					decNPC_Count();
				}
     			delete *marker;
				marker = m_actorList.erase(marker); //if out of boundaries
				
			}
			else {
				marker++;
			}
		}
}
