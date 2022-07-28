#pragma once
class PlayerController
{
public:
	explicit PlayerController() = default;
	virtual ~PlayerController() = default;
	
	virtual void Update() const = 0;
};

