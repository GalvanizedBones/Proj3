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
		{	
			Actor* torp = new Torpedo(true, thisGameWorld(), IID_TORPEDO, X + 12, Y, 0);
			thisGameWorld()->addActor(torp);
			thisGameWorld()->playSound(SOUND_TORPEDO);
			break;
		}

		}

	}
}


 bool NonPlayerShootingActor::checkFlownOffLeft(int x) {
	 if (x > 0) { return true; }
		 else { return false; }
 }

 bool NonPlayerShootingActor::checkTopOrBottom(int y) {
	 if (y == VIEW_HEIGHT-1 || y == 0) { return true; }
	 else { return false; }

 }



 void Smallgon::doSomething() {
	 //Nows your time Smallgon! To action!
	 
	 //1) Check if alive
	 if (isAlive()) {

		 double x = getX();
		 double y = getY();
		 //2) Check if flown off the left part of screen (passed player)
		 if (checkFlownOffLeft(x)) {
			 //3) Check if collided with player or projectile
			 if ((*thisGameWorld()).collisionCheck(this)) {
				 
				 
				 //QEFWFAWEGW
				 //Make Explosion!!!
				 //GAWERGARGVERV



				 return; //Give it up, You're dead bub
			 }

			//4) Check if pathing needs an update
			 if (getNPCPathLength() <= 0 || checkTopOrBottom(y) ) { //or at top/bottom of screen
				 //Time to make a new path

				 if (y >= VIEW_HEIGHT - 1) {
					 //Go down and left
					 setOrientation(-1);
				 }
				 else if (y <= 0) {
					 //Go up and left
					 setOrientation(1);
				 }
				 else if (getNPCPathLength() <=0) {
					 //Randomly Select direction
						//i) left and up
						//ii) due left
						//iii) left and down
					 int Rdir = (rand() % 3) - 1;
					 setOrientation(Rdir);

					 int Rpth = (rand() % 32) + 1;
					 setNPCPAthLength(Rpth);
				 }
				 else {
					 //Randomly Select direction
						 //i) left and up
						 //ii) due left
						 //iii) left and down
					 //Randomly select flight path
						// inbetween 1 and 32
					 int Rdir = (rand() % 3) - 1;
					 setOrientation(Rdir);
					int  Rpth = (rand() % 32) + 1;
					 setNPCPAthLength(Rpth);
				 }

			 }

			 //5) If Player is to the left of the Smallgon
				// and Smallgon has a y coord within [-4 to 4] pixles of Playes
					//Then, chance Smallgon will:
						//Fire turnip toward Nachenblaster
							//Add turnig 14 pixel to left of center of the smallgon ship
							//Play a SOUND_ALIEN_SHOOT fx
							//End current tick
			 int px = thisGameWorld()->getPlayerX(); 
			 int py = thisGameWorld()->getPlayerY();

			 if (px < x) {
				 //Player to the left
				 if (py <= y + 4 && py >= y - 4) {
					 //In vertical range
						//Target acquired.....
					 int smlchance = (20 / thisGameWorld()->getLevel()) + 5;
					 int randSShoot = rand() % smlchance;
					 if (randSShoot == 1) //1 in smlChance chance
					 {
						 Actor* shoot = new Turnip(thisGameWorld(), IID_TURNIP, x - 16, y); //Spawn 12 to right
						 thisGameWorld()->addActor(shoot);
						 //Play sound
						 thisGameWorld()->playSound(SOUND_ALIEN_SHOOT);

					 }
				 }
				 





			 }


			 //6) Smallgon will try to move in current direction
				//Reduce flight path by one
					//Case 1: Move N up, N left 
						//Where N is current travel speed
					//Case 2: Move N down and N left
						//Where N is current travel speed
					//Case 3: Due left, N=

			 int N = getNPCSpeed();
			 decFlightPath();
			 switch (getOrientation()) {
			 case(1):
				 if (thisGameWorld()->checkPotentialNPCMoveInBounds(x - N, y + N) ){
				 moveTo(x - N, y + N);
				 }
				 else {
					 moveTo(x - N, y);
				 }
				 break;
			 case(0):
					 moveTo(x - N, y);
				 break;
			 case (-1):
				 if (thisGameWorld()->checkPotentialNPCMoveInBounds(x - N, y - N)) {
					 moveTo(x - N, y - N);
				 }
				 else {
					 moveTo(x - N, y);
				 }
				 break;
			 default:
				 std::cerr << "errOrientation";
			 }

			 //7) After moving, check again for a collision
			 (*thisGameWorld()).collisionCheck(this);


		 }
		 else {
			 setAlive(false); //Mark self dead if offscreen
		 }
	 }
	 else {
		 return; //Return immediately if dead...
	 }



 }


 ///////////Projectile 


 void Projectile::doSomething() {
	 //1) Check if alive
	 if (isAlive()) {

		 //2) Check if flown off screen
		 if (thisGameWorld()->checkInBounds(this)) {
			 //3) Check if collided yet
			 if ((*thisGameWorld()).collisionCheck(this)) {
				 //If collsion with player
				 //Damage player  \
				 				 //Set self dead   >taken care of in collide function
//Do nothing else this tick
				 return;
			 }
			

			 doSomethingSpecific();
			 // 4 & 5 are specific to the projectile

												//6) After moving, check again for a collision
			 if ((*thisGameWorld()).collisionCheck(this)) {
				 //Same as part 3
				 return;
			 }
		 }
		 else {
			 setAlive(false);
			 //Mark dead if off screen
		 }
	 }
	 //Dont do anything if not alive

 }






 ///////////////////CABBAGE
 void Cabbage::doSomethingSpecific() {
	 double X = getX();
	 double Y = getY();
	 X = X + 8; //move 8 to the right each tick
	 moveTo(X, Y);
	 setDirection(getDirection() - 20);

 }




 //////////////////////TURNIP

 void Turnip::doSomethingSpecific() {
	 //4) If not collided, move to the left by 6
	 double X = getX();
	 double Y = getY();
	 X = X - 6; //move to the left each tick
	 moveTo(X, Y);

	 //5) rotate self 20 deg CCW
	 //Use set direction function from graphObject
	 setDirection(getDirection() - 20); //Guessing CCW is negative
	 								    //Seems setDirection funct makes postive anyways...
 }

 void Torpedo::doSomethingSpecific() {
	 double X = getX();
	 double Y = getY();
	 int step = 0;
	 (Frednly()) ? (step = 8) : (step = -8);
	 X = X + step;
	 moveTo(X, Y);


 }

 /////////////////Shootingactor

void ShootingActor::collide(double damage) {
	 subractHealth(damage);
	 //Incurring damage! 
	 //Either by a torpedo collision
	 //or a collision with another ship!
	 if (getHealth() < 0) {
		 setAlive(false);
		 postDeath(); 
	 }
 }


///////////////SMALLGON
void Smallgon::postDeath() {
        	(thisGameWorld())->incPlayerKillCount();
			(thisGameWorld())->makeExplosion(getX(), getY());
	//Make Explosion

}