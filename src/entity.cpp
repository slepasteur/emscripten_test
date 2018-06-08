#include "entity.h"

entity::entity(drawable shape, point position, bool selected):
  shape_{std::move(shape)},
  position_{std::move(position)},
  selected_{selected}
{
}

void entity::draw(sdl_renderer& renderer, const point& pos) const
{
  ::draw(shape_, renderer, pos + position_);
}

entity entity::select() const
{
  return {shape_, position_, true};
}

entity entity::deselect() const
{
  return {shape_, position_, false};
}

entity entity::move(const point& offset) const
{
  return {shape_, position_ + offset, selected_};
}

