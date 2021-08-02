#include "percent_handler.h"
#include <cmath>

PercentHandler::PercentHandler() {};
void PercentHandler::IncreasePct(float dt, Sim& sim) {
	pct += dt;
	if (pct >= 1) {
		ActivatePct(sim);
		pct = pct - floor(pct);
	};
};

void PercentHandler::ActivatePct(Sim& sim) {};