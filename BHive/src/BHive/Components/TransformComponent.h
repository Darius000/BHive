#pragma once

#include "Core.h"
#include "Component.h"



namespace BHive
{
	class TransformComponent;

	using ChildComponents = std::vector<std::unique_ptr<TransformComponent>>;

	class BHive_API TransformComponent : public Component 
	{
		BCLASS(TransformComponent, ComponentCategory, Component)

	private:
		TransformComponent* m_Parent;
		Transform m_Transform;

	public:

		TransformComponent();

		// Get the component's transform
		Transform GetTransform() const { return m_Transform; }

		//Get the components transform relative to its parent
		Vector3 GetRelativePosition() const;

		//Get the parent component
		TransformComponent* GetParentComponent() const { return m_Parent; }

		//Implement the ability to add child transform components
		ChildComponents children;

		//Add component as child to this
		//void AddChild(std::unique_ptr<TransformComponent> child);
		//void RemoveChild(TransformComponent* child);
		//TransformComponent* GetChildAtIndex(unsigned int index);
		//TransformComponent* GetChildWithName(String name);

	private:
		//Called when the component's transform is updated
		void OnTransformUpdated(const Transform& newTranform);
	};
}