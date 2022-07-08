#include "MiniginPCH.h"
#include "SpriteComponent.h"

#include "TimerInfo.h"

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const SourcePart& sourcePart, const SDL_Rect& dstRect, float animationTime, bool flip)
	:Component(pGO)
	,m_SourcePart(sourcePart)
	,m_AnimationTime(animationTime)
	,m_DstRect(dstRect)
	,m_Flip(flip)
{
	if (dstRect.w == dstRect.h && dstRect.w == 0)
	{
		const auto dim = m_SourcePart.GetTextureDimensions();
		m_DstRect.w = dim.x / m_SourcePart.Cols;
		m_DstRect.h = dim.y / m_SourcePart.Rows;
	}
}

void SpriteComponent::Update()
{
	m_curTimer += dae::TimerInfo::GetInstance().deltaTime;
	if(m_curTimer >= m_AnimationTime)
	{
		MoveToNextFrame();
		m_curTimer -= m_AnimationTime;
	}
}

void SpriteComponent::FixedUpdate()
{
}

void SpriteComponent::Render() const
{
	const auto pos = GetGameObject()->GetLocalPosition();
	const SDL_Rect tempDstRect{ static_cast<int>(m_DstRect.x + pos.x), static_cast<int>(m_DstRect.y + pos.y), m_DstRect.w,m_DstRect.h };
	dae::Renderer::GetInstance().RenderTexture(*m_SourcePart.GetTexture(), m_SourcePart.SrcRect, tempDstRect, m_Flip);
}

void SpriteComponent::SetFlip(bool flip)
{
	m_Flip = flip;
}

void SpriteComponent::MoveToNextFrame()
{
	if(m_CurCol != m_SourcePart.Cols)
	{
		++m_CurCol;
	}
	else
	{
		m_CurCol = 1;
		if(m_CurRow != m_SourcePart.Rows)
		{
			++m_CurRow;
		}
		else
		{
			m_CurRow = 1;
			m_ReachedEnd = true;
		}
		m_SourcePart.SrcRect.y = static_cast<int>((m_CurRow - 1) *(m_SourcePart.SrcRect.h  + m_SourcePart.OffSet.y) + m_SourcePart.StartPos.y);
	}
	m_SourcePart.SrcRect.x = static_cast<int>((m_CurCol - 1) * (m_SourcePart.SrcRect.w  + m_SourcePart.OffSet.x) + m_SourcePart.StartPos.x);
}

