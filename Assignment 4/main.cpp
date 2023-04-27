/*

(1) Give the angler with the corresponding contest ID who has caught the biggest catfish
(it is possible that no one has caught catfish).

*/

/*

(2) List those contests where catfishes bigger than 30 cm were caught.

*/

#include <iostream>
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/linsearch.hpp"
#include "library/counting.hpp"
#include "library/maxsearch.hpp"

using namespace std;
 
struct Species
{
    string fish;
    int size;
    friend istream &operator>>(istream &is, Species &s)
    {
        is >> s.fish >> s.size;
        return is;
    }
};

class Result : public MaxSearch<Species, int, Greater<int>>
{
protected:
    int func(const Species &e) const override { return e.size; }
    bool cond(const Species &e) const override { return e.fish == "catfish"; }
};
struct Contest
{
    string name;
    string hunter;
    int counter;
    friend istream &operator>>(istream &is, Contest &c)
    {
        string line;
        getline(is, line, '\n');
        stringstream ss(line);
        ss >> c.name >> c.hunter;
        StringStreamEnumerator<Species> ssenor(ss);

        Result pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        c.counter = pr.opt();
        return is;
    }
};

class MyMaxSearch : public MaxSearch<Contest, int, Greater<int>>
{
protected:
    int func(const Contest &e) const override { return e.counter; }
};

int main(int argc, char **argv)
{
    ///First task

    try
    {
        string fileName;
        if (argc > 1)
            fileName = argv[1];
        else
            fileName = "inp.txt";

        SeqInFileEnumerator<Contest> enor(fileName);
        MyMaxSearch pr;
        pr.addEnumerator(&enor);
        pr.run();
        if (pr.found())
        {
            cout << "Angler and contest ID: " << pr.optElem().name << "  " << pr.optElem().hunter << endl;
            cout << "Size of the catfish: " << pr.opt() << endl;
        }
        else
        {
            cout << "Nothing is found" << endl;
        }
    }
    catch (SeqInFileEnumerator<Contest>::Exceptions err)
    {
        cout << "File not found\n";
        return 1;
    }

    return 0;
}