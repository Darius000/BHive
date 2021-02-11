#pragma once

#include "BHive/Object/SceneCamera.h"
#include "BHive/Renderer/Buffer.h"
#include "BHive/Renderer/VertexArray.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"
#include "BHive/Renderer/Texture.h"
#include "BHive/Renderer/Model/Mesh.h"
#include "TypeTraits.h"

namespace BHive
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {}
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

		LinearColor3 m_LightColor = LinearColor3(1.0f);
		float m_LightBrightness = 1.0f;
	};

	struct PointLightComponent
	{
		PointLightComponent() = default;
		PointLightComponent(const PointLightComponent&) = default;

		LinearColor3 m_Color = LinearColor3(1.0f);
		float m_Constant  =1.0f;
		float m_Linear = 0.09f;
		float m_Quadratic = 0.032f;
		float m_Brightness = 1.0f;
	};

	struct SpotLightComponent
	{
		SpotLightComponent() = default;
		SpotLightComponent(const SpotLightComponent&)  = default;

		LinearColor3 m_Color = LinearColor3(1.0);
		float m_Cutoff = 12.5f;
		float m_OuterCutoff = 17.5;
		float m_Constant = 1.0f;
		float m_Linear = 0.09f;
		float m_Quadratic = 0.032f;
		float m_Brightness = 1.0f;
	};

	struct CameraComponent 
	{
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

		SceneCamera m_Camera;
		bool m_PrimaryCamera = true;
		bool m_FixedAspectRatio = false;
	};

	class CPPScript;
	struct NativeScriptComponent
	{
		NativeScriptComponent() = default;
		NativeScriptComponent(const NativeScriptComponent&)  = default;

		std::function<void(CPPScript*)> OnCreateFunc;
		std::function<void(CPPScript*)> OnDestroyFunc;
		std::function<void(CPPScript*, const Time&)> OnUpdateFunc;
		std::function<void()>InstantiateFunc;

		Ref<CPPScript> Instance = nullptr;

		template<typename T>
		void Bind()
		{
			Instance = Make_Ref<T>();

			InstantiateFunc = [&](){ Instance = Make_Ref<T>(); };

			if constexpr (TypeTraits::HasOnCreateFunction<T>())
				OnCreateFunc = [](CPPScript* t){ ((T*)t)->OnCreate(); };

			if constexpr (TypeTraits::HasOnDestroyFunction<T>())
				OnDestroyFunc = [](CPPScript* t) { ((T*)t)->OnDestroy(); };

			if constexpr (TypeTraits::HasOnUpdateFunction<T>())
				OnUpdateFunc = [](CPPScript* t, const Time& time) { ((T*)t)->OnUpdate(time); };
		}
	};
}