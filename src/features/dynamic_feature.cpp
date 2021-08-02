#include "dynamic_feature.h"
#include "feature_data.h"
#include "abstract_event.h"
#include "sim.h"

DynamicFeature::DynamicFeature(Component& _component, const FeatureData _data) : AbstractFeature(_component, _data), cd(0) {
	AbstractFeature::isDynamic = true;
};


bool DynamicFeature::FieldCheck(Sim& sim, AbstractEvent& event) {
	return ((event.get_player() == *(sim.current_player)) || !data.field);
};


void DynamicFeature::CheckEvent(Sim& sim, AbstractEvent& event, std::string timing) {

	if (!enabled()) return;
	if (cd > 0) return;
	if (!FieldCheck(sim, event)) return;
	if (!(timing == data.timing)) return;

	for (auto& i : event.get_triggers()) {
		if ((data.condition.front() == "any") || (std::find(data.condition.begin(), data.condition.end(), i) != data.condition.end())) {
			Activate(sim);
			return;
		};
	};
};

void DynamicFeature::Activate(Sim& sim) {
	if (data.cd > float(0)) cd = data.cd;
};

void DynamicFeature::PassTime(float dt) {
	cd = std::max(float(0), cd - dt);
};