#pragma once

#include "Component.h"

namespace BHive
{
	class TransformComponent;

	using ChildComponents = std::vector<TransformComponent*>;

	class BHive_API TransformComponent : public Component 
	{
		BCLASS(TransformComponent, ComponentCategory, Component)

	public:

		TransformComponent();
		virtual ~TransformComponent() {}

	public:
		Transform& GetTransform() { return m_Transform;}
		Transform GetRelativeTransform();
		Transform GetAbsoluteTransform();
		void SetRelativeTransform(const Transform& transform);
		TransformComponent* GetParent() { return m_Parent; }
		void AddChild(TransformComponent& child);
		void RemoveChild(TransformComponent& child);
		void AttachToComponent(TransformComponent& parent);
		void AttachToEntity(Actor& entity);
		
	protected:
		virtual void OnTransformUpdated(const Transform& transform);;
		void UpdateTransformation(const Transform& transform);
		void UpdateRelativeTransform();

	public:
		ChildComponents children;
	private:
		TransformComponent* m_Parent;
		Transform m_Transform;
		Transform m_RelativeTransform;
	};
}