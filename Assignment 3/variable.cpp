#include "variable.h"

Thunder *Thunder::_instance = nullptr;
Thunder *Thunder::instance()
{
	if (_instance == nullptr)
	{
		_instance = new Thunder();
	}
	return _instance;
}
void Thunder::destroy()
{
	if (nullptr != _instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}

Sunshine *Sunshine::_instance = nullptr;
Sunshine *Sunshine::instance()
{
	if (_instance == nullptr)
	{
		_instance = new Sunshine();
	}
	return _instance;
}
void Sunshine::destroy()
{
	if (nullptr != _instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}

Other *Other::_instance = nullptr;
Other *Other::instance()
{
	if (_instance == nullptr)
	{
		_instance = new Other();
	}
	return _instance;
}
void Other::destroy()
{
	if (nullptr != _instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}
