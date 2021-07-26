#pragma once
#include <map>
#include <memory>

enum class Element;
class DamageEvent;
class Sim;
class ElementalGauge;

class ElementalGaugesVector {
public:

	ElementalGaugesVector();
	ElementalGaugesVector(const ElementalGaugesVector& toCopy) = delete;
	void ApplyElement(Sim& sim, DamageEvent& event, bool aura = false);
	void Update();

	std::map<Element, std::shared_ptr<ElementalGauge>>& get_gauges() { return gauges; };

private:
	std::map<Element, std::shared_ptr<ElementalGauge>> gauges;
};