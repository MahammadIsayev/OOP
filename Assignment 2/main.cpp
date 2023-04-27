#include <iostream>
#include "contest.h" //this is not necessary when we use the next include (only for the first task)
#include "angler.h"

using namespace std;

//First task
//Activity: Give the angler with the corresponding contest ID who has caught the biggest catfish
bool first_search(const string &name, Angler *a)
{
    AnglerEnor t(name);
    bool l = false;
    int max = 0;
    for (t.first(); !t.end(); t.next())
    {
        if (t.current().maxx > max)
        {
            max = t.current().maxx;
            a->name = t.current().name;
            a->id = t.current().id;
            l = true;
        }
    }
    return l;
}

//Second task
//Activity:  List those contests where catfishes bigger than 30 cm were caught.
bool second_search(const string &name)
{
    ContestEnor t(name);
    bool l;
    for (t.first(); !t.end(); t.next())
    {
        if (l=t.current().bigger)
        {
            cout << t.current().contest << endl;
        }
    }
    return l;
}

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{

    string filename;
    cout << "Enter the name of the input file, please: ";
    cin >> filename;

    //First task
    cout << "First  task\n";
    try
    {
        Angler a;
        if (first_search(filename, &a))
        {
            cout << "The biggest catfish caught by " << a.name << " on " << a.id << endl;
        }
        else
        {
            cout << "There is no angler matching our search criteria.\n";
        }
    }
    catch (ContestEnor::FileError err)
    {
        cerr << "Can't find input file " << filename << "!" << endl;
    }

    //Second task
    cout << "Second task\n";

    try
    {
        second_search(filename);
        //        if (second_search(filename))
        //            cout << " is a";
        //        else
        //            cout << "There is no";
    }
    catch (ContestEnor::FileError err)
    {
        cerr << "Can't find the input file:" << filename << endl;
    }
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

//linear search first part

TEST_CASE("first task empty file", "t0.txt")
{
    Angler a;
    CHECK_FALSE(first_search("t0.txt", &a));
}

TEST_CASE("first task 1 angler, true", "t2.txt")
{
    Angler a;
    CHECK(first_search("t2.txt", &a));
    CHECK(a.name == "Peter");
}

TEST_CASE("first task 1 angler, false", "t13.txt")
{
    Angler a;
    CHECK_FALSE(first_search("t13.txt", &a));
}

TEST_CASE("first task more anglers, first one meets the requirements", "tt3.txt")
{
    Angler a;
    CHECK(first_search("tt3.txt", &a));
    CHECK((a.name == "Peter" && a.id == "Kiliti0512") == TRUE);
}

TEST_CASE("first task more anglers, third one meets the requirements", "tt5.txt")
{
    Angler a;
    CHECK(first_search("tt5.txt", &a));
    CHECK(a.name == "Peter");
}

TEST_CASE("first task more anglers, last one meets the requirements", "tt6.txt")
{
    Angler a;
    CHECK(first_search("tt6.txt", &a));
    CHECK(a.name == "Peter");
}

TEST_CASE("first task more anglers, no one meets the requirements", "t6.txt")
{
    Angler a;
    CHECK_FALSE(first_search("t6.txt", &a));
}

// linear search second part

TEST_CASE("empty file", "t0.txt")
{
    CHECK_FALSE(second_search("t0.txt"));
}

TEST_CASE("1 angler", "t2.txt")
{
    Contest e;
    CHECK(second_search("t2.txt"));
    CHECK(e.bigger);
}

TEST_CASE("more angler more contests", "t14.txt")
{
    Contest e;
    CHECK(second_search("t14.txt"));
    CHECK(e.bigger);
}

TEST_CASE("none of them", "t4.txt")
{
    Contest e;
    CHECK_FALSE(second_search("t4.txt"));
}

TEST_CASE("last one meets", "t5.txt")
{
    Contest e;
    CHECK(second_search("t5.txt"));
    CHECK(e.bigger);
}

TEST_CASE("one ", "t4.txt")
{
    Contest e;
    CHECK_FALSE(second_search("t4.txt"));
}

TEST_CASE("no  ", "t6.txt")
{
    Contest e;
    CHECK_FALSE(second_search("t6.txt"));
}

TEST_CASE("more  ", "t14.txt")
{
    Contest e;
    CHECK(second_search("t14.txt"));
    CHECK(e.bigger);
}

#endif
