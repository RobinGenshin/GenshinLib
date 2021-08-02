#pragma once
#include "weapon.h"
#include "stat_component.h"

class ThunderingPulse : public GWeapon {
public:
	ThunderingPulse(Player* p);

	class ThunderingPulseStatComponent : public StatComponent {
	public:
		ThunderingPulseStatComponent(ThunderingPulse& ms);
		ThunderingPulse& tp;
		float get_value() override;
	};
};
