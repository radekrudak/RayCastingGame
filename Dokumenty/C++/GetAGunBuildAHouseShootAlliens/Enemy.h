#pragma once
#include "FindPath.h"
#include "olcPixelGameEngine.h"
#include <math.h>
static const int MapSize = 1024;




class Enemy
{   public:
    sNode *sNodeMap = nullptr;
    float x; 
    float y;
    olc::Sprite *Sprite=nullptr;
    olc::Decal *Decal=nullptr;
    std::vector<olc::vf2d> Path;
    
    public:
    
     Enemy(float xx,float yy,olc::Sprite *sp) 
    {
            x=xx;
            y=yy;
            Sprite=sp;
            Decal = new olc::Decal(sp);
    }

    olc::vf2d Move(float fPX,float fPY,float fElapsedTime)
    {   if(!Path.empty())
        {    float distance = sqrt((Path.back().x+0.5f-x)*(Path.back().x+0.5f-x)+(Path.back().y+0.5f-y)*(Path.back().y+0.5f-y));   
            x+= (Path.back().x+0.5f-x)/distance*fElapsedTime;//-x*fElapsedTime*0.1f;
            y+= (Path.back().y+0.5f-y)/distance*fElapsedTime;//-y*fElapsedTime*0.1f;
            if(distance<0.25f) //Path.back().x+0.5f== x && Path.back().y+0.5f == y
                Path.pop_back();
        }
        return olc::vf2d(x,y);
    }
    olc::vf2d GetPosition()
    {
        return olc::vf2d (x,y);

    }
};
