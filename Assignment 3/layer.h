#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED
#include <string>
#include <iostream>
#include "variable.h"

class Layer
{
protected:
    double _thickness;
    Layer(double t = 0) : _thickness(t) {}

public:
    virtual void print() const = 0;
    virtual int get_ID() const = 0;
    double getThickness() const { return _thickness; }
    bool perish() const { return _thickness < 0.5; }
    void changeThickness(double t) { _thickness -= t; }
    virtual Layer *change(const Variable *var) = 0;
    virtual ~Layer() {}
};

class Oxygen : public Layer
{
public:
    Oxygen(double t = 0) : Layer(t) {}
    Layer *change(const Variable *var) override final;
    ~Oxygen() {}
    void print() const override { std::cout << "X " << _thickness << std::endl; }
    int get_ID() const override { return 1; }
};

class Ozone : public Layer
{
public:
    Ozone(double t = 0) : Layer(t) {}
    Layer *change(const Variable *var) override final;
    void print() const override { std::cout << "Z " << _thickness << std::endl; }
    ~Ozone() {}
    int get_ID() const override { return 2; }
};

class CO2 : public Layer
{
public:
    CO2(double t = 0) : Layer(t) {}
    Layer *change(const Variable *var) override final;
    void print() const override { std::cout << "C " << _thickness << std::endl; }
    int get_ID() const override { return 3; }
    ~CO2() {}
};

#endif // LAYER_H_INCLUDED
