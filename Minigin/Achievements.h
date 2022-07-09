#pragma once
#include "Observer.h"
enum class EEvent;

class Achievements final :
    public Observer
{
public:
    void Notify(const dae::GameObject& gameObject, EEvent event) override;
private:
    void Unlock(EEvent achievement);
    std::vector<EEvent> m_UnlockedAchievments{};
};

