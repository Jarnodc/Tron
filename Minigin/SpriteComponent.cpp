#include "MiniginPCH.h"
#include "SpriteComponent.h"

#include "GameObject.h"
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

SpriteComponent::SpriteComponent(dae::GameObject* pGO, const SpriteComponent* pSC)
	:Component(pGO)
	, m_SourcePart(pSC->m_SourcePart)
	, m_AnimationTime(pSC->m_AnimationTime)
	, m_DstRect(pSC->m_DstRect)
	, m_Flip(pSC->m_Flip)
{
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

	glm::dmat4x4 final{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	for (auto rotation : m_Rotations)
	{
		const auto angle{ ToRadians(rotation.second) };
		const glm::dmat4x4 cur
		{
			cos(angle),-sin(angle),0,rotation.first.x,
			sin(angle),cos(angle),0,rotation.first.y,
			0,0,1,0,
			0,0,0,1
		};
		final *= cur;

	}

	dae::Renderer::GetInstance().RenderTexture(*m_SourcePart.GetTexture(), m_SourcePart.SrcRect, tempDstRect, acos(final[0][0]), SDL_Point{ static_cast<int>(final[3][0]) ,static_cast<int>(final[3][1]) }, m_Flip);
}

void SpriteComponent::SetFlip(bool flip)
{
	m_Flip = flip;
}

void SpriteComponent::SetRotation(const SDL_Point& rotationPoint, float angle)
{
	m_Rotations[rotationPoint] = angle;
}

float SpriteComponent::GetRotation(const SDL_Point& rotationPoint) const
{
	return m_Rotations.at(rotationPoint);
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

