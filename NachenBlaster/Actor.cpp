#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp




 void NachenBlaster::doSomething() {
	//shoot cabbage
	//shoot torpedo
	//move up/down/left/right
	//do nothing
	int userAction = 0;
	if (m_gameWorld->getKey(userAction)) {
		double X = getX();
		double Y = getY();
		int step = 6;

		switch (userAction) {

		case KEY_PRESS_UP: //move up
		{	//Check if potential move possible
			if (m_gameWorld->checkPotentialActorMoveInBounds(X, Y + step)) {
				moveTo(X, Y + step);
			}

		break;
		}
		case KEY_PRESS_DOWN: //move down
		{	
			if (m_gameWorld->checkPotentialActorMoveInBounds(X, Y - step)) {
				moveTo(X, Y - step);
			}
		break;
		}
		case KEY_PRESS_LEFT: //move left
		{	
			if (m_gameWorld->checkPotentialActorMoveInBounds(X-step, Y)) {
				moveTo(X - step, Y);
			}
		break;
		}
		case KEY_PRESS_RIGHT: //move right
		{
			if (m_gameWorld->checkPotentialActorMoveInBounds(X + step, Y)) {
				moveTo(X + step, Y);
			}
		break;
		}
		case KEY_PRESS_ESCAPE: //leave game
		{	//return GWSTATUS_PLAYER_DIED;
			//Call function to leave game
			break;
		}
		case KEY_PRESS_SPACE: //shoot cabbage
		{	Actor* shoot = new Cabbage(IID_CABBAGE, X, Y, 0, .5, 1);
			m_gameWorld->addActor(shoot);
			break;
		}
		case KEY_PRESS_TAB: //shoot torpedo
		{	break;
		}

		}

	}
}


 bool NonPlayerShootingActor::checkFlownOffLeft(int x) {

	 if (x > 0) {
		 return true;
	 }
	 else {
		 return false;
	 }


 }


 void Smallgon::doSomething() {
	 //Nows your time Smallgon! To action!
	 
	 //1) Check if alive
	 if (isAlive()) {

		 int x = getX();
		 int y = getY();
		 //2) Check if flown off the left part of screen (passed player)
		 if (checkFlownOffLeft(x)) {
			 //3) Check if collided with player

		 }
		 else {
			 setAlive(false); //Mark self dead if offscreen
		 }
	 
	 
	 
	 
	 
	 
	 
	 }
	 else {
		 return; //Return immediately if dead...
	 }



 }