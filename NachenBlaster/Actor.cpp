#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp




 void NachenBlaster::doSomething() {
	//shoot cabbage
	//shoot torpedo
	//move up/down/left/right
	//do nothing
	int userAction = 0;
	if (thisGameWorld()->getKey(userAction)) {
		double X = getX();
		double Y = getY();
		int step = 6;

		switch (userAction) {

		case KEY_PRESS_UP: //move up
		{	//Check if potential move possible
			if (thisGameWorld()->checkPotentialActorMoveInBounds(X, Y + step)) {
				moveTo(X, Y + step);
			}

		break;
		}
		case KEY_PRESS_DOWN: //move down
		{	
			if (thisGameWorld()->checkPotentialActorMoveInBounds(X, Y - step)) {
				moveTo(X, Y - step);
			}
		break;
		}
		case KEY_PRESS_LEFT: //move left
		{	
			if (thisGameWorld()->checkPotentialActorMoveInBounds(X-step, Y)) {
				moveTo(X - step, Y);
			}
		break;
		}
		case KEY_PRESS_RIGHT: //move right
		{
			if (thisGameWorld()->checkPotentialActorMoveInBounds(X + step, Y)) {
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
		{	Actor* shoot = new Cabbage(thisGameWorld(), IID_CABBAGE, X+12, Y); //Spawn 12 to right
			thisGameWorld()->addActor(shoot);
			//Play sound
			thisGameWorld()->playSound(SOUND_PLAYER_SHOOT);
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

		 double x = getX();
		 double y = getY();
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