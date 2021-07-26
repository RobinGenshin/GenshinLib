#include "elemental_gauges.h"
#include <cmath>
#include "damage_event.h"
#include "sim.h"
#include "transformative_reaction_event.h"
#include "enum_maps.h"

ElementalGaugesVector::ElementalGaugesVector() : gauges() {};

ElementalGauge::ElementalGauge(Element _element, int units, bool aura) : element(_element) {
	float tax;
	if (!aura) tax = 0.2f;
	else tax = 0;

	gauge = units * (1 - tax);
	decay_rate = (gauge * 2.5f + 7) / gauge;
	time_remaining = gauge * decay_rate;
};

float ElementalGauge::get_gauge() {
	return gauge;
}

void ElementalGauge::set_gauge(float g) {
	gauge = g;
}

void ElementalGauge::PassTime(float dt) {
	time_remaining = std::max(float(0), time_remaining - dt);
	gauge = std::max(float(0), gauge - ((1/decay_rate) * dt));
}

void ElementalGauge::SubtractFromGauge(float dg) {
	gauge -= dg;
}

void ElementalGauge::AddToGauge(float units, bool aura) {
	float tax;
	if (!aura) tax = 0.2f;
	else tax = 0;

	float trigger_gauge = units * (1 - tax);
	gauge = std::max(gauge, trigger_gauge);
};