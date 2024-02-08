#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <list>
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

const int WAITING_OR_INACTIVE = 0;
const int PAUSED = 0;
const int WALKING_OR_ACTIVE = 1;

const int PEACH = 1;
const int YOSHI = 2;

const int BLUE = 1;
const int RED = 2;

const int BOWSER = 1;
const int BOO = 2;




// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
    public:
    Actor(int imageID, int x, int y, StudentWorld* world ,int dir = right, int depth = 0, double size = 1.0 );
    virtual void doSomething() = 0;
    
    void setState(int newState);
    int getState() const;
    
    virtual bool isSquare();
    virtual bool isDrop();
    
    bool isToBeDestroyed();
    void setToBeDestroyed(bool d);
    
    bool isToDropSquare();
    void setIsToDropSquare(bool d);
    
    bool getHasBeenImpacted();
    void setHasBeenImpacted(bool d);
    
    virtual bool getIsImpactable();
    
   virtual bool isBaddie();
   
    
    bool overlaps(Actor* other);
    
    virtual bool getIsVortex();
    
    bool getIsActivePeach();
    bool getIsActiveYoshi();
    void setIsActivePeach(bool isActive);
    void setIsActiveYoshi(bool isActive);
    
    void setPlayerActives();
    
    StudentWorld* getWorld() const;
    
    virtual ~Actor();
    
    
   
    
    private:
    int state;
    StudentWorld* world;
    bool toBeDestroyed;
    
    bool toDropSquare;
    
    bool hasBeenImpacted;
    
    bool isActivePeach;
    bool isActiveYoshi;
    
    
    
    
    
   
    
};

class Character : public Actor
{
public:
    Character(int imageID, int x, int y, StudentWorld* world,int dir = right, int walkingDir = right);
    int getWalkingDir();
    void setWalkingDir(int dir);
    int getOppositeWalkingDir();
    
     
    
    
    bool isValidDirRight();
    bool isValidDirLeft();
    bool isValidDirUp();
    bool isValidDirDown();
    
    bool hasInvalidDir();
    
    bool isAtFork();
    
    int getTicks();
    void setTicks(int t);
    
    bool getJustTeleported();
    void setJustTeleported(bool d);
    
    void changeRandomDir();
    void teleportRandom();
    
    
private:
    int walkingDir;
    int ticks_to_move;
    bool justTeleported;
    
};

class Avatar : public Character
{
public:
    Avatar(int imageID, int x, int y, StudentWorld* world , int playerNum, int walkingDir = right);
    
    int getPlayerNum();
    
    
    virtual void doSomething();
    
    int getRoll();
    int getCoins();
    void giveCoins(int sum);
    void takeCoins(int sum);
    
    int getStars();
    void giveStars(int sum);
    void takeStars(int sum);
    
    bool getHasVortex();
    void setHasVortex(bool v);
    
    bool getToIntroVortex();
   void setToIntroVortex(bool d);
    
    
    void blueLanded();
    void redLanded();
    void starLanded();
    
    
private:
    int playerNum;
    int nCoins;
    int nStars;
    int die_roll;
    // move to character
    bool hasVortex;
    bool toIntroVortex;
    
    
    
    
};

class Baddie: public Character
{
public:
    Baddie(int imageID, int x, int y, StudentWorld* world, int dir, int bowOrBoo);
    virtual void doSomething();
    virtual bool getIsImpactable();
    virtual bool isBaddie();
    
    
private:
    int pauseCounter;
    
    bool hasTaken;
    int bowOrBoo;
    
    
    
};





class Square: public Actor
{
    public:
    Square(int imageID, int x, int y, StudentWorld* world, int dir);
    
    
    
    bool virtual isSquare();
    
    
    
    
    bool hasLandedPeach(Avatar* peach);
    bool hasLandedYoshi(Avatar* yoshi);
    
   
   
    
    
private:
   
    
    
    
    
    
};

class CoinSquare: public Square
{
    public:
    CoinSquare(int imageID, int x, int y, StudentWorld* world, int dir, int color);
    
    virtual void doSomething();
    
   
    
    private:
    
    int color;
    
    
    
};


class StarSquare : public Square
{
    public:
    StarSquare(int imageID, int x, int y, StudentWorld* world, int dir);
    
    virtual void doSomething();
    
    private:
    
    
    
};

class DirectionalSquare: public Square
{
    public:
    DirectionalSquare(int imageID, int x, int y, StudentWorld* world, int dir);
    
    virtual void doSomething();
    
    private:
    
    
    
};

class BankSquare: public Square
{
    public:
    BankSquare(int imageID, int x, int y, StudentWorld* world, int dir);
    
    virtual void doSomething();
    
    private:
    
};

class EventSquare: public Square
{
    public:
    EventSquare(int imageID, int x, int y, StudentWorld* world, int dir);
    
    virtual void doSomething();
    
    private:
    void teleportPlayers();
    
    
};

class DroppingSquare: public Square
{
    public:
    DroppingSquare(int imageID, int x, int y, StudentWorld* world, int dir);
    
    virtual void doSomething();
    virtual bool isDrop();
    
    private:
};

class Vortex: public Character
{
public:
    Vortex(int imageID, int x, int y, StudentWorld* world , int travelDir,int dir = right, int depth = 0, double size = 1.0);
    virtual void doSomething();
    virtual bool getIsVortex();
    
     
    
    
private:
    
    int travelDir;
    
    
};



#endif // ACTOR_H_
