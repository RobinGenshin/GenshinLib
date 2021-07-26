#pragma once
#include "weapon.h"
#include "dynamic_feature.h"

class FreedomSworn : public GWeapon {
public:
	FreedomSworn(Player*);

	class SigilOfRebellion : public DynamicFeature {
	public:
		SigilOfRebellion(FreedomSworn&);
		void Activate(Sim& sim) override;
	private:
		int stacks = 0;
	};
};