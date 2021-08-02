#include "favonius.h"
#include "component.h"
#include "player.h"
#include "sim.h"

FavoniusTrigger::FavoniusTrigger(Component& _component, FeatureData _data) : PercentageDecorator<DynamicFeature>(0, _component, _data) {};
FavoniusTrigger::FavoniusParticleEvent::FavoniusParticleEvent(Player& p) : ParticleEvent(p, Element::PHYSICAL, 3) {};


void FavoniusTrigger::ActivatePct(Sim& sim) {
	PercentageDecorator<DynamicFeature>::ActivatePct(sim);
	sim.AddEvent(std::make_shared<FavoniusTrigger::FavoniusParticleEvent>(*component.player));
	cd = 13.5f - component.player->refinement * 1.5f;
};

float FavoniusTrigger::get_pct() {
	return component.player->get_stat(Stat::CRIT_RATE);
};
