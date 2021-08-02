#include "static_feature.h"
#include "feature_data.h"
#include "linear_refine_stat_modifier.h"
#include "staff_of_homa.h"
#include "primordial_jade_winged_spear.h"
#include "primordial_jade_cutter.h"
#include "lithic.h"
#include "hamayumi.h"
#include "element_dependent_stat_modifier.h"

template <class S>
float StaticFeature<S>::get_stat(Stat stat) {
	if (enabled()) return FeatureStatModifierContainer::get_stat(stat);
	else return 0;
};

template class StaticFeature<StatModifier>;
template class StaticFeature<LinearRefineStatModifier>;
template class StaticFeature<StaffOfHoma::HPConversionModifier>;
template class StaticFeature<PrimordialJadeWingedSpear::StackCheckStaticModifier>;
template class StaticFeature<PrimordialJadeCutter::HPConversionModifier>;
template class StaticFeature<LithicStatModifier>;
template class StaticFeature<Hamayumi::HamayumiStatModifier>;

template class StaticFeature<ElementDependentStatModifier<StatModifier>>;
template class StaticFeature<ElementDependentStatModifier<LinearRefineStatModifier>>;
