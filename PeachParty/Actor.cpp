#include "Actor.h"
#include "StudentWorld.h"
#include <cstdlib>
#include <vector>

//TO DO
//      FORK AT THE HORIZONTAL T'S

//FIX when BOO is on same square as PLAYER
//FIX THE DROPPING SQUARES





// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor (int imageID, int x, int y, StudentWorld* world,int dir, int depth, double size ): GraphObject(imageID, x, y, dir, depth, size), state(WAITING_OR_INACTIVE)
{
    this->world = world;
    toBeDestroyed = false;
    toDropSquare = false;
    isActivePeach = true;
    isActiveYoshi = true;
    
    
    
}

 bool Actor::getIsVortex()
{
     return false;
 }

bool Actor::overlaps(Actor* other)
{
    int disX = abs(getX() - other->getX());
    int disY = abs(getY() - other->getY());
    
    if(disX <16 && disY<16)
    {
        return true;
    }
    return false;
}

bool Actor::isDrop()
{
    return false;
}

 bool Actor::isBaddie()
{
     return false;
}
bool Actor::isSquare()
{
    return false;
}

bool Actor::isToBeDestroyed()
{
    return toBeDestroyed;
}

void Actor::setToBeDestroyed(bool d)
{
    toBeDestroyed = d;
}

bool Actor::isToDropSquare()
{
    return toDropSquare;
}
void Actor::setIsToDropSquare(bool d)
{
    toDropSquare = d;
}
bool Actor::getHasBeenImpacted()
{
    return hasBeenImpacted;
}
void Actor::setHasBeenImpacted(bool d)
{
    hasBeenImpacted = d;
}

bool Actor::getIsImpactable()
{
    return false;
}




 Actor::~Actor()
{
    
 }

int Actor::getState() const
{
    return state;
}
void Actor::setState(int newState)
{
    state = newState;
}

StudentWorld* Actor::getWorld() const
{
    return world;
}


bool Actor::getIsActivePeach()
{
    return isActivePeach;
}
bool Actor::getIsActiveYoshi()
{
    return isActiveYoshi;
}


void Actor::setIsActivePeach(bool isActive)
{
    isActivePeach = isActive;
}
void Actor::setIsActiveYoshi(bool isActive)
{
    isActiveYoshi = isActive;
}


void Actor::setPlayerActives()
{
    if( getWorld()->getPeach()->getX() != getX() || getWorld()->getPeach()->getY() != getY())
    {
       
        setIsActivePeach(true);
       
    }
    
    
     
    if( getWorld()->getYoshi()->getX() != getX() || getWorld()->getYoshi()->getY() != getY())
    {
        setIsActiveYoshi(true);
        
    }
}


//


//CHARACTERS CLASS


//

int Character::getWalkingDir()
{
    return walkingDir;
}
void Character::setWalkingDir(int dir)
{
    walkingDir = dir;
}

int Character::getOppositeWalkingDir()
{
    if(walkingDir == right)
        return ACTION_LEFT;
    else if(walkingDir == up)
        return ACTION_DOWN;
    else if(walkingDir == left)
        return ACTION_RIGHT;
    else
        return ACTION_UP;
}

Character::Character(int imageID, int x, int y,StudentWorld* world  ,int dir, int walkingDir): Actor(imageID, x, y,world, dir)
{
    this->walkingDir  = walkingDir;
    ticks_to_move = 0;
    justTeleported = false;
}



int Character::getTicks()
{
    return ticks_to_move;
}

void Character::setTicks(int t)
{
    ticks_to_move = t;
}


bool Character::isValidDirRight()
{
        
    if(getWorld() ->getBoard().getContentsOf(getX()/16 + 1 , getY()/16) != Board::empty )
            return true;
    return false;
        
}

bool Character::isValidDirLeft()
{
    if(getWorld() ->getBoard().getContentsOf(getX()/16 -1 , getY()/16) != Board::empty )
            return true;
    return false;
}
bool Character::isValidDirUp()
{
    if(getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 + 1) != Board::empty )
            return true;
    return false;
}
bool Character::isValidDirDown()
{
    if(getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 - 1) != Board::empty )
            return true;
    return false;
}

bool Character::hasInvalidDir()
{
    if(walkingDir == right && !isValidDirRight())
        return true;
    if(walkingDir == left && !isValidDirLeft())
        return true;
    if(walkingDir == up && !isValidDirUp())
        return true;
    if(walkingDir == down && !isValidDirDown())
        return true;
    return false;
}



