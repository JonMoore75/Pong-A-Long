#ifndef Font_TTF_h__
#define Font_TTF_h__
#pragma once

#include <SDL_ttf.h>

class FontTTF
{
public:
	FontTTF(const char* file = nullptr, int ptsize = 0, SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF });
	~FontTTF();

	bool LoadFont(const char* file, int ptsize, SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF });

	void Release();

	void ChangeSize(int ptsize) {m_ptsize = ptsize;}
	void ChangeColour(SDL_Color textColour) { m_textColour = textColour; }

	TTF_Font* GetFontPtr() { return m_pFont;  }
	SDL_Color& GetColor() { return m_textColour;  }
	
private:
	TTF_Font* m_pFont = nullptr;
	int m_ptsize = 0;
	SDL_Color m_textColour = { 0x00, 0x00, 0x00, 0x00 };
};

#endif // Font_TTF_h__

