#include "hspch.h"
#include "Window.h"

#ifdef SP_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Sisyphus
{
	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
#ifdef SP_PLATFORM_WINDOWS
		return std::make_unique<WindowsWindow>(props);
#else
		SP_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}