bool Character::isAtFork()
{
    
    if(getTicks()%8!=0)
        return false;
    
    
    
    //horizontal T's
    if(getWalkingDir() == right &&
       getWorld() ->getBoard().getContentsOf(getX()/16 + 1, getY()/16) == Board::empty
       && getWorld() ->getBoard().getContentsOf(getX()/16 - 1, getY()/16) != Board::empty
       &&(getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 + 1) != Board::empty  &&  getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 - 1) != Board::empty ))
        return true;
    if(getWalkingDir() == left &&
       getWorld() ->getBoard().getContentsOf(getX()/16 - 1, getY()/16) == Board::empty
       && getWorld() ->getBoard().getContentsOf(getX()/16 + 1, getY()/16) != Board::empty
       &&(getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 + 1) != Board::empty  &&  getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 - 1) != Board::empty ))
        return true;
    
    //vertical T's
    if(getWalkingDir() == up &&
       getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 +1) == Board::empty
       && getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 -1) != Board::empty
       &&(getWorld() ->getBoard().getContentsOf(getX()/16 + 1, getY()/16) != Board::empty  &&  getWorld() ->getBoard().getContentsOf(getX()/16 - 1, getY()/16) != Board::empty ))
        return true;
    if(getWalkingDir() == down &&
       getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 -1) == Board::empty
       && getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 +1) != Board::empty
       &&(getWorld() ->getBoard().getContentsOf(getX()/16 + 1, getY()/16) != Board::empty  &&  getWorld() ->getBoard().getContentsOf(getX()/16 - 1, getY()/16) != Board::empty ))
        return true;
    
    
    
    if(getWalkingDir() == right &&
       getWorld() ->getBoard().getContentsOf(getX()/16 + 1, getY()/16) != Board::empty
       && getWorld() ->getBoard().getContentsOf(getX()/16 - 1, getY()/16) != Board::empty
       &&(getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 + 1) != Board::empty  ||  getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 - 1) != Board::empty ))
        return true;
    if(getWalkingDir() == left && getWorld() ->getBoard().getContentsOf(getX()/16 - 1, getY()/16) != Board::empty && getWorld() ->getBoard().getContentsOf(getX()/16 + 1, getY()/16) != Board::empty &&(  getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 + 1) != Board::empty  ||  getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 - 1) != Board::empty ))
        return true;
    if(getWalkingDir() == up && getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 + 1) != Board::empty && getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 - 1) != Board::empty &&(  getWorld() ->getBoard().getContentsOf(getX()/16 + 1, getY()/16) != Board::empty  ||  getWorld() ->getBoard().getContentsOf(getX()/16 - 1, getY()/16) != Board::empty ))
        return true;
    if(getWalkingDir() == down &&  getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 - 1) != Board::empty && getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 + 1) != Board::empty &&(  getWorld() ->getBoard().getContentsOf(getX()/16 + 1, getY()/16) != Board::empty  ||  getWorld() ->getBoard().getContentsOf(getX()/16 - 1, getY()/16) != Board::empty ))
        return true;
    
    
    return false;
}

bool Character::getJustTeleported()
{
    return justTeleported;
}
void Character::setJustTeleported(bool d)
{
    justTeleported = d;
}

void Character::changeRandomDir()
{
    int dir[] = {0,0,0,0};
    //random
    
    
    if(isValidDirRight())
        dir[0] = 1;
    if(isValidDirUp())
        dir[1] = 1;
    if(isValidDirLeft())
        dir[2] = 1;
    if(isValidDirDown())
        dir[3] = 1;
    
    int rand = randInt(0,3);
    
    while(dir[rand] == 0)
    {
        rand = randInt(0,3);
        
    }
    //rand = 0 : right
    //rand = 1 : up
    //rand = 2 : leftr
    //rand = 3 : down
    switch(rand)
    {
        case 0: //right
        {
            if(getWalkingDir() == left)
                setDirection(right);
            setWalkingDir(right);
            break;
        }
        case 1: //up
        {
            if(getWalkingDir() == left)
                setDirection(right);
            setWalkingDir(up);
            break;
        }
        case 2: //left
        {
            setDirection(left);
            setWalkingDir(left);
            break;
        }
        case 3: //down
        {
            if(getWalkingDir() == left)
                setDirection(right);
            setWalkingDir(down);
            break;
        }
    }
}


