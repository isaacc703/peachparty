#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    Board getBoard();
    ~StudentWorld();
    
    int getNumActors() const;
    void setNumActors(int d);
    
    Actor* getActorAt(int i);
    
    Avatar* getWinner();
    
    int getBankSum() const;
    void giveBank(int amt);
    void emptyBank();
    
    void removeSquare(int x , int y);
    void enterVortex(Avatar* player);
    
    Avatar* getPeach();
    Avatar* getYoshi();
    
    
    
    

private:
    std::list<Actor*> actors;
    int numActors;
    Board bd;
    Avatar* peach;
    Avatar* yoshi;
    int bankSum;
    
    
   
    
    
};

#endif // STUDENTWORLD_H_
