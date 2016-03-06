#ifndef GameApp_h__
#define GameApp_h__
#pragma once

#include "Window.h"
#include "EventHandler.h"

class GameApp : public EventHandler
{
public:
	GameApp(std::string appname);
	virtual ~GameApp();

	int Execute();

protected:

	void Cleanup();

	bool Init();

	void HandleEvents();

	virtual void AppCleanup() {}
	virtual bool AppInit() { return true; }
	virtual void AppRender(Renderer& renderer) = 0;
	virtual void AppUpdate(double dt) = 0;

	void MainLoop();

	void Render();

	bool OnExit() { m_Running = false; return true; }

	void DrawFramesPerSecond(double deltaTime);

protected:
	std::string m_AppName;
	bool	m_Running = false;
	int		m_maxFPS = 100;
	int		m_minFPS = 10;

	int		m_MissedFrames = 0;

	bool	m_ShowFPS = true;

	Window	m_Window;
};

#endif // GameApp_h__

