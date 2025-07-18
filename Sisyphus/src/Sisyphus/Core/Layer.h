#pragma once

#include "Sisyphus/Core/Base.h"
#include "Sisyphus/Core/Timestep.h"
#include "Sisyphus/Events/Event.h"

namespace Sisyphus {

	class SISYPHUS_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}