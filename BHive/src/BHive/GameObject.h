#pragma  once


#include "ECS.h"
#include "Components/TransformComponent.h"

namespace BHive
{
	const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);


	class BHive_API GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Start() override;
		virtual void Update(float deltaTime) override;
		void SetRootComponent(TransformComponent* component);
		TransformComponent* GetRootComponent();
	private:

		TransformComponent* rootComponent;
	};
}
