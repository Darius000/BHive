#pragma  once


#include "BHive/Object/Object.h"
#include "BHive/Components/Component.h"
#include "BHive/Components/TransformComponent.h"

namespace BHive
{
	const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);//Move to another file

	using ComponentID = std::size_t;

	inline ComponentID GetComponentID();

	template <typename T> 
	inline ComponentID GetComponentTypeID() noexcept;

	constexpr std::size_t maxComponents = 32;

	using ComponentBitSet = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;

	class BHive_API Entity : public Object
	{
		BCLASS(Entity, EntityCategory, Object)

	public:
		Entity();
		virtual ~Entity();

		virtual void Start();
		virtual void Update(float deltaTime);
		virtual void OnDestroyed() override;

		void SetRootComponent(TransformComponent& component);
		TransformComponent* GetRootComponent();
		Transform GetTransform() const { return m_RootComponent->GetTransform(); }

	private:
		std::vector<std::unique_ptr<Component>> components;

		ComponentArray componentArray;
		ComponentBitSet componentBitSet;

	public:
		template <typename T> 
		bool HasComponent() const;

		template <typename T, typename... TArgs>
		T* AddComponent(TArgs&&... mArgs);

		template <typename T>
		T* GetComponent() const;

	private:

		TransformComponent* m_RootComponent;
	};
}

#include "Entity.inl"