#pragma  once

#include "Components/TransformComponent.h"
#include "Object.h"
#include <glm/glm.hpp>

namespace BHive
{
	const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);


	class BHive_API GameObject : public Object
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Start();
		virtual void Update(float deltaTime);
		void SetRootComponent(TransformComponent* component);
		TransformComponent* GetRootComponent();
		bool IsDestroyed();
		virtual void OnDestroyed() override;

		template<typename T>
		T* AddComponent(std::string name);

	private:

		std::vector<ObjectComponent*> components;

		TransformComponent* rootComponent;

		bool destroyed;
	};

	template<class T>
	T* GameObject::AddComponent(std::string name)
	{
		T* component = new T();

		component->SetParent(this);

		components.push_back(component);

		return component;
	}
}