void Character::teleportRandom()
{
    std::vector<Actor*> vec;
    
    int i = 0;
    while(getWorld()->getActorAt(i)!= nullptr && i<getWorld()->getNumActors())
    {

        if(getWorld()->getActorAt(i)->isSquare())
       {
           vec.push_back(getWorld()->getActorAt(i));
        }
        i++;
    
    //
    }
    int rand = randInt(0,vec.size()-1);
    int  newX = vec[rand]->getX();
    int newY = vec[rand]->getY();
    moveTo(newX,newY);
}



//

//AVATAR

//




Avatar::Avatar(int imageID, int x, int y, StudentWorld* world, int playerNum, int walkingDir): Character(imageID, x, y, world)
{
    walkingDir = right;
    
    die_roll = 0;
    nCoins = 0;
    nStars = 0;
    this->playerNum = playerNum;
    //CHANGE TO FALSE
    hasVortex = false;
    toIntroVortex = false;
}

int Avatar::getPlayerNum()
{
    return playerNum;
}

void Avatar::blueLanded()
{
    nCoins = nCoins+ 3;
}
void Avatar::redLanded()
{
    if(nCoins<3)
        nCoins = 0;
    else
        nCoins= nCoins-3;
}

void Avatar::starLanded()
{
    nCoins-=20;
    nStars++;
}




int Avatar::getRoll()
{
    return die_roll;
}


int Avatar::getCoins()
{
    return nCoins;
}

int Avatar::getStars()
{
    return nStars;
}
 
bool Avatar::getHasVortex()
{
    return hasVortex;
}

void Avatar::setHasVortex(bool v)
{
    hasVortex = v;
}


bool Avatar::getToIntroVortex()
{
    return toIntroVortex;
}
void Avatar::setToIntroVortex(bool d)
{
   toIntroVortex = d;
}

void Avatar::giveCoins(int sum)
{
    nCoins+=sum;
}

void Avatar::takeCoins(int sum)
{
    nCoins -= sum;
}

void Avatar::giveStars(int sum)
{
    nStars +=sum;
}
void Avatar::takeStars(int sum)
{
    nStars -=sum;
}



void Avatar::doSomething()
{
    
    if(getState() == WAITING_OR_INACTIVE)
    {
        //NEED TO FINISH
        if(hasInvalidDir() && getJustTeleported())
        {
            //MAKESURE that THIS DOESNT HAPPEN IF AVATAR LANDS ON A CORNER
            changeRandomDir();
            setJustTeleported(false);
        }
        
        int act = getWorld()->getAction(getPlayerNum());
        
        
      
           if(act== ACTION_ROLL)
           {
               die_roll = randInt(1,10);
               
               //REMOVE
               //die_roll = 1;
               
               setTicks(die_roll*8);
               setState(WALKING_OR_ACTIVE);
           }
       
        else if(act == ACTION_FIRE && getHasVortex())
        {
            
    //            Introduce a new Vortex projectile on the square directly in front of the Avatar in the Avatar's current walk direction.
            //NEED TO DO THIS
            setToIntroVortex(true);
            
    //            Play the SOUND_PLAYER_FIRE sound using GameWorld’s playSound() method.
            getWorld()->playSound(SOUND_PLAYER_FIRE);
    //            Update your Avatar so it no longer has a Vortex to shoot.
            hasVortex = false;
            
        }
        
        
       else
           return;
       
    }
    if(getState() == WALKING_OR_ACTIVE)
    {
        //check if it can move
        if(getWorld()->getBoard().getContentsOf(getX()/16, getY()/16) == Board::down_dir_square ||getWorld()->getBoard().getContentsOf(getX()/16, getY()/16) == Board::up_dir_square || getWorld()->getBoard().getContentsOf(getX()/16, getY()/16) == Board::left_dir_square || getWorld()->getBoard().getContentsOf(getX()/16, getY()/16) == Board::right_dir_square  )
        {}
        
       else if(isAtFork() )
        {
            int act = getWorld()->getAction(playerNum);
            
           if(act!= ACTION_NONE && act!= ACTION_ROLL && act!=getOppositeWalkingDir())
           {
               
               
               if(act == ACTION_RIGHT && isValidDirRight())
               {
                   if(getDirection() == left)
                       setDirection(right);
                   setWalkingDir(right);
               }
               else if(act == ACTION_LEFT && isValidDirLeft())
               {
                   
                    setDirection(left);
                   setWalkingDir(left);
               }
               else if(act == ACTION_DOWN && isValidDirDown())
               {
                  
                   if(getDirection() == left)
                       setDirection(right);
                   setWalkingDir(down);
                   //std:: cout << "HIHIHII" << std::endl;
               }
               else if(act == ACTION_UP && isValidDirUp())
               {
                   if(getDirection() == left)
                       setDirection(right);
                   setWalkingDir(up);
               }
               else
                   return;
              

           }
            else
                return;
        }
            
        else{
        
        //walking dir right and change
       if(getWalkingDir() == right && !isValidDirRight() )
       {
           if(isValidDirUp())
               //REPLACE WITH ISVALID FUNCSSSS
           {
               
               //find function or create to change walking direction
               setWalkingDir(up);
           }
           else if(isValidDirDown())
           {
               setWalkingDir(down);
               
           }
       }
        //walk dir left and change
        else if(getTicks()%8 == 0 && getWalkingDir() == left)
        {
                
              if( !isValidDirLeft()/*getWorld() ->getBoard().getContentsOf(getX()/16 -1, getY()/16) == Board::empty*/ )
        {
            if(isValidDirUp())
            {
                setWalkingDir(up);
                setDirection(right);
            }
            else if(isValidDirDown())
            {
                setWalkingDir(down);
                setDirection(right);
            }
        }
        }
        //walk dir up and change
        else if(getWalkingDir() == up && /*getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 + 1) == Board::empty */ !isValidDirUp())
        {
            if(isValidDirRight())
            {
                setWalkingDir(right);
            }
            else if(isValidDirLeft())
            {
                setWalkingDir(left);
                setDirection(left);
            }
        }
        
        else if(getTicks()%8 == 0 && getWalkingDir() == down)
        {
         if(/*getWorld() ->getBoard().getContentsOf(getX()/16, getY()/16 - 1) == Board::empty*/ !isValidDirDown() )
            {
                //std:: cout << "HIHIHII" << std::endl;
                if(isValidDirRight())
                {
                    setWalkingDir(right);
                }
                else if(isValidDirLeft())
                {
                    setWalkingDir(left);
                    setDirection(left);
                }
            }
        }
      }
    
        //still in if walking state
        moveAtAngle(getWalkingDir(), 2);
        setTicks(getTicks()-1);
        if(getTicks() == 0)
            setState(WAITING_OR_INACTIVE);
        
        
    }
}


