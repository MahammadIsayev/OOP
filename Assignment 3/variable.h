#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED
#include <string>

class Variable
{
public:
    virtual bool isThunder() const { return false; }
    virtual bool isSun() const { return false; }
    virtual bool isOther() const { return false; }
    virtual ~Variable() {}
};

class Other : public Variable
{
public:
    static Other *instance();
    bool isOther() const override { return true; }
    static void destroy();

protected:
    Other() {}

private:
    static Other *_instance;
};

class Thunder : public Variable
{
public:
    static Thunder *instance();
    bool isThunder() const override { return true; }
    static void destroy();

protected:
    Thunder() {}

private:
    static Thunder *_instance;
};

class Sunshine : public Variable
{
public:
    static Sunshine *instance();
    bool isSun() const override { return true; }
    static void destroy();

protected:
    Sunshine() {}

private:
    static Sunshine *_instance;
};

#endif // VARIABLE_H_INCLUDED
