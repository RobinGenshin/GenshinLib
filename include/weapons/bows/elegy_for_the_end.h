#pragma once
#include "weapon.h"
#include "dynamic_feature.h"

class ElegyForTheEnd : public GWeapon {
public:
	ElegyForTheEnd(Player* p);

	class SigilOfRebellion : public DynamicFeature {
	public:
		SigilOfRebellion(ElegyForTheEnd&);
		void Activate(Sim& sim) override;
	private:
		int stacks = 0;
	};
};
