#include "update.h"

#include <variant>
#include <tuple>

#include "draw/rectangle.h"
#include "draw/line.h"
#include "sdl/sdl_utils.h"
#include "overloaded.h"
#include "functions.h"

model update(model m, action a)
{
  return std::visit(overloaded {
      [&] (up) {
        return m.update_entities(
          on_selected( [](const auto& e){ return e.move(point{0, -1}); } )
        );
      },
      [&] (down) {
        return m.update_entities(
          on_selected( [](const auto& e){ return e.move(point{0, 1}); } )
        );
      },
      [&] (left) {
        return m.update_entities(
          on_selected( [](const auto& e){ return e.move(point{-1, 0}); } )
        );
      },
      [&] (right) {
        return m.update_entities(
          on_selected( [](const auto& e){ return e.move(point{1, 0}); } )
        );
      },
      [&] (selection s) {
        return m.update_entities(
          all(
            on_selected( [](const auto& e){ return e.deselect(); } ),
            on_colliding( s.coordinates_, [](const auto& e){ return e.select(); } )
          )
        );
      },
      [&] (insert_entity i) {
        return m.add_entity(
          entity{
            drawable(rectangle(width{150}, height{75}, color::red())),
            i.coordinates_
          }.with_bbox(bounding_box{point{0,0}, width{150}, height{75}})
        );
      }
  }, a);
}

