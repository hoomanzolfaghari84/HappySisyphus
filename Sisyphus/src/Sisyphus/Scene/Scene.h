#pragma once

#include "Sisyphus/Core/Timestep.h"
#include "Sisyphus/Core/UUID.h"
#include "Sisyphus/Renderer/EditorCamera.h"

#include "entt.hpp"

namespace Sisyphus {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		bool m_IsRunning = false;
		bool m_IsPaused = false;
		int m_StepFrames = 0;

		std::unordered_map<UUID, entt::entity> m_EntityMap;

		friend class Entity;
		/*friend class SceneSerializer;
		friend class SceneHierarchyPanel;*/
	};

}

