#include "hspch.h"
#include "Window.h"

#ifdef SP_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Sisyphus
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef SP_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		SP_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}