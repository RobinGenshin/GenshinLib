#include "character_dict.h"

CharacterDict& CharacterDict::Get() {
    static CharacterDict instance;
    return instance;
};

CharacterDict::CharacterDict() {
    map["Albedo"] = &createInstance<Albedo>;
    map["Amber"] = &createInstance<Amber>;
};