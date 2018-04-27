#pragma once

#include <immer/vector.hpp>
#include "draw/drawable.h"

class model
{
public:
  model() {}

  const immer::vector<drawable>& entities() const
  {
    return entities_;
  }

  model add_entity(drawable e)
  {
    return model{
      entities_.push_back(e)
    };
  }

private:
  model(immer::vector<drawable> entities):
    entities_{std::move(entities)}
  {}

  immer::vector<drawable> entities_;
};

