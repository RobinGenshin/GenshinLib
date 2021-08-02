#pragma once
#include "weapon.h"
#include "dynamic_feature.h"
#include "static_feature.h"

class Component;
struct FeatureData;

class PrimordialJadeCutter : public GWeapon {
public:
	PrimordialJadeCutter(Player* p);

	class HPConversionModifier : public StatModifier {
	public:
		HPConversionModifier(float val, AbstractFeature* feature, PrimordialJadeCutter& _pjc);
		virtual float Value() override;
	private:
		PrimordialJadeCutter& pjc;
	};
};