#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    peach = nullptr;
    yoshi = nullptr;
    bankSum = 0;
    numActors = 0;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
    delete peach;
    delete yoshi;
    
}

void StudentWorld::cleanUp()
{
    
    list<Actor*>::iterator p = actors.begin();
    
    while(!actors.empty())
    {
        delete *p;
        p = actors.erase(p);
        
    }
   
}



int StudentWorld::init()
{
    startCountdownTimer(99);  // this placeholder causes timeout after 5 seconds
    /*
    Board bd;
    string board_file = assetPath() + "board0" + to_string(getBoardNumber()) + ".txt";
    
    Board::LoadResult result = bd.loadBoard(board_file);
     */
    int xS = 0;
    int yS = 0;
    
    
    string board_file = assetPath() + "board0" + to_string(getBoardNumber()) + ".txt";
    
    
    
    Board::LoadResult result = bd.loadBoard(board_file);
    
        if (result == Board::load_fail_file_not_found)
        cerr << "Could not find board01.txt data file\n"; else if (result == Board::load_fail_bad_format)
        cerr << "Your board was improperly formatted\n"; else if (result == Board::load_success)
       cerr << "Successfully loaded board\n";
            
            
           
    
    for(xS=0; xS<16; xS++)
    {
        for(yS=0;yS<16 ; yS++)
        {
            if(bd.getContentsOf(xS,yS) == Board::player) {
                break;
            }
        }
        if(bd.getContentsOf(xS,yS) == Board::player)
            break;
    }
   
    peach = new Avatar(IID_PEACH, xS*16, yS*16, this , 1);
    
    yoshi = new Avatar(IID_YOSHI, xS*16, yS*16, this , 2);
    
    
   
    actors.push_back(new CoinSquare( IID_BLUE_COIN_SQUARE, xS*16, yS*16, this, 0, 1));
    
    numActors++;
    
    
    for(xS = 0; xS<16; xS++)
    {
        for(yS = 0;yS<16 ; yS++)
        {
            if(bd.getContentsOf(xS,yS) == Board::player)
                continue;
            
            if(bd.getContentsOf(xS,yS) == Board::bowser)
            {
                actors.push_back(new Baddie(IID_BOWSER, xS*16, yS*16, this, 0, BOWSER));
                actors.push_back(new CoinSquare( IID_BLUE_COIN_SQUARE, xS*16, yS*16, this, 0, 1));
                numActors+=2;
                continue;
            }
            else if(bd.getContentsOf(xS,yS) == Board::boo)
            {
                actors.push_back(new Baddie(IID_BOO, xS*16, yS*16, this, 0,  BOO));
                actors.push_back(new CoinSquare( IID_BLUE_COIN_SQUARE, xS*16, yS*16, this, 0, 1));
                numActors+=2;
                continue;
            }
            
            
            else if(bd.getContentsOf(xS,yS) == Board::blue_coin_square)
                actors.push_back(new CoinSquare( IID_BLUE_COIN_SQUARE, xS*16, yS*16, this, 0, 1));
                 
           else if(bd.getContentsOf(xS,yS) == Board::red_coin_square)
                actors.push_back(new CoinSquare( IID_RED_COIN_SQUARE, xS*16, yS*16, this, 0, 2));
            
           else if(bd.getContentsOf(xS,yS) == Board::star_square)
                actors.push_back(new StarSquare( IID_STAR_SQUARE, xS*16, yS*16, this, 0));
            
            //DIRECTIONAL SQUARE
                //UP
           else if(bd.getContentsOf(xS,yS) == Board::up_dir_square)
                actors.push_back(new DirectionalSquare( IID_DIR_SQUARE, xS*16, yS*16, this,90));
                //DOWN
           else if(bd.getContentsOf(xS,yS) == Board::down_dir_square)
                actors.push_back(new DirectionalSquare( IID_DIR_SQUARE, xS*16, yS*16, this,270));
                //LEFT
           else if(bd.getContentsOf(xS,yS) == Board::left_dir_square)
                actors.push_back(new DirectionalSquare( IID_DIR_SQUARE, xS*16, yS*16, this,180));
            //RIGHT
       else if(bd.getContentsOf(xS,yS) == Board::right_dir_square)
            actors.push_back(new DirectionalSquare( IID_DIR_SQUARE, xS*16, yS*16, this,0));
            
          else  if(bd.getContentsOf(xS,yS) == Board::bank_square)
                actors.push_back(new BankSquare( IID_BANK_SQUARE, xS*16, yS*16, this,0));
            
           else if(bd.getContentsOf(xS,yS) == Board::event_square)
                actors.push_back(new EventSquare( IID_EVENT_SQUARE, xS*16, yS*16, this,0));
            
            if(bd.getContentsOf(xS,yS) != Board::empty)
                numActors++;
            
            
        }
        
    }
    
    
    
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.
    
    if (timeRemaining() <= 0)
    {
        playSound(SOUND_GAME_FINISHED);
        
        Avatar* winner = getWinner();
        
        setFinalScore(winner->getStars(), winner->getCoins());
        
        if(winner == peach)
            return GWSTATUS_PEACH_WON;
        else
            return GWSTATUS_YOSHI_WON;
        
    }
    
    
    
    std::string text = "P1 Roll: " + to_string(peach->getTicks()/8) + " Stars: " + to_string(peach->getStars())  +  " $$: " + to_string(peach->getCoins()) + " ";
    
    if(peach->getHasVortex())
      text +=  "VOR | Time: ";
    else
        text +=   "| Time: ";
    
    text+= to_string(timeRemaining()) + " | Bank: "+ to_string(bankSum) +" | P2 Roll: " + to_string(yoshi->getTicks()/8) + " Stars: "+ to_string(yoshi->getStars()) +" $$: " + to_string(yoshi->getCoins()) + " ";
    if(yoshi->getHasVortex())
        text+= "VOR" ;
    
        
    
    setGameStatText(text);
    
    //setGameStatText("P1 Roll: " + "3 Stars: 2 $$: 15 VOR | Time: 75 | Bank: 9 | P2 Roll: 0 Stars: 1 $$: 22 VOR");
    
   
    
    
    peach->doSomething();
    
    if((peach)->getToIntroVortex())
    {
        enterVortex(peach);
        peach->setToIntroVortex(false);
    }
    
    
    
    yoshi->doSomething();
    
    if((yoshi)->getToIntroVortex())
    {
        enterVortex(yoshi);
        yoshi->setToIntroVortex(false);
    }
    
    for(list<Actor*>::iterator p = actors.begin(); p != actors.end(); p++)
    {
        
        
        (*p)->doSomething();
        if((*p)->isToBeDestroyed())
        {
            delete (*p);
            p = actors.erase(p);
            numActors--;
        }
        if(p==actors.end())
            break;
        
        //if(remove) //make a function to check if things need to be removed
           // ...
        if((*p)->isToDropSquare())
        {
            removeSquare((*p)->getX(),(*p)->getY());
             (*p)->setIsToDropSquare(false);
            //std::cerr<<"HIHIHIHIHI"<<std::endl;
            
            actors.push_back(new DroppingSquare( IID_DROPPING_SQUARE, (*p)->getX(), (*p)->getY(), this,  0));
            
            
          
            
        }
        
       
        
        
        
    }
  // std::cerr<< numActors << std::endl;
    return GWSTATUS_CONTINUE_GAME;
}

