#include "MiniginPCH.h"
#include "BoxCollider.h"

#include "GameObject.h"
#include "PhysicsManager.h"
#include "Renderer.h"

BoxCollider::BoxCollider(dae::GameObject* pGO, SDL_Rect rect)
    :Component(pGO)
	,m_Collider(rect)
{
    PhysicsManager::GetInstance().AddBoxCollider(this);
}

BoxCollider::BoxCollider(dae::GameObject* pGO, int size)
    :Component(pGO)
    , m_Collider({ 0, 0,size,size })
{
    PhysicsManager::GetInstance().AddBoxCollider(this);
}

BoxCollider::~BoxCollider()
{
    PhysicsManager::GetInstance().RemoveBoxCollider(this);
}

void BoxCollider::Update()
{
}

void BoxCollider::FixedUpdate()
{
}

void BoxCollider::Render() const
{
    const auto objPos = GetGameObject()->GetLocalPosition();
    const SDL_Rect colWorldPos { static_cast<int>(m_Collider.x + objPos.x),static_cast<int>(m_Collider.y + objPos.y),m_Collider.w,m_Collider.h };
    dae::Renderer::GetInstance().RenderRectangle(colWorldPos,m_Color);
}

bool BoxCollider::IsOverlapping(const BoxCollider* collider, bool includeBorder) const
{
    const auto objPos = GetGameObject()->GetLocalPosition();
    const SDL_Rect colWorldPos{ static_cast<int>(m_Collider.x + objPos.x),static_cast<int>(m_Collider.y + objPos.y),m_Collider.w,m_Collider.h };

    const auto otherObjPos = collider->GetGameObject()->GetLocalPosition();
    const SDL_Rect other = collider->GetBoxCollider();
    const SDL_Rect otherColPos{ static_cast<int>(other.x + otherObjPos.x),static_cast<int>(other.y + otherObjPos.y),other.w,other.h };

    const SDL_Point l1{ otherColPos.x,otherColPos.y + otherColPos.h }, r1{ otherColPos.x + otherColPos.w, otherColPos.y  };
    const SDL_Point l2{ colWorldPos.x,colWorldPos.y + colWorldPos.h }, r2{ colWorldPos.x + colWorldPos.w, colWorldPos.y  };

    if (includeBorder)
		return !(l1.x > r2.x || l2.x > r1.x || l1.y < r2.y || l2.y < r1.y);
	return !(l1.x >= r2.x || l2.x >= r1.x || l1.y <= r2.y || l2.y <= r1.y);
}

bool BoxCollider::IsOverlapping(BoxCollider* collider, bool includeBorder, std::string tag) const
{
    return IsOverlapping(collider,includeBorder) && GetGameObject()->GetTag() == tag;
}

bool BoxCollider::IsOverlapping(BoxCollider* collider, std::string tag) const
{
    return IsOverlapping(collider) && GetGameObject()->GetTag() == tag;
}
Side BoxCollider::HitSide(const BoxCollider* collider) const
{
    const auto c{ GetCenter() }, oc{ SDL_Point{ static_cast<int>(collider->GetCenter().x + collider->GetGameObject()->GetLocalPosition().x), static_cast<int>(collider->GetCenter().y + collider->GetGameObject()->GetLocalPosition().y)} }; // center, other center
    const auto r{ m_Collider }, ob{collider->GetBoxCollider()}; // rect, other boxcollider

    Side hor, ver;

    const glm::vec2 vec{ oc.x - c.x,oc.y-c.y };
    if (vec.x < 0)
        hor = Side::Left;
    else
        hor = Side::Right;
    if (vec.y > 0)
        ver = Side::Bottom;
    else
        ver = Side::Top;

    if(hor == Side::Right)
    {
	    if(ver == Side::Top)
	    {
            const SDL_Point rt{ r.x + r.w, r.y },lb{ oc.x - ob.w/2,oc.y + ob.h/2 }; // right top, LeftBottom
            const int horD{ abs(rt.x - lb.x) }, verD{ abs(rt.y - lb.y) }; // horizontal Delta, vertical Delta
            if (horD > verD)
            {
                return Side::Top;
            }
            else
            {
                return Side::Right;
            }
	    }
        else if (ver == Side::Bottom)
        {
            const SDL_Point rb{ r.x + r.w, r.y + r.h }, lt{ oc.x-ob.w/2,oc.y - ob.h/2}; // right bottom, LeftTop
            const int horD{ abs(rb.x - lt.x) }, verD{ abs(rb.y - lt.y) }; // horizontal Delta, vertical Delta
            if (horD > verD)
            {
                return Side::Bottom;
            }
            else
            {
                return Side::Right;
            }
        }
    }
    else if(hor == Side::Left)
    {
	    if(ver == Side::Top)
	    {
            const SDL_Point lt{ r.x, r.y}, rb{ oc.x + ob.w/2,oc.y + ob.h/2 }; // left top, RightBottom
            const int horD{ abs(rb.x - lt.x) }, verD{ abs(rb.y - lt.y) }; // horizontal Delta, vertical Delta
            if (horD > verD)
            {
                return Side::Top;
            }
            else
            {
                return Side::Left;
            }
	    }
        else if (ver == Side::Bottom)
        {
            const SDL_Point lb{ r.x, r.y + r.h}, rt{ oc.x + ob.w/2,oc.y - ob.h/2 }; // left bottom, rightTop
            const int horD{ abs(rt.x - lb.x) }, verD{ abs(rt.y - lb.y) }; // horizontal Delta, vertical Delta
            if (horD > verD)
            {
                return Side::Bottom;
            }
            else
            {
                return Side::Left;
            }
        }
    }

    return Side::Right;
}
bool BoxCollider::IsPointInRect(const glm::vec3& point) const
{
    const auto objPos = GetGameObject()->GetLocalPosition();
    SDL_Rect rect{ static_cast<int>(m_Collider.x + objPos.x), static_cast<int>(m_Collider.y + objPos.y), m_Collider.w,m_Collider.h };
    if (point.x >= rect.x && point.x <= rect.x + rect.w && point.y >= rect.y && point.y <= rect.y + rect.h)
        return true;
    return false;
}
