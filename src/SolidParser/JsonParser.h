//
//
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "../Solid/Solid.h"
#include <string>
#include <fstream>
#include <streambuf>

#ifndef VCAM_JSONPARSER_H
#define VCAM_JSONPARSER_H

using namespace std;
using namespace rapidjson;

class JsonParser
{
public:
    static vector<Solid> readSolids(string path);
};


#endif //VCAM_JSONPARSER_H