//
//
//BADDIE
//
//

Baddie::Baddie(int imageID, int x, int y, StudentWorld* world, int dir, int bowOrBoo): Character(imageID, x, y, world)
{
    pauseCounter = 180;
    setState(PAUSED);
    
    
    hasTaken = false;
    this->bowOrBoo = bowOrBoo;
    
    
}


bool Baddie::getIsImpactable()
{
    return true;
}


void Baddie::doSomething()
{
    
    if(getHasBeenImpacted())
    {
        teleportRandom();
        setWalkingDir(right);
        setDirection(right);
        setState(PAUSED);
        setTicks(180);
        setHasBeenImpacted(false);
        
    }
    
    
    setPlayerActives();
    
    
    if(getState() == PAUSED )
    {
       
        
        
        
        
        
        if(getX() == getWorld()->getPeach()->getX() && getY() == getWorld()->getPeach()->getY() && getWorld()->getPeach()->getState() == WAITING_OR_INACTIVE && getIsActivePeach())
        {
            if(bowOrBoo == BOWSER)
            {
                int rand = randInt(1,2);
                    
                    
                if(rand == 2)
                {
                    getWorld()->getPeach()->takeCoins(getWorld()->getPeach()->getCoins());
                    getWorld()->getPeach()->takeStars(getWorld()->getPeach()->getStars());
                    getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
                   
                }
                setIsActivePeach(false);
                    
            }
            if(bowOrBoo == BOO)
            {
                //BOO STUFF
                int rand = randInt(1,2);
                
                if(rand == 1 )
                {
                    //swap player coins
                    int tempCoins = getWorld()->getPeach()->getCoins();
                    getWorld()->getPeach()->takeCoins(getWorld()->getPeach()->getCoins());
                    getWorld()->getPeach()->giveCoins(getWorld()->getYoshi()->getCoins());
                    
                    getWorld()->getYoshi()->takeCoins(getWorld()->getYoshi()->getCoins());
                    getWorld()->getYoshi()->giveCoins(tempCoins);
                    
                    
                    
                }
                else
                {
                    // swap player stars
                    int tempStars = getWorld()->getPeach()->getStars();
                    getWorld()->getPeach()->takeStars(getWorld()->getPeach()->getStars());
                    getWorld()->getPeach()->giveStars(getWorld()->getYoshi()->getStars());
                    
                    getWorld()->getYoshi()->takeStars(getWorld()->getYoshi()->getStars());
                    getWorld()->getYoshi()->giveStars(tempStars);
                    
                    
                }
                
                getWorld()->playSound(SOUND_BOO_ACTIVATE);
                setIsActivePeach(false);
            }
            
        }
        
       
        
       
        
        
        
        if(getX() == getWorld()->getYoshi()->getX() && getY() == getWorld()->getYoshi()->getY() && getWorld()->getYoshi()->getState() == WAITING_OR_INACTIVE && getIsActiveYoshi())
        {
            if(bowOrBoo == BOWSER)
            {
            int rand = randInt(1,2);
                
                
            if(rand == 2)
            {
                getWorld()->getYoshi()->takeCoins(getWorld()->getYoshi()->getCoins());
                getWorld()->getYoshi()->takeStars(getWorld()->getYoshi()->getStars());
                getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
                setIsActiveYoshi(false);
            }
                
                
            }
            if(bowOrBoo == BOO )
            {
                //BOO STUFF
                int rand = randInt(1,2);
                
                if(rand == 1)
                {
                    //swap player coins
                    int tempCoins = getWorld()->getPeach()->getCoins();
                    getWorld()->getPeach()->takeCoins(getWorld()->getPeach()->getCoins());
                    getWorld()->getPeach()->giveCoins(getWorld()->getYoshi()->getCoins());
                    
                    getWorld()->getYoshi()->takeCoins(getWorld()->getYoshi()->getCoins());
                    getWorld()->getYoshi()->giveCoins(tempCoins);
                    
                }
                else
                {
                    // swap player stars
                    int tempStars = getWorld()->getPeach()->getStars();
                    getWorld()->getPeach()->takeStars(getWorld()->getPeach()->getStars());
                    getWorld()->getPeach()->giveStars(getWorld()->getYoshi()->getStars());
                    
                    getWorld()->getYoshi()->takeStars(getWorld()->getYoshi()->getStars());
                    getWorld()->getYoshi()->giveStars(tempStars);
                    
                }
                getWorld()->playSound(SOUND_BOO_ACTIVATE);
                setIsActiveYoshi(false);
            }
        }
        
        
        pauseCounter--;
        
        
        
        if(pauseCounter == 0)
        {
            int squares = 0;
            if(bowOrBoo == BOWSER)
                squares = randInt(1,10);
            else
                squares = randInt(1,3);
            
            
            //REMOVE LATER
           // squares = 5;
        
            setTicks(squares*8);
    
            changeRandomDir();
            
            setState(WALKING_OR_ACTIVE);
            
        }
        
        
    }
    
    
    
    if(getState() == WALKING_OR_ACTIVE)
    {
        setIsActiveYoshi(true);
        setIsActivePeach(true);
        //PROBLEM WITH UP AND DOWN DIRECTIONAL TURNING
        
        if(  getTicks()%8 == 0 && isAtFork())
                changeRandomDir();
        
        else
        {
                
        if  (getWalkingDir() == right && !isValidDirRight())
        {
            if(isValidDirUp())
                setWalkingDir(up);
            else
                setWalkingDir(down);
        }
        else if( getTicks()%8 == 0 && (getWalkingDir() == left && !isValidDirLeft()))
        {
            if(isValidDirUp())
            {
                setDirection(right);
                setWalkingDir(up);
            }
            else
            {
                setDirection(right);
                setWalkingDir(down);
            }
        }
        else if( (getWalkingDir() == up && !isValidDirUp()))
        {
            if(isValidDirRight())
            {
                setWalkingDir(right);
            }
            else
            {
                setDirection(left);
                setWalkingDir(left);
                
            }
        }
        else if( getTicks()%8 == 0 && (getWalkingDir() == down && !isValidDirDown()))
        {
            if(isValidDirRight())
            {
                setWalkingDir(right);
            }
            else
            {
                setDirection(left);
                setWalkingDir(left);
            }
        }
            
      }
        
       //move two pixels in direction
        moveAtAngle(getWalkingDir(), 2);
        setTicks(getTicks() -1);
        if(getTicks() == 0)
        {
            setState(PAUSED);
            pauseCounter = 180;
            //DEPOST DROPPING SquAER
            
            if(bowOrBoo == BOWSER)
            {
                int prob = randInt(1,4);
                
                //remove
                //prob = 1;
                
                if(prob == 1)
                {
                    
                    setIsToDropSquare(true);
                    getWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
                }
            }
            
        }
            
    }
    
    
    
}

 bool Baddie::isBaddie()
{
     return true;
 }







