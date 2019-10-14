#pragma once

#include "Core.h"
#include "Component.h"



namespace BHive
{
	class TransformComponent;

	using ChildComponents = std::vector<TransformComponent*>;

	class BHive_API TransformComponent : public Component 
	{
		BCLASS(TransformComponent, ComponentCategory, Component)

	private:
		TransformComponent* m_Parent;
		Transform m_Transform;
		Vector3 m_RelativeLocation;
	public:

		TransformComponent();
		virtual ~TransformComponent() {}

		// Get the component's transform
		Transform& GetTransform() { return m_Transform;}

		//Get the components transforms relative to its parent
		Vector3 GetRelativeLocation();
		Vector3 GetAbsoluteLocation();
		void SetRelativeLocation(Vector3& location);

		//Get the parent component
		TransformComponent* GetParent() { return m_Parent; }

		//Implement the ability to add child transform components
		ChildComponents children;

		//Add component as child to this
		void AddChild(TransformComponent& child);
		void RemoveChild(TransformComponent& child);
		void AttachToComponent(TransformComponent& parent);
		void AttachToEntity(Entity& entity);
		
	protected:
		virtual void OnTransformUpdated(const Transform& transform);
	private:
		void UpdateRelativeLocation();
	};
}