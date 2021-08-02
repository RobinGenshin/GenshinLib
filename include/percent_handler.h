#pragma once

class Sim;

class PercentHandler {
public:
	PercentHandler();
	virtual void IncreasePct(float dp, Sim& sim);
	virtual void ActivatePct(Sim& sim);
protected:
	float pct = 0;
};