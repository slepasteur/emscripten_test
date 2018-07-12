#pragma once

#include <optional>
#include <variant>
#include <vector>

#include "geometry/point.h"

struct up{};
struct down{};
struct left{};
struct right{};
struct selection{ point coordinates_; };
struct insert_entity{ point coordinates_; };
struct quit{};

using action = std::variant<up, down, left, right, selection, insert_entity, quit>;

union SDL_Event;

/**
 * Transform an SDL event into an action.
 */
std::optional<action> intent(const SDL_Event& event);

/**
 * Process all the SDL events and transform them into actions.
 */
std::vector<action> intents();

