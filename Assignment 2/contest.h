#pragma once

#include <fstream>
#include <sstream>
#include <string>

    enum Status { abnorm,
                  norm };

struct Contest
{
    std::string contest;
    std::string angler;
    bool bigger;
    friend std::istream &operator>>(std::istream &is, Contest &h);
};

class ContestEnor
{
private:
    std::ifstream _f;
    Contest _cur;
    Contest _dx;
    Status _sx;
    bool _end;

public:
    enum FileError
    {
        MissingInputFile
    };
    ContestEnor(const std::string &str) throw(FileError);
    void first()
    {
        read();
        next();
    }
    void next();
    Contest current() const { return _cur; }
    bool end() const { return _end; }

    void read();
};
