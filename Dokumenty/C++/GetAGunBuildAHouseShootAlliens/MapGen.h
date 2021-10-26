#pragma once
#include "olcPixelGameEngine.h"
#include "Tile.h"
inline void GenerateMap(std::vector<std::vector< std::vector<Tile*> > >  &mapa, std::vector<Tile*> &Tiles)
{

    for(int x =0; x<1024; x++)
    {
        std::vector<std::vector<Tile*>> v2d;
        v2d.reserve(1024);

        for(int y =0; y<1024; y++)
        {
            std::vector<Tile*> v1d;
            v1d.push_back(Tiles[4] );
            v1d.push_back(Tiles[0] );
            if (rand()%10 < 2)
                v1d.push_back(Tiles[1])  ;

            v2d.push_back(v1d);

        }
        std::cout<<"Row :"<<x<<" Finished ! \n";
        mapa.push_back(v2d);
    }
}