//



//SQUARE CLASS

//

Square::Square(int imageID, int x, int y, StudentWorld* world, int dir): Actor(imageID, x, y, world, dir, 1, 1)
{
    
    
}

bool Square::isSquare()
{
    return true;
}



bool Square::hasLandedPeach(Avatar* peach)
{
    if(peach->getTicks() <=1)
    {
        if( peach->getState() == WAITING_OR_INACTIVE && getIsActivePeach())
            {
            
            if(peach->getX()== getX()
               && peach->getY() == getY())
                {
                    return true;
                }
            }
    }
    return false;
}
bool Square::hasLandedYoshi(Avatar* yoshi)
{
    if(yoshi->getTicks() <=1)
    {
        if( yoshi->getState() == WAITING_OR_INACTIVE && getIsActiveYoshi())
            {
            
            if(yoshi->getX()== getX()
               && yoshi->getY() == getY())
                {
                    return true;
                }
            }
    }
    return false;
}










CoinSquare::CoinSquare(int imageID, int x, int y, StudentWorld* world, int dir, int color): Square(imageID, x, y, world, dir)
{
    
    
    this->color = color;
    setState(WALKING_OR_ACTIVE);
}





void CoinSquare::doSomething()
{
    
    setPlayerActives();
    
    
    
    if(hasLandedPeach(getWorld()->getPeach()))
            {
                if(color == BLUE)
                {
                    getWorld()->getPeach()->blueLanded();
                getWorld()->playSound(SOUND_GIVE_COIN);
                }
                if(color == RED)
                {
                    getWorld()->getPeach()->redLanded();
                    getWorld()->playSound(SOUND_TAKE_COIN);
                }
                
                
                setIsActivePeach(false);
                
            }
        //incase they land at same time
       
        
    
         
        //list of pointers to characters
    
    
    
    
    if(hasLandedYoshi(getWorld()->getYoshi()))
        {
            if(color == BLUE)
            {
                getWorld()->getYoshi()->blueLanded();
            getWorld()->playSound(SOUND_GIVE_COIN);
            }
            if(color == RED)
            {
                getWorld()->getYoshi()->redLanded();
                getWorld()->playSound(SOUND_TAKE_COIN);
            }
            setIsActiveYoshi(false);
        }
        //incase they land at same time
       
        
        
         //list of pointers to characters
    
    
}


