//
//
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "../Figure/Figure.h"
#include <string>
#include <fstream>
#include <streambuf>
#include "../Figure/t_World.h"

#ifndef VCAM_JSONPARSER_H
#define VCAM_JSONPARSER_H

using namespace std;
using namespace rapidjson;

class JsonParser
{
public:
	static void parseWorld(char * path,t_World &world);
};


#endif //VCAM_JSONPARSER_H
