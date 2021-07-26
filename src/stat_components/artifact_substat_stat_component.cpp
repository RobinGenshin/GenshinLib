#include "artifact_substat_stat_component.h"


void ArtifactSubstatComponent::set_amount(int a) {
	amount = a;
	amount_changed = true;
};
ArtifactSubstatComponent::ArtifactSubstatComponent(Stat stat) :StatComponent(), stat_type(stat), amount(0) {};

float ArtifactSubstatComponent::get_value() {
	if (amount_changed) {
		_value = statMap();
		amount_changed = false;
	};
	return _value;
};

float ArtifactSubstatComponent::statMap() {
	return (statMultiplierMap.at(stat_type) * amount * (4.95f / 6.0f) / 100);
};