StarSquare::StarSquare(int imageID, int x, int y, StudentWorld* world, int dir): Square(imageID, x, y, world, dir)
{
    
}

void StarSquare::doSomething()
{
    
    setPlayerActives();
    
    if(( (getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY())||hasLandedPeach(getWorld()->getPeach())) && getIsActivePeach() )
    {
         if(getWorld()->getPeach()->getCoins() < 20)
             return;
        else
        {
            getWorld()->getPeach()->starLanded();
            getWorld()->playSound(SOUND_GIVE_STAR);
            setIsActivePeach(false);
        }
    }
    if(((getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY())||hasLandedYoshi(getWorld()->getYoshi())) && getIsActiveYoshi())
    {
         if(getWorld()->getYoshi()->getCoins() < 20)
             return;
        else
        {
            getWorld()->getYoshi()->starLanded();
            getWorld()->playSound(SOUND_GIVE_STAR);
            setIsActiveYoshi(false);
        }
    }
    
    
    
}






DirectionalSquare::DirectionalSquare(int imageID, int x, int y, StudentWorld* world, int dir): Square(imageID,  x,  y, world,  dir)
{}

void DirectionalSquare::doSomething()
{
   if((getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY()))
   {
       
       getWorld()->getPeach()->setWalkingDir(getDirection());
       
       if(getWorld()->getPeach()->getDirection() == left && (getDirection() == down || getDirection() == up))
           getWorld()->getPeach()->setDirection(right);
       
       if(getWorld()->getPeach()->getDirection() == right && (getDirection() == left))
           getWorld()->getPeach()->setDirection(left);
       
   }
    if((getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY()))
    {
        getWorld()->getYoshi()->setWalkingDir(getDirection());
        
        if(getWorld()->getYoshi()->getDirection() == left && (getDirection() == down || getDirection() == up))
            getWorld()->getYoshi()->setDirection(right);
        
        if(getWorld()->getYoshi()->getDirection() == right && (getDirection() == left))
            getWorld()->getYoshi()->setDirection(left);

    }
       
}


