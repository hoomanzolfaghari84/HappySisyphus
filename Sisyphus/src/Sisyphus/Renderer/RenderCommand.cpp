#include "hspch.h"
#include "RenderCommand.h"

namespace Sisyphus {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}

