#ifndef ENTITY_H
#define ENTITY_H

#include <utility>

class Entity
{
private:
  std::pair<float, float> position;
  std::pair<float, float> velocity;

public:
  Entity();
};

class ScuttleCrab : public Entity
{
public:
  float health;

public:
  ScuttleCrab();
};

#endif // ENTITY_H
