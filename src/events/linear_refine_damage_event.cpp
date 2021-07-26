#include "linear_refine_damage_event.h"
#include "player.h"

LinearRefineDamageEvent::LinearRefineDamageEvent(Player& e, DamageData& dd, float l_i) : DamageEvent(e, dd), linear_pct_increase(l_i) {};

float LinearRefineDamageEvent::get_ratio(DamageScalingStat stat, int tick) {
	return DamageEvent::get_ratio(stat, tick) * (1 + linear_pct_increase * float(get_player().refinement - 1));
};

//void LinearRefineDamageEvent::ProcessEvent(Sim& sim) {
//	DamageEvent::ProcessEvent(sim);
//};