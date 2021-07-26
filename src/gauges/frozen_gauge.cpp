#include "frozen_gauge.h"
#include <cmath>

FrozenGauge::FrozenGauge(float _gauge) : ElementalGauge() {
	time_remaining = 2 * std::sqrt(5 * _gauge + 4) - 4;
};

void FrozenGauge::AddToGauge(float units, bool aura) {

	float new_time = 2.0f * std::sqrt(5.0f * 2.0f * units + 4.0f) - 4.0f;

	if (time_remaining < new_time) time_remaining = new_time;
};

float FrozenGauge::get_gauge() {
	return (std::pow(time_remaining, 2.0f) / 20.0f) + (2.0f * time_remaining / 5.0f);
};

void FrozenGauge::PassTime(float dt) {
	time_remaining = std::max(float(0), time_remaining - dt);
}

void FrozenGauge::SubtractFromGauge(float dg) {
	float n_g = get_gauge() - dg;
	time_remaining = 2 * std::sqrt(5 * 2 * n_g + 4) - 4;
};