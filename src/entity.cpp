#include "entity.h"

entity::entity(drawable shape, point position):
  shape_{std::move(shape)},
  position_{std::move(position)}
{
}

void entity::draw(sdl_renderer& renderer, const point& pos) const
{
  ::draw(shape_, renderer, pos + position_);
}
