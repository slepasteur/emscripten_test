#include "entity.h"

entity::entity(drawable shape, point position):
  shape_{std::move(shape)},
  position_{std::move(position)},
  bbox_{point{0, 0}, point{0, 0}},
  selected_{false}
{
}

void entity::draw(sdl_renderer& renderer, const point& pos) const
{
  ::draw(shape_, renderer, pos + position_);
}

entity entity::select() const
{
  auto e = *this;
  e.selected_ = true;
  return e;
}

entity entity::deselect() const
{
  auto e = *this;
  e.selected_ = false;
  return e;
}

entity entity::with_bbox(bounding_box bbox) const
{
  auto e = *this;
  e.bbox_ = std::move(bbox);
  return e;
}

entity entity::move(const point& offset) const
{
  auto e = *this;
  e.position_ = position_ + offset;
  return e;
}

bounding_box entity::bbox() const
{
  return bounding_box{bbox_.top_left() + position_, bbox_.bottom_right() + position_};
}
