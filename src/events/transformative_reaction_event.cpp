#include "transformative_reaction_event.h"
#include "enum_maps.h"
#include "damage_calculation.h"

TransformativeReactionEvent::TransformativeReactionEvent(Player& p, TransformativeReaction t_r) : AbstractEvent(p), transformative_reaction(t_r) {};

float TransformativeReactionEvent::get_event_time() { return _initial_time; };

void TransformativeReactionEvent::ProcessEvent(Sim& sim) {
	sim.damage += DamageCalculation::TransformativeCalculate(*this, sim);
};

std::vector<std::string> TransformativeReactionEvent::get_triggers() {
	return { EnumMap::get_string_transformative(transformative_reaction) };
};