#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <imgui.h>
#include <SDL_ttf.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl2.h>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(),
	                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}



void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect, bool flipped) const
{
	if(flipped)
	{
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect,0,nullptr,SDL_FLIP_HORIZONTAL);
	}
	else
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect, const double& angle, bool flipped) const
{
	if (flipped)
	{
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect, angle, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect, const double& angle, const SDL_Point& center, bool flipped) const
{
	if (flipped)
	{
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect, angle, &center, SDL_FLIP_HORIZONTAL);
	}
	else 
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect, angle, &center, SDL_FLIP_NONE);
}

void dae::Renderer::RenderRectangle(const SDL_Rect& rect, const SDL_Color& color, bool fill) const
{
	SDL_SetRenderDrawColor(GetSDLRenderer(), color.r, color.g, color.b, color.a);
	if(fill)
	{
		SDL_RenderFillRect(GetSDLRenderer(), &rect);
	}
	else 
	{
		SDL_RenderDrawRect(GetSDLRenderer(), &rect);
	}
}

void dae::Renderer::RenderText(const std::string& text, const SDL_Rect& dstRect, const std::string& font, int fontSize, const SDL_Color& color) const
{
	TTF_Font* Sans = TTF_OpenFont(("../Data/" + font).c_str(), fontSize);
	
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(Sans, text.c_str(), color);
	
	SDL_Texture* Message = SDL_CreateTextureFromSurface(GetSDLRenderer(), surfaceMessage);
	
	SDL_RenderCopy(GetSDLRenderer(), Message, NULL, &dstRect);
	
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	TTF_CloseFont(Sans);
}

void dae::Renderer::RenderText(
	const std::string& text,
	const SDL_Point& leftTop,
	std::pair< HorAllignment, VerAllignment> textAllignment,
	const std::string& font,
	int fontSize,
	const SDL_Color& color
	) const
{
	TTF_Font* Sans = TTF_OpenFont(("../Data/" + font).c_str(), fontSize);

	SDL_Rect Message_rect;
	Message_rect.x = leftTop.x;
	Message_rect.y = leftTop.y;
	TTF_SizeText(Sans, text.c_str(), &Message_rect.w, &Message_rect.h);

	// -- Text Allignment -- //
	if(textAllignment.first == HorAllignment::Mid)
	{
		Message_rect.x -= Message_rect.w / 2;
	}
	else if(textAllignment.first == HorAllignment::Right)
	{
		Message_rect.x -= Message_rect.w;
	}
	if(textAllignment.second == VerAllignment::Mid)
	{
		Message_rect.y -= Message_rect.w / 2;
	}
	else if(textAllignment.second == VerAllignment::Bottom)
	{
		Message_rect.y -= Message_rect.w;
	}


	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Sans, text.c_str(), color);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(GetSDLRenderer(), surfaceMessage);

	SDL_RenderCopy(GetSDLRenderer(), Message, NULL, &Message_rect);
	
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	TTF_CloseFont(Sans);
}

void dae::Renderer::RenderText(
	const std::string& text,
	const int top,
	HorAllignment windowAllignment,
	std::pair< HorAllignment, VerAllignment> textAllignment,
	const std::string& font,
	int fontSize,
	const SDL_Color& color
) const
{
	SDL_Point Message_rect;
	SDL_Point windowDim{};
	SDL_GetWindowSize(m_Window, &windowDim.x, &windowDim.y);
	Message_rect.y = top;

	// -- Window Allignment -- //
	switch (windowAllignment)
	{
	case HorAllignment::Left:
		Message_rect.x = 0;
		break;
	case HorAllignment::Mid:
		Message_rect.x = windowDim.x / 2;
		break;
	case HorAllignment::Right:
		Message_rect.x = windowDim.x;
		break;
	}
	RenderText(text, Message_rect, textAllignment, font, fontSize, color);
}

void dae::Renderer::RenderText(
	const std::string& text,
	std::pair< HorAllignment, VerAllignment> windowAllignment,
	std::pair< HorAllignment, VerAllignment> textAllignment,
	const std::string& font,
	int fontSize,
	const SDL_Color& color
) const
{
	SDL_Point Message_rect;
	SDL_Point windowDim{};

	SDL_GetWindowSize(m_Window, &windowDim.x, &windowDim.y);

	// -- Window Allignment -- //
	switch (windowAllignment.first)
	{
	case HorAllignment::Left:
		Message_rect.x = 0;
		break;
	case HorAllignment::Mid:
		Message_rect.x = windowDim.x / 2;
		break;
	case HorAllignment::Right:
		Message_rect.x = windowDim.x;
		break;
	}
	switch (windowAllignment.second)
	{
	case VerAllignment::Top:
		Message_rect.y = 0;
		break;
	case VerAllignment::Mid:
		Message_rect.y = windowDim.y / 2;
		break;
	case VerAllignment::Bottom:
		Message_rect.y = windowDim.y;
		break;
	}
	RenderText(text, Message_rect, textAllignment, font, fontSize, color);
}

void dae::Renderer::RenderPolygon(const std::vector<SDL_Point>& points, const glm::vec2& size, const SDL_Color& color, bool AddPoints, const SDL_Color& PointsColor) const
{
	if (points.size() == 0)
		return;

	SDL_RenderSetScale(GetSDLRenderer(), size.x, size.y);

	//DrawPoints
	if (AddPoints)
	{
		SDL_Point* pointArr{ new SDL_Point[points.size()]{} };
		for (size_t i = 0; i < points.size(); ++i)
		{
			const auto& point{ points[i] };
			pointArr[i] = point;
		}
		SDL_SetRenderDrawColor(GetSDLRenderer(), PointsColor.r, PointsColor.g, PointsColor.b, PointsColor.a);
		SDL_RenderDrawPoints(GetSDLRenderer(), pointArr, static_cast<int>(points.size()));
		delete[] pointArr;
		pointArr = nullptr;
	}

	SDL_SetRenderDrawColor(GetSDLRenderer(), color.r, color.g, color.b, color.a);
	if (points.size() == 1)
	{
		SDL_RenderDrawLine(GetSDLRenderer(),0,0,points.front().x,points.front().y);
	}
	else if (points.size() == 2)
	{
		SDL_RenderDrawLine(GetSDLRenderer(), points[0].x, points[0].y, points[1].x, points[1].y);
	}
	else
	{
		SDL_FPoint* fPointArr{ new SDL_FPoint[points.size()]{} };
		for (size_t i = 0; i < points.size(); ++i)
		{
			const auto& point{ points[i] };
			fPointArr[i] = SDL_FPoint(static_cast<float>(point.x), static_cast<float>(point.y));
		}
		SDL_RenderDrawLinesF(GetSDLRenderer(), fPointArr, static_cast<int>(points.size()));
		delete[] fPointArr;
		fPointArr = nullptr;
	}
	SDL_RenderSetScale(GetSDLRenderer(), 1, 1);
}