BankSquare::BankSquare(int imageID, int x, int y, StudentWorld* world, int dir): Square(imageID, x, y, world, dir)
{};


void BankSquare::doSomething()
{
    setPlayerActives();
    
    
    
    
    if(hasLandedPeach(getWorld()->getPeach()) && getIsActivePeach())
    {
        getWorld()->getPeach()->giveCoins(getWorld()->getBankSum());
        getWorld()->emptyBank();
        getWorld()->playSound(SOUND_WITHDRAW_BANK);
        setIsActivePeach(false);
        
    }
    if(hasLandedYoshi(getWorld()->getYoshi()) && getIsActiveYoshi())
    {
        getWorld()->getYoshi()->giveCoins(getWorld()->getBankSum());
        getWorld()->emptyBank();
        getWorld()->playSound(SOUND_WITHDRAW_BANK);
        setIsActiveYoshi(false);
    }
    
    if((getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY()) && !(getWorld()->getPeach()->getState() == WAITING_OR_INACTIVE))
    {
        
            if(getWorld()->getPeach()->getCoins() < 5)
            {
                getWorld()->giveBank(getWorld()->getPeach()->getCoins());
                getWorld()->getPeach()->takeCoins(getWorld()->getPeach()->getCoins());
            }
            else
            {
                getWorld()->giveBank(5);
                getWorld()->getPeach()->takeCoins(5);
            }
            
            getWorld()->playSound(SOUND_DEPOSIT_BANK);
        
    }
    
    if((getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY()) && !(getWorld()->getYoshi()->getState() == WAITING_OR_INACTIVE))
    {
        
            if(getWorld()->getYoshi()->getCoins() < 5)
            {
                getWorld()->giveBank(getWorld()->getYoshi()->getCoins());
                getWorld()->getYoshi()->takeCoins(getWorld()->getYoshi()->getCoins());
            }
            else
            {
                getWorld()->giveBank(5);
                getWorld()->getYoshi()->takeCoins(5);
            }
            
            getWorld()->playSound(SOUND_DEPOSIT_BANK);
        
    }
}


EventSquare::EventSquare(int imageID, int x, int y, StudentWorld* world, int dir): Square(imageID, x, y, world, dir)
{}

void EventSquare::teleportPlayers()
{
    
    
    
    int tempX = getWorld()->getPeach()->getX();
    int tempY = getWorld()->getPeach()->getY();
    getWorld()->getPeach()->moveTo(getWorld()->getYoshi()->getX(), getWorld()->getYoshi()->getY());
    getWorld()->getYoshi()->moveTo(tempX,tempY);
    
    int tempTick = getWorld()->getPeach()->getTicks();
    getWorld()->getPeach()->setTicks(getWorld()->getYoshi()->getTicks());
    getWorld()->getYoshi()->setTicks(tempTick);
    
    int tempDir = getWorld()->getPeach()->getWalkingDir();
    getWorld()->getPeach()->setWalkingDir(getWorld()->getYoshi()->getWalkingDir());
    getWorld()->getYoshi()->setWalkingDir(tempDir);
    
    int tempSprite = getWorld()->getPeach()->getDirection();
    getWorld()->getPeach()->setDirection(getWorld()->getYoshi()->getDirection());
    getWorld()->getYoshi()->setDirection(tempSprite);
    
    int tempState = getWorld()->getPeach()->getState();
    getWorld()->getPeach()->setState(getWorld()->getYoshi()->getState());
    getWorld()->getYoshi()->setState(tempState);
}


