//
//
#include "JsonParser.h"

vector<Figure> JsonParser::readWorld(char *path)
{
    vector<Figure> ret;
    ifstream s(path);
    string rawJson;
    s.seekg(0, std::ios::end);
    rawJson.reserve(s.tellg());
    s.seekg(0, std::ios::beg);

    rawJson.assign((std::istreambuf_iterator<char>(s)),
                   std::istreambuf_iterator<char>());
    Document d;
    d.Parse(rawJson.c_str());
for(  auto & figure : d["Figures"].GetArray() )
    //for(auto & figure :d.GetArray())
    {
        Figure fig;
        for(const  auto  &node:figure["Nodes"].GetArray())
        {
          //  t_3dvec new_node(node["x"].GetDouble(),node["y"].GetDouble(),node["z"].GetDouble(),node["route_id"].GetInt());
         //   fig.addNode(&new_node);
         fig.getNodes().emplace_back(make_shared<t_3dvec>(node["x"].GetDouble(),node["y"].GetDouble(),node["z"].GetDouble(),node["route_id"].GetInt()));
        }
        for(const auto& wall:figure["walls"].GetArray())
        {
            t_Wall new_wall;
            for(auto it=wall["wall"].GetArray().begin();it<wall["wall"].GetArray().end()-1;it++)
            {
               // t_Edge * new_edge=new t_Edge(fig.getRoutedNode(it->GetInt()),fig.getRoutedNode((it+1)->GetInt()));
                new_wall.edges.emplace_back(make_shared<t_Edge>(fig.getRoutedNode(it->GetInt()),fig.getRoutedNode((it+1)->GetInt())));
				new_wall.nodes.emplace_back(fig.getRoutedNode(it->GetInt()));
				new_wall.signatures.push_back(it->GetInt());
            }
			new_wall.signatures.push_back((wall["wall"].GetArray().end()-1)->GetInt());
            fig.getWalls().push_back(new_wall);
        }
        fig.gatherEdgesFromWalls();
        ret.push_back(fig);
    };
    return ret;
}

void JsonParser::parseWorld(char * path,t_World &world)
{
    vector<Figure> ret;
    ifstream s(path);
    string rawJson;
    s.seekg(0, std::ios::end);
    rawJson.reserve(s.tellg());
    s.seekg(0, std::ios::beg);

    rawJson.assign((std::istreambuf_iterator<char>(s)),
                   std::istreambuf_iterator<char>());
    Document d;
    d.Parse(rawJson.c_str());
	for(const auto & node:d["Nodes"].GetArray())
	{
         world.nodes.emplace_back(make_shared<t_3dvec>(node["x"].GetDouble(),node["y"].GetDouble(),node["z"].GetDouble(),node["route_id"].GetInt()));
	}
        for(const auto& wall:d["walls"].GetArray())
        {
            t_Wall new_wall;
            for(auto it=wall["wall"].GetArray().begin();it<wall["wall"].GetArray().end()-1;it++)
            {
               // t_Edge * new_edge=new t_Edge(fig.getRoutedNode(it->GetInt()),fig.getRoutedNode((it+1)->GetInt()));
                new_wall.edges.emplace_back(make_shared<t_Edge>(world.nodes[it->GetInt()],world.nodes[(it+1)->GetInt()]));
				new_wall.signatures.push_back(it->GetInt());
            }
			new_wall.signatures.push_back((wall["wall"].GetArray().end()-1)->GetInt());
			world.walls.push_back(new_wall);
        }
    };
