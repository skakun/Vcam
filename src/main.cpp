#include<stdio.h>
#include <iostream>
#include "SolidParser/JsonParser.h"
#include "WorldTransformer/WorldTransformer.h"
#include <math.h>

using namespace std;
int main (int argc,char** argv)
{
 /*   Figure  S;
    //front
    S.addEdge(t_3dvec(0,0,1),t_3dvec(1,0,1));
    S.addEdge(t_3dvec(1,0,1),t_3dvec(1,0,0));
    S.addEdge(t_3dvec(1,0,0),t_3dvec(0,0,0));
    //right
    S.addEdge(t_3dvec(1,0,1),t_3dvec(1,1,1));
    S.addEdge(t_3dvec(1,1,1),t_3dvec(1,1,0));
    S.addEdge(t_3dvec(1,1,0),t_3dvec(1,0,0));
    //left
    S.addEdge(t_3dvec(0,0,1),t_3dvec(0,1,1));
    S.addEdge(t_3dvec(0,1,1),t_3dvec(0,1,0));
    S.addEdge(t_3dvec(0,1,0),t_3dvec(0,0,0));
    //back
    S.addEdge(t_3dvec(0,1,1),t_3dvec(1,1,1));
    S.addEdge(t_3dvec(1,1,1),t_3dvec(1,1,0));
    S.addEdge(t_3dvec(1,1,0),t_3dvec(1,0,1));*/
        vector<Figure> world=JsonParser::readWorld("../sworld.json");
    cout<<"pozdro"<<endl;
}
