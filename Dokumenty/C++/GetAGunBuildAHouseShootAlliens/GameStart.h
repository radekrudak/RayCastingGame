       
        Clear(olc::BLACK);
        vTileMap.reserve(MapSize);

        // Tilemapp = new Tile[1024]();
        //Enemy test(vTileMap,vTiles);
        lNight = CreateLayer();
        lPlayer = CreateLayer();
        lGround = CreateLayer();
        //sprite loading
        sMT = new olc::Sprite("./assets/tiles/TextureMissing.png");
        for(auto &i:vTiles)
        {
            i = new Tile(0xBEEF,sMT);


        }
        sPGELogo =    new olc::Sprite("./assets/PGELogo.png");
        sGrass =      new olc::Sprite("./assets/tiles/Grass.png");
        sTest =       new olc::Sprite ("./assets/tiles/TestTile.png");
        sMC =         new olc::Sprite ("./assets/characters/mc.png");
        sWood =       new olc::Sprite ("./assets/tiles/WoodAlpha.png");
        sWoodWall =   new olc::Sprite ("./assets/tiles/WoodWall.png");
        sWoodFloor =  new olc::Sprite ("./assets/tiles/WoodFloor.std::thread thread(this, &FindPath,olc::vf2d(123,128), olc::vf2d(125,124),vNodeMap,Path) ;png");
        sEnemy =      new olc::Sprite ("./assets/characters/Enemy.png");
        sNight =      new olc::Sprite ("./assets/tiles/black.png");
        sMoonAndSun = new olc::Sprite("./assets/tiles/MoonandSun.png");

        dPGELogo =     new olc::Decal(sPGELogo);
        dWood =       new olc::Decal (sWood);
        dMoonAndSun = new olc::Decal(sMoonAndSun);
        dNight =      new olc::Decal (sNight);
        dMC =         new olc::Decal(sMC);

        vItems.push_back(new Item(sWood,dWood));
        vItems.push_back(new Item(sWood,dWood));

        vTiles.push_back( new Tile(0,sGrass,false,TZpos::floor)); // grass

        vTiles.push_back(new Tile(1, new olc::Sprite ("./assets/tiles/WoodAlpha.png"),true)); // Wood
        vTiles[1]->vItemsGathered.push_back(vItems[1]);
        std::cout<<vTiles[1]->vItemsGathered.back()<<"\n";
        std::cout<<vTiles[1]->vItemsGathered.front()<<"\n";
        vTiles[1]->vItemsGatheredQuantity.push_back(5);


        vTiles.push_back(new Tile(2,sWoodWall,true)); // Wood wall
        vTiles[2]->vItemsRequiredQuantity.push_back(10);
        vTiles[2]->vItemsRequired.push_back(vItems[1]);
        vBuildableTiles.push_back(vTiles[2]);


        vTiles.push_back(new Tile(3,sWoodFloor,false,TZpos::floor)); // WoodFloor
//        vTiles[3]->vItemsRequiredQuantity.push_back(10);
//        vTiles[3]->vItemsRequired.push_back(vItems[1]);
//        vBuildableTiles.push_back(vTiles[3]);
        vTiles.push_back(new Tile(4,sTest,false,TZpos::dirt)); // cley


        //generating map
        using namespace std::chrono;


        auto mapstart = high_resolution_clock::now();



        GenerateMap(vTileMap,vTiles);

        auto mapstop = high_resolution_clock::now();

        vNodeMap.reserve(MapSize);
        vNodeMap.clear();
        // Seting up nodemap for a*
        for(int x=0;x<MapSize/2;++x)
        {
            std::vector<sNode*> v1;

            for(int y=0;y<MapSize/2;++y)
            {
                std::cout<<"Allocating node "<< x<<" "<<y<<std::endl;
                v1.push_back(new sNode);
                v1[y]->x =x;
                v1[y]->y =y;
                v1[y]->isColisive = vTileMap[x][y].back()->isColisive() ;
            }
         vNodeMap.push_back(v1);

        }
        // it DOSE NOT cover whole map but sinceo only border tiles are sacrivased for less complicated code.
         for(int x=1;x<MapSize/2-1;++x)
        {

            for(int y=1;y<MapSize/2-1;++y)
            {


                    // vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x-1][y-1]);vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x][y-1]);vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x+1][y-1]);
                    // vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x-1][y]);                                             vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x+1][y]);
                    // vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x-1][y+1]);vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x][y+1]);vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x+1][y+1]);
                                                                           vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x][y-1]);
                   vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x-1][y]);                                             vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x+1][y]);
                                                                           vNodeMap[x][y]->vNeighbours.push_back(vNodeMap[x][y+1]);
            }
        }
        auto NodeMapStop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(mapstop - mapstart);
        auto duration2 = duration_cast<milliseconds>(mapstop - mapstart);
        std::cout << "Time taken by MapGen: "
                  << duration.count() << " seconds"
                  << duration2.count() << " miliseconds" << std::endl;
        auto duration3 = duration_cast<seconds>(NodeMapStop - mapstop);
        auto duration4 = duration_cast<milliseconds>(NodeMapStop - mapstop);
        std::cout << "Time taken by NodeGen: "
                  << duration3.count() << " seconds"
                  << duration4.count() << " miliseconds" << std::endl;
        
        
        return true;