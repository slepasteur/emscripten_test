#pragma once

#include <immer/vector.hpp>
#include "entity.h"
#include "transform.h"

class model
{
public:
  model() {}

  model add_entity(entity e) const;
  model with_entities(immer::vector<entity> es) const;

  template <typename F>
  model update_entities(F f)
  {
    return with_entities(transform(entities_, f));
  }
  
  template <typename P, typename F>
  model update_entities(P predicate, F func)
  {
    return with_entities(transform(entities_, predicate, func));
  }

  model set_quit() const;
  
  const immer::vector<entity>& entities() const { return entities_; }
  bool should_quit() const { return quit_; }

private:
  model(immer::vector<entity> entities, bool quit = false);

  immer::vector<entity> entities_;

  bool quit_;
};

