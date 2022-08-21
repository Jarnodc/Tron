#include "MiniginPCH.h"
#include "Clip.h"

Clip::Clip(const std::string& path, int loops, int volume)
	:m_Path{ path }
	,m_Volume{ volume }
	,m_Loops{ loops }
{
}

bool Clip::operator==(const Clip& c) const
{
	return c.m_Loops == m_Loops && c.m_Volume == m_Volume && c.m_Path == m_Path;
}
