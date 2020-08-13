#pragma once

#include "BHive/Object/SceneCamera.h"
#include "BHive/Renderer/Buffer.h"
#include "BHive/Renderer/VertexArray.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"
#include "BHive/Renderer/Texture.h"
#include "BHive/Renderer/Mesh.h"
#include "TypeTraits.h"

namespace BHive
{
	struct TagComponent
	{
		std::vector<std::string> Tags;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::vector<std::string>& tags)
			:Tags(tags) {}
		TagComponent(std::initializer_list<std::string> tags)
			:Tags(tags) {}
	};

	struct RenderComponent
	{
		RenderComponent() = default;
		RenderComponent(const RenderComponent&) = default;

		Ref<Model> m_Model;
	};

	struct TransformComponent
	{
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		Transform m_Transform;
	};

	struct DirectionalLightComponent
	{
		DirectionalLightComponent() = default;
		DirectionalLightComponent(const DirectionalLightComponent&) = default;

		FVector3 m_LightColor = FVector3(1.0f);
		float m_LightBrightness = 1.0f;
		FVector3 m_LightDirection = FVector3(0.5f, 1.0f, 0.0f);
	};

	struct CameraComponent 
	{
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

		SceneCamera m_Camera;
		bool m_PrimaryCamera = true;
		bool m_FixedAspectRatio = false;
		OrthographicSettings m_OrthographicSettings;
		PerspectiveSettings m_PerspectiveSettings;

	private:
		int item = 0;
	};

	class ScriptEntity;
	struct NativeScriptComponent
	{
		std::function<void(ScriptEntity*)> OnCreateFunc;
		std::function<void(ScriptEntity*)> OnDestroyFunc;
		std::function<void(ScriptEntity*, const Time&)> OnUpdateFunc;
		std::function<void()>InstantiateFunc;

		Ref<ScriptEntity> Instance = nullptr;

		template<typename T>
		void Bind()
		{
			Instance = Make_Ref<T>();

			InstantiateFunc = [&](){ Instance = Make_Ref<T>(); };

			if constexpr (TypeTraits::HasOnCreateFunction<T>())
				OnCreateFunc = [](ScriptEntity* t){ ((T*)t)->OnCreate(); };

			if constexpr (TypeTraits::HasOnDestroyFunction<T>())
				OnDestroyFunc = [](ScriptEntity* t) { ((T*)t)->OnDestroy(); };

			if constexpr (TypeTraits::HasOnUpdateFunction<T>())
				OnUpdateFunc = [](ScriptEntity* t, const Time& time) { ((T*)t)->OnUpdate(time); };
		}
	};
}