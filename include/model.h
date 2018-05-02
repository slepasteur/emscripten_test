#pragma once

#include <immer/vector.hpp>
#include "entity.h"

class model
{
public:
  model() {}

  const immer::vector<entity>& entities() const
  {
    return entities_;
  }

  model add_entity(entity e)
  {
    return model{
      entities_.push_back(e)
    };
  }

private:
  model(immer::vector<entity> entities):
    entities_{std::move(entities)}
  {}

  immer::vector<entity> entities_;
};

