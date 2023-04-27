#pragma once

#include "contest.h"
#include <string>

//Datatype of anglers
struct Angler
{
    std::string id;
    std::string name;
    int maxx;
};

//Datatype of the enumerator of anglers for the second part
class AnglerEnor
{
private:
    std::ifstream _f;
    Angler _cur;
    bool _end;

public:
    enum FileError
    {
        MissingInputFile
    };
    AnglerEnor(const std::string &str) throw(FileError);
    void first(){ next(); }
    void next();
    Angler current() const { return _cur; }
    bool end() const { return _end; }
};
