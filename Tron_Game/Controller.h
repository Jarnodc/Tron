#pragma once

#include "Observer.h"
#include "SubjectComponent.h"

class Controller : public SubjectComponent, public Observer
{
public:
	Controller(dae::GameObject* pGO):SubjectComponent(pGO),Observer(){}
	virtual ~Controller() override = default;

	Controller(const Controller& other) = delete;
	Controller(Controller&& other) noexcept = delete;
	Controller& operator=(const Controller& other) = delete;
	Controller& operator=(Controller&& other) noexcept = delete;

	void Update() override{}
	void FixedUpdate() override{}
	void Render() const override{}
	
	void Notify(const dae::GameObject& pObject, EEvent event) override;
protected:
private:
	int m_Lives{ 3 };
};

