#include "amber.h"
#include "sim.h"


TalentData& Amber::get_talent_data(Talent talentName) {
	if ((talentName == Talent::CHARGED) && (player->constellation > 0)) return c1;
	else return GCharacter::get_talent_data(talentName);
};

Amber::Amber(Player* p) : GCharacter(p, Data::Get().get_char_dict().at("Amber")), c1(C1(*this)) {

	talent_event_constructors.at(Talent::SKILL) = [](Player& p, int ticks = -1) {
		return std::make_shared<Skill>(p);
	};

	features.emplace("Amber A2", std::make_unique<A2>(*this));
	features.emplace("Amber A4", std::make_unique<A4>(*this));
	features.emplace("Amber C2", std::make_unique<C2>(*this));
	features.emplace("Amber C3", std::make_unique<C3>(*this));
	features.emplace("Amber C4", std::make_unique<C4>(*this));
	features.emplace("Amber C5", std::make_unique<C5>(*this));
	features.emplace("Amber C6", std::make_unique<C6>(*this));
};

Amber::Skill::Skill(Player& p) : SkillTalentEvent(p), detonated(false) {};

void Amber::Skill::ProcessEvent(Sim& sim) {
	SkillTalentEvent::ProcessEvent(sim);
	dynamic_cast<Amber::C2*>(_player.character.get()->features.at("Amber C2").get())->skills.clear();
};

void Amber::Skill::Detonate(Sim& sim) {
	detonated = true;
	detonation_time = sim.current_time;
};

void Amber::Skill::InitialiseForSim(Sim& sim) {
	SkillTalentEvent::InitialiseForSim(sim);
	if (_player.constellation > 1) {
		dynamic_cast<Amber::C2*>(_player.character.get()->features.at("Amber C2").get())->skills.push_back(this);
	};
};

float Amber::Skill::get_event_time() {
	if (detonated) return detonation_time;
	else return SkillTalentEvent::get_event_time();
};

float Amber::Skill::get_ratio(DamageScalingStat statType, int tick) {
	float r = SkillTalentEvent::get_ratio(statType, tick);
	if (detonated) r = r + 2.0f;
	return r;
};


Amber::A2::A2(Amber& amber) : StaticFeature<>(amber, Data::Get().get_feature_dict().at("Amber A2")) {};

Amber::A4::A4(Amber& amber) : StatModifierDecorator<DynamicFeature>(amber, Data::Get().get_feature_dict().at("Amber A4")) {};

Amber::C1::C1(Amber& amber) : TalentData(*amber.talent_data.at(Talent::CHARGED).get()) {
	ticks = 2;
	times.push_back(times.at(0));
	damage.at(DamageScalingStat::ATK).push_back(0.248f);
};

Amber::C2::C2(Amber& amber) : DynamicFeature(amber, Data::Get().get_feature_dict().at("Amber C2")) {};
void Amber::C2::Activate(Sim& sim) {
	for (auto& i : skills) {
		if (!i->detonated) i->Detonate(sim);
	};
};

Amber::C3::C3(Amber& amber) : StaticFeature<>(amber, Data::Get().get_feature_dict().at("Amber C3")) {};

Amber::C4::C4(Amber& amber) : StaticFeature<>(amber, Data::Get().get_feature_dict().at("Amber C4")) {};

Amber::C5::C5(Amber& amber) : StaticFeature<>(amber, Data::Get().get_feature_dict().at("Amber C5")) {};

Amber::C6::C6(Amber& amber) : StatModifierDecorator<DynamicFeature>(amber, Data::Get().get_feature_dict().at("Amber C6")) {};
