#pragma once
#include "Component.h"
enum class Side{
	Left,
	Right,
	Bottom,
	Top
};
class BoxCollider final: public Component
{
	public:
		BoxCollider(dae::GameObject* pGO, SDL_Rect rect) ;
		BoxCollider(dae::GameObject* pGO,int size);
		~BoxCollider() override;

		BoxCollider(const BoxCollider& other) = delete;
		BoxCollider(BoxCollider&& other) noexcept = delete;
		BoxCollider& operator=(const BoxCollider& other) = delete;
		BoxCollider& operator=(BoxCollider&& other) noexcept = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		bool IsOverlapping(const BoxCollider* collider, bool includeBorder = false) const;
		bool IsOverlapping(BoxCollider* collider, bool includeBorder, std::string tag ) const;
		bool IsOverlapping(BoxCollider* collider, std::string tag) const;

		Side HitSide(const BoxCollider* collider) const;

		bool IsPointInRect(const  glm::vec3& point)const;

		SDL_Point GetCenter() const { return { m_Collider.x + m_Collider.w / 2, m_Collider.y + m_Collider.h / 2 }; }

		SDL_Rect GetBoxCollider() const { return m_Collider; }
		void SetBoxCollider(SDL_Rect col) { m_Collider = col; }
		void SetColor(const SDL_Color& color) { m_Color = color; }
	private:
		SDL_Rect m_Collider{};
		SDL_Color m_Color{ 255,255,255,1 };
};

