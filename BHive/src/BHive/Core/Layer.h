#pragma once

namespace BHive
{
	class BHive_API Layer
	{
	public:
		Layer(const BString& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(const Time& time) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const BString& GetName() const { return m_DebugName; }

	protected:
		BString m_DebugName;
	};
}