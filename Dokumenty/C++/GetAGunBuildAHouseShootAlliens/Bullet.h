#pragma once

class Bullet
{
    olc::vf2d Velocity = {0,0};
    float PosX;
    float PosY;
    float fSpeed =100;
public:
    Bullet(float fPX,float fPY,float fPA)
    {
        PosX = fPX;
        PosY = fPY;
        Velocity = {cos(fPA)*fSpeed,sin(fPA)*fSpeed};
        //std::cout<<"\n Hello World \n";

    }
    olc::vf2d Move(float fFrameTime) // fFrame tiem is esaped time
    {
        PosX += Velocity.x *fFrameTime;
        PosY += Velocity.y *fFrameTime;
        olc::vf2d ret= {PosX,PosY};
        //std::cout<<"\n Wieeeew \n"<<std::to_string(ret.x)<<" "<<std::to_string(ret.y)<<std::endl;
        return ret;

    }
    olc::vf2d GetPos()
    {

        olc::vf2d ret= {PosX,PosY};

        return ret;

    }
    float GetX()
    {
        return PosX;

    }
    float GetY()
    {
        return PosY;

    }

};


