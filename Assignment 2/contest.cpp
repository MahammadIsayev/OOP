#include "contest.h"
#include <iostream>

using namespace std;

//Input:    string str  - the test file's name
//Activity: tries to open the given file. If the opening fails, it throws a "FileError" exception.
ContestEnor::ContestEnor(const std::string &str) throw(FileError)
{
    _f.open(str.c_str());
    if (_f.fail())
        throw MissingInputFile;
}

std::istream &operator>>(std::istream &is, Contest &h)
{
    string line;
    getline(is, line, '\n');
    istringstream ss(line);
    ss >> h.angler >> h.contest;
    string fish;
    int size;
    h.bigger = false;
    for (ss >> fish >> size; !ss.fail(); ss >> fish >> size)
    {
        h.bigger = h.bigger || ((fish == "catfish") && (size > 30));
    }
    return is;
}
void ContestEnor::read()
{
    _sx = (_f >> _dx) ? norm : abnorm;
}
void ContestEnor::next()
{
    if (_sx != norm)
        _end = true;
    else
    {
        _end = false;
        _cur.contest = _dx.contest;
        _cur.bigger = true;
        for (; _sx == norm && _cur.contest == _dx.contest; read())
        {
            _cur.bigger = true;
            _cur.bigger = _cur.bigger && _dx.bigger;
        }
    }
}
