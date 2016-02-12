#include "Texture.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SDLErrorReport.h"
#include "Renderer.h"
#include "Font_TTF.h"


Texture::Texture()
{

}

Texture::~Texture()
{
	Release();
}

void Texture::Release()
{
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = nullptr;
	m_Width = 0;
	m_Height = 0;
}

void Texture::Render(Renderer& renderer, int x, int y)
{
	SDL_Rect image_rect = {x,y, m_Width, m_Height};
	RenderStretch(renderer, &image_rect);
}

void Texture::RenderStretch(Renderer& renderer, SDL_Rect* pDestRect /*= nullptr*/)
{
	if (renderer.GetRenderPtr() && m_pTexture)
		SDL_RenderCopy(renderer.GetRenderPtr(), m_pTexture, m_pClipRect, pDestRect);
}

bool Texture::CreateFromFile(Renderer& renderer, std::string filename)
{
	SDL_Surface* pSurface = IMG_Load(filename.c_str());

	if (!pSurface)
	{
		Error2MsgBox("Could not load texture from file.\n");
		return false;
	}
	else
	{
		Release();
		m_pTexture = SDL_CreateTextureFromSurface(renderer.GetRenderPtr(), pSurface);
		SDL_FreeSurface(pSurface);

		if (m_pTexture != nullptr)
		{
			m_Width = pSurface->w;
			m_Height = pSurface->h;
		}
		else
		{
			Error2MsgBox("Could not create texture loaded from file.\n");
			return false;
		}
	}
	return true;
}

bool Texture::CreateFromText(Renderer& renderer, std::string text, FontTTF& font)
{
	if (!font.GetFontPtr())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Font not loaded", nullptr);
		return false;
	}

	SDL_Surface* textSurface = TTF_RenderText_Blended(font.GetFontPtr(), text.c_str(), font.GetColor() );

	return CreateFromSurface(textSurface, renderer);
}

bool Texture::CreateFromText_Fast(Renderer& renderer, std::string text, FontTTF& font)
{
	if (!font.GetFontPtr())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Font not loaded", nullptr);
		return false;
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid( font.GetFontPtr(), text.c_str(), font.GetColor() );

	return CreateFromSurface(textSurface, renderer);
}

bool Texture::CreateFromSurface(SDL_Surface* textSurface, Renderer &renderer)
{
	Release();

	if (textSurface == nullptr)
	{
		Error2MsgBox("Tried to create texture from invalid surface.\n");
		return false;
	}

	//Create texture from surface pixels 
	m_pTexture = SDL_CreateTextureFromSurface(renderer.GetRenderPtr(), textSurface);
	if (m_pTexture == nullptr)
		Error2MsgBox("Unable to create texture from surface!\n");
	else
	{
		//Get image dimensions 
		m_Width = textSurface->w;
		m_Height = textSurface->h;
	}
	//Get rid of old surface 
	SDL_FreeSurface(textSurface);

	return m_pTexture != nullptr;
}