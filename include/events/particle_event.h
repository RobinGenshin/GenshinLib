#pragma once
#include "abstract_event.h"
#include "element.h"

class ParticleEvent : public AbstractEvent {
public:

	Element element;
	float amount;

	ParticleEvent(Player& e, Element element, float amount);
	virtual ~ParticleEvent() {};
	float get_event_time() override;

	virtual void ProcessEvent(Sim& sim) override;
	virtual std::vector<std::string> get_triggers() override;
	virtual void PostProcessEvent(Sim& sim) override;
};