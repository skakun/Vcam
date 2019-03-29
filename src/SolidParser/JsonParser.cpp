//
//
#include <iostream>
#include "JsonParser.h"


vector<Solid> JsonParser::readSolids(string path)
{
    vector<Solid> ret;
    ifstream s(path);
    string rawJson;
    s.seekg(0, std::ios::end);
    rawJson.reserve(s.tellg());
    s.seekg(0, std::ios::beg);

    rawJson.assign((std::istreambuf_iterator<char>(s)),
               std::istreambuf_iterator<char>());
    Document d;
    d.Parse(rawJson.c_str());
    for(const auto& jsolid : d["Solids"].GetArray())
    {
        ret.emplace(ret.end());

        for(const auto& jedge: jsolid["Edges"].GetArray())
        {
            const auto &j_n1 = jedge["n1"];
            _3dvec n1(j_n1["x"].GetDouble(), j_n1["y"].GetDouble(), j_n1["z"].GetDouble());
            const auto &j_n2 = jedge["n2"];
            _3dvec n2(j_n2["x"].GetDouble(), j_n2["y"].GetDouble(), j_n2["z"].GetDouble());
            (ret.end()-1)->addEdge(n1,n2);
        }
    //cout<<"pozdro"<<endl;
    }
    return  ret;
}