Board StudentWorld::getBoard()
{
    return bd;
}

int StudentWorld::getNumActors() const
{
    return numActors;
}
void StudentWorld::setNumActors(int d)
{
    numActors = d;
}

Actor* StudentWorld::getActorAt(int i)
{
    list<Actor*>::iterator p = actors.begin();
    
    if(i>=getNumActors())
        return nullptr;
    
    while(i!=0 && p!=actors.end())
    {
     p++;
        i--;
    }
    
    return *p;
    
}

Avatar* StudentWorld::getWinner()
{
    if(peach->getStars()>yoshi->getStars())
        return peach;
    if(peach->getStars()<yoshi->getStars())
        return yoshi;
    if(peach->getCoins()>yoshi->getCoins())
        return peach;
    if(peach->getCoins()<yoshi->getCoins())
        return yoshi;
    int rand = randInt(1,2);
    if(rand == 1)
        return peach;
    return yoshi;
    
}


int StudentWorld::getBankSum() const
{
    return bankSum;
}
void StudentWorld::giveBank(int amt)
{
    bankSum+=amt;
}

void StudentWorld::emptyBank()
{
    bankSum = 0;
}


Avatar* StudentWorld::getPeach()
{
    return peach;
}

Avatar* StudentWorld::getYoshi()
{
    return yoshi;
}

void StudentWorld::removeSquare(int x, int y)
{
 //what if current square is not square
    //possibly boo or bowser
    
    
    
    for(list<Actor*>::iterator p = actors.begin(); (p) != actors.end() ; p++)
    {
        list<Actor*>::iterator end = actors.end();
        end--;
        if(p == end)
            return;
        
        if((*p)->isSquare() && (*p)->getX() == x && (*p)->getY() == y)
        {
            delete (*p);
            p = actors.erase(p);
            numActors--;
        }
    }
}

void StudentWorld::enterVortex(Avatar* player)
{
    if(player->getWalkingDir() == GraphObject::right)
        actors.push_back(new Vortex( IID_VORTEX, player->getX() + 16, player->getY(), this , GraphObject::right,0, 0, 1));
    else if(player->getWalkingDir() == GraphObject::left)
        actors.push_back(new Vortex( IID_VORTEX, player->getX() - 16, player->getY(), this , GraphObject::left,0, 0, 1));
    else if(player->getWalkingDir() == GraphObject::down)
        actors.push_back(new Vortex( IID_VORTEX, player->getX() , player->getY() -16, this , GraphObject::down,0, 0, 1));
   else if(player->getWalkingDir() == GraphObject::up)
        actors.push_back(new Vortex( IID_VORTEX, player->getX(), player->getY() + 16, this , GraphObject::up,0, 0, 1));
    
    numActors++;
}

