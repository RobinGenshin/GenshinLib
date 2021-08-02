#include "kitain_cross_spear.h"
#include "player.h"
#include "sim.h"

KitainCrossSpear::KitainCrossSpear(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Kitain Cross Spear")) {
	features.emplace("Kitain Cross Spear Dynamic", std::make_unique<Trigger>
		(*this, Data::Get().get_feature_dict().at("Kitain Cross Spear Dynamic")));
};


KitainCrossSpear::Trigger::Trigger(Component& _component, FeatureData _data) : DynamicFeature(_component, _data) {};
void KitainCrossSpear::Trigger::Activate(Sim& sim) {
	DynamicFeature::Activate(sim);
	sim.AddEvent(std::make_shared<EnergyEvent>(*component.player, 0, -3));
	sim.AddEvent(std::make_shared<EnergyEvent>(*component.player, 2, 3));
	sim.AddEvent(std::make_shared<EnergyEvent>(*component.player, 4, 3));
	sim.AddEvent(std::make_shared<EnergyEvent>(*component.player, 6, 3));
};

KitainCrossSpear::EnergyEvent::EnergyEvent(Player& p, float _dt, int _energy) : AbstractEvent(p), dt(_dt), energy(_energy) {};
float KitainCrossSpear::EnergyEvent::get_event_time() {
	return dt + _initial_time;
}
void KitainCrossSpear::EnergyEvent::ProcessEvent(Sim& sim) {
	AbstractEvent::ProcessEvent(sim);
	if (energy == -3) _player.energy += std::max(float(0), _player.energy-float(3));
	else _player.energy += float(energy) + ((_player.refinement - 1) * 0.5f);
};