void EventSquare::doSomething()
{
    setPlayerActives();
    
    int rand = randInt(1,3);
    //rand = 2;
    
    if(hasLandedPeach(getWorld()->getPeach()) && getIsActivePeach())
    {
        if(rand == 1)
        {
            getWorld()->getPeach()->teleportRandom();
            getWorld()->getPeach()->setJustTeleported(true);
            getWorld()->playSound(SOUND_PLAYER_TELEPORT);
            
            
            
        }
        else if(rand == 2)
        {
            //teleport with other player
            
            teleportPlayers();
            
            setIsActiveYoshi(false);
            getWorld()->playSound(SOUND_PLAYER_TELEPORT);
            
            
            
        }
        else
        {
            
            
            getWorld()->getPeach()->setHasVortex(true);
           getWorld()->playSound(SOUND_GIVE_VORTEX);
            setIsActivePeach(false);
        }
        
    }
    if(hasLandedYoshi(getWorld()->getYoshi()) && getIsActiveYoshi())
    {
        if(rand == 1)
        {
            getWorld()->getYoshi()->teleportRandom();
            getWorld()->getYoshi()->setJustTeleported(true);
            getWorld()->playSound(SOUND_PLAYER_TELEPORT);
        }
        else if(rand == 2)
        {
            //teleport with other player
            teleportPlayers();
            setIsActivePeach(false);
            
            getWorld()->playSound(SOUND_PLAYER_TELEPORT);
        }
        else
        {
            //give player vortex
            
            getWorld()->getYoshi()->setHasVortex(true);
           getWorld()->playSound(SOUND_GIVE_VORTEX);
            setIsActiveYoshi(false);
        }
        
    }
    
    
    
}


DroppingSquare::DroppingSquare(int imageID, int x, int y, StudentWorld* world, int dir): Square(imageID, x, y, world, dir)
{
    
}

void DroppingSquare::doSomething()
{
    setPlayerActives();
    int rand = randInt(1,2);
    if(hasLandedPeach(getWorld()->getPeach()) && getIsActivePeach())
    {
        if(rand == 1)
        {//deduct 10 coins
            if(getWorld()->getPeach()->getCoins()<=10)
                getWorld()->getPeach()->takeCoins(getWorld()->getPeach()->getCoins());
            else
                getWorld()->getPeach()->takeCoins(10);
                
        }
        else
        {
            if(getWorld()->getPeach()->getStars()>=1)
                getWorld()->getPeach()->takeStars(1);
        }
        setIsActivePeach(false);
        getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
        
    }
    if(hasLandedYoshi(getWorld()->getYoshi())&& getIsActiveYoshi())
    {
        if(rand == 1)
        {//deduct 10 coins
            if(getWorld()->getYoshi()->getCoins()<=10)
                getWorld()->getYoshi()->takeCoins(getWorld()->getYoshi()->getCoins());
            else
                getWorld()->getYoshi()->takeCoins(10);
                
        }
        else
        {
            if(getWorld()->getYoshi()->getStars()>=1)
                getWorld()->getYoshi()->takeStars(1);
        }
        setIsActiveYoshi(false);
        getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
    }
    
    
   
}

bool DroppingSquare::isDrop()
{
    return true;
}





Vortex::Vortex(int imageID, int x, int y, StudentWorld* world , int travelDir,int dir, int depth, double size): Character(imageID, x, y, world)
{
    this->travelDir = travelDir;
    setState(WALKING_OR_ACTIVE);
    
}

bool Vortex::getIsVortex()
{
    return true;
}




void Vortex::doSomething()
{
    if(getState() == WAITING_OR_INACTIVE)
    {
        setToBeDestroyed(true);
        return;
    }
    moveAtAngle(travelDir, 2);
    
    
    if(getX() < 0 || getX() >= VIEW_WIDTH ||
       getY()< 0 || getY() >= VIEW_HEIGHT)
    {
        setState(WAITING_OR_INACTIVE);
        setToBeDestroyed(true);
    }
    //see if object overlaps
    
    int i = 0;
    while(getWorld()->getActorAt(i)!= nullptr && i<getWorld()->getNumActors())
    {
       // std::cerr <<"NUM ACTORS:" <<getWorld()->getNumActors() << std::endl;
        if(!getWorld()->getActorAt(i)->getIsVortex())
       {
        //std::cerr <<"i:" <<i << std::endl;
            if( overlaps(getWorld()->getActorAt(i))&&
               getWorld()->getActorAt(i)->getIsImpactable())
            {
               // std::cerr <<"HIHIHIHI"<< std::endl;
                //if(getWorld()->getActorAt(i)->isBaddie())
                //    std::cerr <<"HIHIHIHI"<< std::endl;
                getWorld()->getActorAt(i)->setHasBeenImpacted(true);
               
                setState(WAITING_OR_INACTIVE);
                setToBeDestroyed(true);
                getWorld()->playSound(SOUND_HIT_BY_VORTEX);
                break;
            }
        }
        i++;
    
    //
    }
    //
    
    
    
    
}
