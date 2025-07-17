#pragma once

#include "Sisyphus/Core/Layer.h"

#include "Sisyphus/Events/ApplicationEvent.h"
#include "Sisyphus/Events/KeyEvent.h"
#include "Sisyphus/Events/MouseEvent.h"

namespace Sisyphus {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;
	private:
		bool m_BlockEvents = true;
	};

}