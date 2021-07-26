#pragma once
#include "abstract_feature.h"

class DynamicFeature : public AbstractFeature {
public:
	DynamicFeature() = delete;
	DynamicFeature(Component& _component, FeatureData _data);
	float cd;

	bool FieldCheck(Sim& sim, AbstractEvent& event);
	virtual void CheckEvent(Sim& sim, AbstractEvent& event, std::string timing);
	virtual void Activate(Sim& sim);
	virtual void PassTime(float dt);
};

