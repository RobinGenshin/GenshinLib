#pragma once
#include "particle_event.h"
#include "dynamic_feature.h"
#include "percentage_decorator.h"

class FavoniusTrigger : public PercentageDecorator<DynamicFeature> {
public:
	FavoniusTrigger(Component& _component, FeatureData _data);
	virtual void ActivatePct(Sim& sim) override;
	virtual float get_pct() override;

	class FavoniusParticleEvent : public ParticleEvent {
	public:
		FavoniusParticleEvent(Player& p);
	};

};