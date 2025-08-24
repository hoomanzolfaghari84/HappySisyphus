#include "hspch.h"
#include "RenderCommand.h"

namespace Sisyphus {

	std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}

