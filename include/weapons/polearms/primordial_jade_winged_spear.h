#pragma once
#include "weapon.h"
#include "static_feature.h"
#include "linear_refine_stat_modifier.h"

class PrimordialJadeWingedSpear : public GWeapon {
public:
	PrimordialJadeWingedSpear(Player* p);

	class StackCheckStaticModifier : public LinearRefineStatModifier {
	public:
		StackCheckStaticModifier(float val, AbstractFeature* feature, PrimordialJadeWingedSpear& pjws);
		virtual float Value() override;
		PrimordialJadeWingedSpear& pjws;
	};
};