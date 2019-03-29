#include<stdio.h>
#include <iostream>
#include "Solid/Solid.h"
#include "SolidParser/JsonParser.h"
#include "WorldTransformer/WorldTransformer.h"
#include <math.h>

using namespace std;
int main (int argc,char** argv)
{
 /*   Solid  S;
    //front
    S.addEdge(_3dnode(0,0,1),_3dnode(1,0,1));
    S.addEdge(_3dnode(1,0,1),_3dnode(1,0,0));
    S.addEdge(_3dnode(1,0,0),_3dnode(0,0,0));
    //right
    S.addEdge(_3dnode(1,0,1),_3dnode(1,1,1));
    S.addEdge(_3dnode(1,1,1),_3dnode(1,1,0));
    S.addEdge(_3dnode(1,1,0),_3dnode(1,0,0));
    //left
    S.addEdge(_3dnode(0,0,1),_3dnode(0,1,1));
    S.addEdge(_3dnode(0,1,1),_3dnode(0,1,0));
    S.addEdge(_3dnode(0,1,0),_3dnode(0,0,0));
    //back
    S.addEdge(_3dnode(0,1,1),_3dnode(1,1,1));
    S.addEdge(_3dnode(1,1,1),_3dnode(1,1,0));
    S.addEdge(_3dnode(1,1,0),_3dnode(1,0,1));*/
    vector<Solid> world=JsonParser::readSolids("../world.json");
    Camera cam(_3dvec(0,0,0),_3dvec(0,0,0),_3dvec(1,1,1));
    //Camera cam(_3dvec(0,0,0),_3dvec(M_PI_4,M_PI_4,M_PI_4),_3dvec(1,1,1));
    vector<Solid> projected=WorldTransformer::project(world,cam);
    cout<<"pozdro"<<endl;
}
