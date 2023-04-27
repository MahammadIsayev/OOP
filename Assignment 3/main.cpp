#include <iostream>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <cstdio>
#include <typeinfo>
#include <vector>
#include "layer.h"
#include "variable.h"

using namespace std;

void create(const string &str, vector<Layer *> &layers, vector<Variable *> &vars)
{
    ifstream f(str);
    if (f.fail())
    {
        cout << "Oops, wrong file name!\n";
        exit(1);
    }
    int n;
    f >> n;
    layers.resize(n);
    for (int i = 0; i < n; ++i)
    {
        char ch;
        double t;
        f >> ch >> t;
        switch (ch)
        {
        case 'Z':
            layers[i] = new Ozone(t);
            break;
        case 'X':
            layers[i] = new Oxygen(t);
            break;
        case 'C':
            layers[i] = new CO2(t);
            break;
        }
    }

    string variables;
    f >> variables;
    vars.resize(variables.size());
    for (int j = 0; j < (int)variables.size(); ++j)
    {
        char v = variables.at(j);
        switch (v)
        {
        case 'T':
            vars[j] = Thunder::instance();
            break;
        case 'O':
            vars[j] = Other::instance();
            break;
        case 'S':
            vars[j] = Sunshine::instance();
            break;
        }
    }
    f.close();
}

int get_Index(const Layer *l, const vector<Layer *> &layers_above)
{
    int i = 0;
    int lSize = (int)layers_above.size();

    while (i < lSize && layers_above[i]->get_ID() != l->get_ID())
        i++;

    if (i < lSize)
        return i;

    return -1;
}

bool search(const Layer *l, const vector<Layer *> &layers_above)
{
    int i = 0;
    int lSize = (int)layers_above.size();

    while (i < lSize && layers_above[i]->get_ID() != l->get_ID())
        i++;

    return i < lSize;
}

void simulation_Process(vector<Layer *> &layer, const vector<Variable *> &vars)
{
    cout << "Simulation process is beginning..." << endl;
    try
    {
        int initialSize = (int)layer.size();
        vector<Layer *> _v;
        int j = 0;
        int i = 0;
        int a = 1;
        while (layer.size() != initialSize - 1)
        {

            if (i == (int)vars.size())
            {
                i = 0;
            }

            Layer *newLayer = layer[j]->change(vars[i]);

            if (newLayer != nullptr)
            {
                cout << "Round: " << a << endl;
                cout << "Layer type: ";
                layer[j]->print();
                cout << "\nNewLayer: ";
                newLayer->print();
                if (!(search(newLayer, _v)) && !newLayer->perish())
                {
                    _v.push_back(newLayer);
                }
            }

            if (!(layer[j]->perish()))
                _v.push_back(layer[j]);
            else
            {
                delete layer[j];
            }
            i++;
            j++;
            if (j == (int)layer.size())
            {
                cout << "Case -> Index of j equals to size of layer: " << endl;
                cout << "Remaining: \n";
                j = 0;
                layer = _v;
                _v.clear();
                for (auto v : layer)
                {
                    v->print();
                }
            }
            a++;
        }
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }
}

void destroy(vector<Layer *> &layers)
{
    for (int i = 0; i < (int)layers.size(); ++i)
        delete layers[i];
}

void destroyVar()
{
    Sunshine::destroy();
    Other::destroy();
    Thunder::destroy();
}

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    vector<Layer *> layers;
    vector<Variable *> vars;
    try
    {
        create("input.txt", layers, vars);
        cout << "Size of layers: " << layers.size() << endl;
        simulation_Process(layers, vars);
        destroy(layers);
        destroyVar();
    }
    catch (exception e)
    {
        e.what();
    }
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("final size", "input.txt")
{
    vector<Layer *> layers;
    vector<Variable *> vars;
    create("input.txt", layers, vars);
    simulation_Process(layers, vars);
    CHECK(layers.size() == 3);
}
TEST_CASE("more layers", "inp1.txt")
{
    vector<Layer *> layers;
    vector<Variable *> vars;
    int countOfLayers = 0;
    create("inp1.txt", layers, vars);
    simulation_Process(layers, vars);
    CHECK(layers.size() == 9);
}

#endif // NORMAL_MODE
