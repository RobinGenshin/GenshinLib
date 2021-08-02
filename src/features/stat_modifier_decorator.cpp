#include "stat_modifier_decorator.h"
#include "feature_data.h"
#include "stat_modifier.h"
#include <stdexcept>
#include "linear_refine_stat_modifier.h"
#include "mistsplitter.h"
#include "skyward_blade.h"
#include "summit_shaper.h"
#include "royal.h"
#include "shield_wep.h"
#include "element_dependent_stat_modifier.h"
#include "alley_hunter.h"


template <class T, class S>
float StatModifierDecorator<T,S>::get_stat(Stat statName) {
	if (std::find(stats.begin(), stats.end(), statName) == stats.end()) return 0;
	float v = stat_modifiers.at(statName).get()->Value();
	return v;
}

template class StatModifierDecorator<DynamicFeature, StatModifier>;
template class StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>;
template class StatModifierDecorator<SkywardBlade::Trigger, LinearRefineStatModifier>;
template class StatModifierDecorator<DynamicFeature, RoyalStatModifier>;
template class StatModifierDecorator<DynamicFeature, ShieldWepStacks>;
template class StatModifierDecorator<DynamicFeature, ElementDependentStatModifier<LinearRefineStatModifier>>;
template class StatModifierDecorator<DynamicFeature, AlleyHunter::AlleyHunterStatModifier>;