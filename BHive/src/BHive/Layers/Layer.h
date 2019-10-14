#pragma once

#include "Core.h"
#include "BHive/Events/Event.h"

namespace BHive
{
	class BHive_API Layer
	{
	public:
		Layer(const FString& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const FString& GetName() const { return m_DebugName; }

	protected:
		FString m_DebugName;
	};
}