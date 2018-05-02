#pragma once

#include <optional>
#include <variant>
#include <vector>

struct up{};
struct down{};
struct left{};
struct right{};

using action = std::variant<up, down, left, right>;

union SDL_Event;

/**
 * Transform an SDL event into an action.
 */
std::optional<action> intent(const SDL_Event& event);

/**
 * Process all the SDL events and transform them into actions.
 */
std::vector<action> intents();

