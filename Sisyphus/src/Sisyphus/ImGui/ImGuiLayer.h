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
		~ImGuiLayer() override = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;


		// Helper to display a little (?) mark which shows a tooltip when hovered.
		// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
		static void HelpMarker(const char* desc);

	private:
		bool m_BlockEvents = true;
	};

}