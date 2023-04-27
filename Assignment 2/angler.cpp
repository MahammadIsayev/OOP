#include "angler.h"

using namespace std;

AnglerEnor::AnglerEnor(const string &str) throw(FileError)
{
    _f.open(str);
    if (_f.fail())
        throw MissingInputFile;
}

void AnglerEnor::next()
{
    string line;
    getline(_f, line, '\n');
    if (!(_end = _f.fail()))
    {
        istringstream is(line);
        is >> _cur.name >> _cur.id;
        string fish;
        int size;
        _cur.maxx = 0;
        for (is >> fish >> size; !is.fail(); is >> fish >> size)
        {
            if (fish == "catfish" && size > _cur.maxx)
            {
                _cur.maxx = size;
            }
        }
    }
}