#pragma once
#include "GameObject.h"

enum class EEvent;

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Notify(const dae::GameObject& pObject, EEvent event) = 0;
};

