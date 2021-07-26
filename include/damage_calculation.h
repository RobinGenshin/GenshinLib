#pragma once
#include <memory>
#include <string>
#include <functional>
#include "Component.h"
#include "Sim.h"
#include "damage_event.h"
#include "transformative_reaction_event.h"

class DamageCalculation
{
public:
	static float StandardCalculate(DamageEvent& event, Sim& sim);
	static float TransformativeCalculate(TransformativeReactionEvent& t_r_event, Sim& sim);

private:
	static float StandardHelper(DamageEvent& proc, Sim& sim, int tick, DamageScalingStat);

	static float get_level_scaling(int);
	static float get_em_multiplier(Player& p);
};