#pragma once
#include "Observer.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

class SpriteComponent : public Component
{
public:
	struct SourcePart
	{
		int Cols{ 1 };
		int Rows{ 1 };
		SDL_Rect SrcRect{ 0,0 };
		SDL_Point OffSet{ 0,0 };
		SDL_Point StartPos{};

		SourcePart() = default;
		SourcePart(const std::string& texturePath, int cols, int rows, const SDL_Rect& srcRect, const SDL_Point& offset)
			:m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(texturePath))
			,Cols(cols)
			,Rows(rows)
			,SrcRect(srcRect)
			,OffSet(offset)
			,StartPos({srcRect.x, srcRect.y})
		{
		}
		SourcePart(const std::string& texturePath, int cols, int rows, const SDL_Point& startPos, const SDL_Point& offset)
			:m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(texturePath))
			, Cols(cols)
			, Rows(rows)
			, OffSet(offset)
			, StartPos(startPos)
		{
			int width, height;
			SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &width, &height);
			SrcRect = { startPos.x,startPos.y, width,height};
		}

		bool operator==(const SourcePart& other) const
		{
			return Cols == other.Cols && Rows == other.Rows && OffSet.x == other.OffSet.x && OffSet.y == other.OffSet.y && StartPos.x == other.StartPos.x && StartPos.y == other.StartPos.y && SrcRect.x == other.SrcRect.x && SrcRect.y == other.SrcRect.y && SrcRect.w == other.SrcRect.w && SrcRect.h == other.SrcRect.h;
		}
		const dae::Texture2D* GetTexture() const { return m_pTexture; }
	private:
		const dae::Texture2D* m_pTexture{ nullptr };
	};


	SpriteComponent(dae::GameObject* pGO, const SourcePart& sourcePart, const SDL_Rect& dstRect, float animationTime = 1, bool flip = false);
	~SpriteComponent() override = default;

	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) noexcept = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void SetFlip(bool flip);

	bool HasReachedEnd()const
	{
		return m_ReachedEnd;
	}

	void ChangeState(const SourcePart& sp)
	{
		if (m_SourcePart == sp)
			return;
		m_SourcePart = sp;
		m_CurCol = m_CurRow = 1;
		m_curTimer = 0;
	}

	void ResetComponent() override { m_Flip = false; m_ReachedEnd = false; m_curTimer = 0;	m_CurCol = m_CurRow = 1; }
	SourcePart GetSourcePart()const { return m_SourcePart; }
private:
	void MoveToNextFrame();
	SDL_Rect m_DstRect{};

	float m_AnimationTime{ 1 };
	bool m_Flip{ false };

	SourcePart m_SourcePart{};

	float m_curTimer{ 0 }, m_CurCol{ 1 }, m_CurRow{ 1 };
	bool m_ReachedEnd{ false };
};

