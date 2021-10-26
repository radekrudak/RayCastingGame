// I was using jJavid9 A Star algorythm inplementation as reference.
#pragma once
#include "Game.h"
inline float Distance(float x1, float y1,float x2,float y2);
struct sNode
{

bool bVisited = false;
// distance to end
float fGlobalGoal = INFINITY ;
// Distance to start
float fLocalGoal=INFINITY;
bool isColisive =false ;
int x;
int y;

std::vector<sNode*> vNeighbours;
sNode *parent = nullptr;
void SetAllDefault()
{
    bVisited = false;
    fGlobalGoal = INFINITY ;
    fLocalGoal=INFINITY;

    parent = nullptr;
}

};

 inline void FindPath(olc::vf2d Start, olc::vf2d End, 
        std::vector<std::vector<sNode*>> mapa,std::vector<olc::vf2d> &vPath,
            std::vector<std::vector< std::vector<Tile *> > > &vTileMap,
                int &FE)
{
    // with every iteration of while loop this value is incremented if this is above 100 while loop breaks and path array isn't updated, "
    // id why this work idk how this work i don't even know if this works all of the time. I added it for debug purposes but i pevented while loop to turning into invinite loop
    // after i changed
//    if (Neigbour->bVisited == false  && !Neigbour->isColisive)
//            {
//                NodesToCheck.push_back(Neigbour);
//            }
/// in to
//    if (Neigbour->bVisited == false  && !Neigbour->isColisive)
//            {
//                NodesToCheck.push_back(Neigbour);
//            }
// in line to prevent algorythm to finding paths trough walls... somone send help pls.
    int sendhelp =0;
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    vPath.clear();
    int Width = mapa.size();
    int Height = 0;
    for (auto &i: mapa)
    {
        if(i.size()<Height)
        {
            Height=i.size();

        }
    }

    //reset
    for (auto &i: mapa)
    {
        for(auto &j:i)
        {
            j->SetAllDefault();

        }
    }


    sNode* StartNode =mapa[(int)Start.x][(int)Start.y];
    StartNode->fLocalGoal =0;
    StartNode->fGlobalGoal = Distance(Start.x,Start.y,End.x,End.y);
    sNode *EndNode = mapa[(int)End.x][(int)End.y];
    sNode *CurrentNode = StartNode;
    std::vector<sNode*> NodesToCheck;
    NodesToCheck.push_back(StartNode);

    while( EndNode->parent == nullptr || !NodesToCheck.empty()) //mapa[(int)End.x][(int)End.y]->parent == nullptr
    {

        CurrentNode = NodesToCheck.front();
        std::cout<<"A star here ! x: "<<CurrentNode->x<< " y: "<< CurrentNode->y<<" Iteration"<< sendhelp<<"\n";
        int i =0;
        for(auto &Neigbour: CurrentNode->vNeighbours)
        {   
            std::cout<< CurrentNode->vNeighbours.size() <<" "<<Neigbour<<"\n";
            
            if(vTileMap[Neigbour->x][Neigbour->y].back()->isColisive())
            {
                Neigbour->bVisited = true;
            }
            if (Neigbour->bVisited == false  && !vTileMap[Neigbour->x][Neigbour->y].back()->isColisive()) //&& !vTileMap[Neigbour->x][Neigbour->y].back()->isColisive() && !Neigbour->isColisive
            {
                NodesToCheck.push_back(Neigbour);
            }
            if(Neigbour->fLocalGoal > CurrentNode->fLocalGoal+1 )
            {
                Neigbour->fLocalGoal =   CurrentNode->fLocalGoal+1;
                Neigbour->parent = CurrentNode;
                Neigbour->fGlobalGoal = Neigbour->fLocalGoal+ Distance(Neigbour->x,Neigbour->y,End.x,End.y);

            }
            if(Neigbour == EndNode || NodesToCheck.empty())
            {
                goto EndOfSearch; //  I know i know I'm gonna be baked in deepest of hells and programing satan himself gonna torture me by showing new top end CPU's being run without coller
                                 // and dying cuz of that  BUT HEAR ME OUT ! this works and is really simple leave from nested loop (only acceptable usage of go to)  other wise i had to
                                 // create seperate bool to use outsied of thus "auto for" loop  neigbours isn't declared and at the end of the day this is more clear
            }
            i++;
            if(i>CurrentNode->vNeighbours.size())
                break;
        }
          std::cout<<"a star after neigbout checking! \n";

        CurrentNode->bVisited = true;
        NodesToCheck.erase(NodesToCheck.begin());
        sort(NodesToCheck.begin(), NodesToCheck.end(), [](const sNode* lhs, const sNode* rhs) {
        return lhs->fGlobalGoal < rhs->fGlobalGoal;
        });


        // int ii =0;
        // for(auto i : NodesToCheck)
        // { //
        //     if(i->isColisive == true)
        //     {
        //         NodesToCheck.erase(NodesToCheck.begin()+ii);
        //         ++ii;
        //     }
        // }

        sendhelp++;

        if( sendhelp >5000){
            printf("Break \n");
            ++FE;
            break;
        }
    }
EndOfSearch:
    std::cout<<"End Of while \n";
    sNode *Path = nullptr;
    //if(EndNode->parent !=nullptr)
        Path =EndNode;
    std::cout<<" Path : "<< Path<<"\n";
    while (Path != StartNode && Path != nullptr )
    {
        vPath.push_back(olc::vf2d(Path->x, Path->y));
        Path = Path->parent;

    }


}
