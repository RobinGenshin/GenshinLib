#pragma once
#include "weapon.h"
#include "stat_modifier.h"

class StaffOfHoma : public GWeapon {
public:
	StaffOfHoma(Player* p);

	class HPConversionModifier : public StatModifier {
	public:
		HPConversionModifier(float val, AbstractFeature* f, StaffOfHoma& _homa);
		virtual float Value() override;
	private:
		StaffOfHoma& homa;
	};

};