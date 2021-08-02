#pragma once
#include "weapon.h"
#include "static_feature.h"
#include "linear_refine_stat_modifier.h"
#include "dynamic_feature.h"
#include "stat_modifier_decorator.h"

class Mistsplitter : public GWeapon {
public:
	Mistsplitter(Player* p);

	class MistsplitterStatComponent : public StatComponent {
	public:
		MistsplitterStatComponent(Mistsplitter& ms);
		Mistsplitter& mistsplitter;
		float get_value() override;
	};
};