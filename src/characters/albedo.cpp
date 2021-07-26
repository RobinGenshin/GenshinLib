#include "albedo.h"
#include "character.h"
#include "player.h"
#include "sim.h"
#include "particle_event.h"
#include "talent_scaling.h"

Albedo::Albedo(Player* p) : GCharacter(p, Data::Get().get_char_dict().at("Albedo")) {
	damage_data.emplace("transient blossom", std::make_unique<TBData>());
	dynamic_cast<TalentData*>(talent_data.at(Talent::BURST).get())->damage.emplace(DamageScalingStat::DEF, std::vector<float>{});

	talent_event_constructors.at(Talent::BURST) = [](Player& p, int ticks = -1) {
		return std::make_shared<Burst>(p);
		};

	features.emplace("Albedo A2", std::make_unique<A2>(*this));
	features.emplace("Albedo E Cast", std::make_unique<SkillCast>(*this));
	features.emplace("Albedo E Trigger", std::make_unique<SkillTrigger>(*this));
	features.emplace("Albedo A4", std::make_unique<A4>(*this));
	features.emplace("Albedo C1", std::make_unique<C1>(*this));
	features.emplace("Albedo C2", std::make_unique<C2>(*this));
	features.emplace("Albedo C3", std::make_unique<C3>(*this));
	features.emplace("Albedo C4", std::make_unique<C4>(*this));
	features.emplace("Albedo C5", std::make_unique<C5>(*this));
	features.emplace("Albedo C6", std::make_unique<C6>(*this));
};

Albedo::Burst::Burst(Player& p) : BurstTalentEvent(p), c2_stacks(0) {
};

float Albedo::Burst::get_ratio(DamageScalingStat stat, int tick) {
	if (stat == DamageScalingStat::DEF) return (c2_stacks * 0.3);
	else return BurstTalentEvent::get_ratio(stat, tick);
};

void Albedo::Burst::InitialiseForSim(Sim& sim) {
	BurstTalentEvent::InitialiseForSim(sim);
	c2_stacks = dynamic_cast<Albedo*>(_player.character.get())->c2_stacks;
	dynamic_cast<Albedo*>(_player.character.get())->c2_stacks = 0;
};

Albedo::TBData::TBData() : TalentData() {
	talent_type = Talent::SKILL;
	ticks = 1;
	times = { 0.1f };
	element = Element::GEO;
	damage = { { DamageScalingStat::DEF, { 1.34f } } };
	units = { 1 };
	particles = { 0.7f };
}

Albedo::TransientBlossom::TransientBlossom(Player& _player, TalentData& td) : DamageEvent(_player, td) {
};

std::vector<std::string> Albedo::TransientBlossom::get_triggers() {
	std::vector<std::string> vec = DamageEvent::get_triggers();
	vec.emplace_back("transient blossom");
	return vec;
};

void Albedo::TransientBlossom::ProcessEvent(Sim& sim) {
	DamageEvent::ProcessEvent(sim);
	sim.AddEvent(std::make_shared<ParticleEvent>(_player, data.element, dynamic_cast<TalentData&>(data).particles.at(get_tick())));
};

float Albedo::TransientBlossom::get_ratio(DamageScalingStat damageType, int tick) {
	float m = TalentScaling::Get().scaling_map.at("Elemental1").at(_player.get_skill_level());
	return m * DamageEvent::get_ratio(damageType, tick);
}

Albedo::SkillCast::SkillCast(Albedo& albedo) : DynamicFeature(albedo, Data::Get().get_feature_dict().at("Albedo E Cast")) {};

void Albedo::SkillCast::Activate(Sim& sim) {
	dynamic_cast<TemporaryDecorator<DynamicFeature>*>(component.features.at("Albedo E Trigger").get())->TemporarilyEnable();
};

Albedo::SkillTrigger::SkillTrigger(Albedo& albedo) : TemporaryDecorator<DynamicFeature>(albedo, Data::Get().get_feature_dict().at("Albedo E Trigger")) {};
void Albedo::SkillTrigger::Activate(Sim& sim) {
	sim.AddEvent(std::make_shared<Albedo::TransientBlossom>(*(component.player), *dynamic_cast<TalentData*>(component.damage_data.at("transient blossom").get())));
	cd = 2;
};

Albedo::A2::A2(Albedo& albedo) : StaticFeature<>(albedo, Data::Get().get_feature_dict().at("Albedo A2")) {};

Albedo::A4::A4(Albedo& albedo) : StatModifierDecorator<DynamicFeature>(albedo, Data::Get().get_feature_dict().at("Albedo A4")) {};

Albedo::C1::C1(Albedo& albedo) : DynamicFeature(albedo, Data::Get().get_feature_dict().at("Albedo C1")) {};
void Albedo::C1::Activate(Sim& sim) {
	dynamic_cast<Player*>(component.player)->energy += 1.2;
};

Albedo::C2::C2(Albedo& albedo) : DynamicFeature(albedo, Data::Get().get_feature_dict().at("Albedo C2")) {};
void Albedo::C2::Activate(Sim& sim) {
	dynamic_cast<Albedo&>(component).c2_stacks = std::min(7, dynamic_cast<Albedo&>(component).c2_stacks+1);
};

Albedo::C3::C3(Albedo& albedo) : StaticFeature<>(albedo, Data::Get().get_feature_dict().at("Albedo C3")) {};

Albedo::C4::C4(Albedo& albedo) : StatModifierDecorator<DynamicFeature>(albedo, Data::Get().get_feature_dict().at("Albedo C4")) {};

Albedo::C5::C5(Albedo& albedo) : StaticFeature<>(albedo, Data::Get().get_feature_dict().at("Albedo C5")) {};

Albedo::C6::C6(Albedo& albedo) : StatModifierDecorator<DynamicFeature>(albedo, Data::Get().get_feature_dict().at("Albedo C6")) {};