#pragma once
#include <string>
#include <map>
#include <memory>
#include "character.h"
#include "albedo.h"
#include "amber.h"

template<typename T> std::unique_ptr<GCharacter> createInstance(Player* player) { return std::make_unique<T>(player); }
typedef std::map<std::string, std::unique_ptr<GCharacter>(*)(Player* player)> map_type;

class CharacterDict
{
public:
    CharacterDict(const CharacterDict&) = delete;
    static CharacterDict& Get();
    map_type map = {};

private:
    CharacterDict();
};