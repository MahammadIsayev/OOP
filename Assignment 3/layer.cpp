#include "layer.h"
#include "variable.h"

Layer *CO2::change(const Variable *var)
{
  if (var->isSun())
  {
    double thick = this->_thickness * 0.05;
    this->changeThickness(thick);
    return new Oxygen(thick);
  }
  return nullptr;
}

Layer *Oxygen::change(const Variable *var)
{
  if (var->isSun())
  {
    double thick = this->_thickness * 0.05;
    this->changeThickness(thick);
    return new Ozone(thick);
  }
  if (var->isThunder())
  {
    double thick = this->_thickness * 0.5;
    this->changeThickness(thick);
    return new Ozone(thick);
  }
  if (var->isOther())
  {
    double thick = this->_thickness * 0.1;
    this->changeThickness(thick);
    return new CO2(thick);
  }
  return nullptr;
}

Layer *Ozone::change(const Variable *var)
{
  if (var->isOther())
  {
    double thick = this->_thickness * 0.05;
    this->changeThickness(thick);
    return new Oxygen(thick);
  }
  return nullptr;
}
