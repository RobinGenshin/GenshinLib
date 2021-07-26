#include "talent_scaling.h"

TalentScaling& TalentScaling::Get() {
    static TalentScaling instance;
    return instance;
};

TalentScaling::TalentScaling() {
    scaling_map.emplace("Elemental1", Elemental1);
    scaling_map.emplace("Elemental1Alternative", Elemental1Alternative);
    scaling_map.emplace("Elemental2", Elemental2);
    scaling_map.emplace("Physical1", Physical1);
    scaling_map.emplace("Physical1Alternative", Physical1Alternative);
    scaling_map.emplace("Physical2", Physical2);
    scaling_map.emplace("ZhongliBurst", ZhongliBurst);
}