#pragma once
#include "stat_modifier.h"
#include "element.h"
#include <vector>

class Component;

template <class T>
class ElementDependentStatModifier : public T {
public:
	static_assert(std::is_base_of<StatModifier, T>::value, "Invalid template argument"); // Compile time safety

	template < typename...  Args>
	ElementDependentStatModifier(float val, AbstractFeature* feature, Component& c, std::vector<Element> e, Args &&... args)
	: comp(c), elements(e), T(val, feature, std::forward<Args>(args)...) {};

	virtual float Value() override;

protected:
	Component& comp;
	std::vector<Element> elements;
};