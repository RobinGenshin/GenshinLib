#pragma once
#include "weapon.h"
#include "stat_modifier.h"

class Hamayumi : public GWeapon {
public:
	Hamayumi(Player* p);

	class HamayumiStatModifier : public StatModifier {
	public:
		HamayumiStatModifier(float val, AbstractFeature* feature);
		virtual float Value() override;
	};
};
