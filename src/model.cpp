#include "model.h"

model model::add_entity(entity e) const
{
  return model{ entities_.push_back(e) };
}

model model::with_entities(immer::vector<entity> es) const
{
  return model{ std::move(es) };
}

model model::set_quit() const
{
  return model(entities_, true);
}

model::model(immer::vector<entity> entities, bool quit):
  entities_{std::move(entities)},
  quit_{quit}
{}
