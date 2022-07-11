#include "MiniginPCH.h"
#include "HorizontalSpriteList.h"


HorizontalSpriteList::HorizontalSpriteList(dae::GameObject* pGO, SpriteComponent* spriteTemplate, int beginAmount, Allignment allignment)
	:SpriteList(pGO, spriteTemplate)
	,m_Allignment(allignment)
{
	AddItem(beginAmount);
}
void HorizontalSpriteList::AddItem(int amount) const
{
	assert(m_pSpriteTemplate);
	const auto dstRect{ m_pSpriteTemplate->GetDstRect() };
	
	for (size_t i = 0; i < amount; ++i)
	{
		const auto pGO = std::make_shared<dae::GameObject>();
		SpriteComponent* pSC{ new SpriteComponent(pGO.get(),m_pSpriteTemplate) };
		pGO->AddComponent(pSC);

		const size_t childCount = GetGameObject()->GetChildCount();
		GetGameObject()->AddChild(pGO,true);

		switch (m_Allignment)
		{
		case Allignment::Left:
			pGO->MovePosition((dstRect.x + dstRect.w) * static_cast<float>(childCount) - dstRect.x, static_cast<float>(dstRect.y));
			break;
		case Allignment::Right:
			pGO->MovePosition((dstRect.x + dstRect.w) * -static_cast<float>(childCount) + dstRect.x, static_cast<float>(dstRect.y));
			break;
		default:;
		}

	}

}

void HorizontalSpriteList::AddItem(SpriteComponent* item) const
{
	assert(item);
	const auto dstRect{ item->GetDstRect() };


	const auto pGO = std::make_shared<dae::GameObject>();
	SpriteComponent* pSC{ new SpriteComponent(pGO.get(),item) };
	pGO->AddComponent(pSC);

	const size_t childCount = GetGameObject()->GetChildCount();
	GetGameObject()->AddChild(pGO,true);

	switch (m_Allignment)
	{
	case Allignment::Left:
		pGO->MovePosition((dstRect.x + dstRect.w) * static_cast<float>(childCount) - dstRect.x, static_cast<float>(dstRect.y));
		std::cout << (dstRect.x + dstRect.w) * static_cast<float>(childCount) - dstRect.x << std::endl;
		break;
	case Allignment::Right:
		pGO->MovePosition((dstRect.x + dstRect.w) * -static_cast<float>(childCount) + dstRect.x, static_cast<float>(dstRect.y));
		break;
	default:;
	}
}
