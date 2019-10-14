#pragma  once


#include "BHive/Object/Object.h"
#include "BHive/Components/Component.h"
#include "BHive/Components/TransformComponent.h"

namespace BHive
{
	const glm::vec3 WorldUp = glm::vec3(0.0f, 0.0f, 1.0f);//Move to another file

	using ComponentID = std::size_t;

	inline ComponentID GetComponentID()
	{
		static ComponentID lastID = 0;
		return lastID++;
	}

	template <typename T> inline ComponentID GetComponentTypeID() noexcept
	{
		static ComponentID typeID = GetComponentID();
		return typeID;
	}

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
		//void AttachComponentToRoot(TransformComponent& component);
		void AttachToEntity(Entity& entity);
		void AttachToComponent(TransformComponent& component);

		TransformComponent* GetRootComponent();

		//returns the root components transform
		Transform& GetTransform() { return m_RootComponent->GetTransform(); }

		//virtual void OnTransformUpdated(const Transform& newTranform);
	private:
		std::vector<std::unique_ptr<Component>> components;

		ComponentArray componentArray;
		ComponentBitSet componentBitSet;

	public:
		template <typename T> bool HasComponent() const {
			return componentBitSet[GetComponentID<T>()];
		}

		template <typename T, typename... TArgs>
		T* AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			//c->SetOwner(*this);
			std::unique_ptr<Component> uPtr{ c };
			components.emplace_back(std::move(uPtr));

			componentArray[GetComponentTypeID<T>()] = c;
			componentBitSet[GetComponentTypeID<T>()] = true;

			c->ComponentInit();

			//Add to root if it exists
			if (!m_RootComponent)
				SetRootComponent(*c);
			else
				c->AttachToEntity(*this);

			return c;
		}

		template <typename T> T* GetComponent() const {
			auto ptr(componentArray[GetComponentTypeID<T>()]);
			return static_cast<T*>(ptr);
		}

		bool RemoveComponent(Component& component);
		void AddComponent(Component& component);

	private:

		TransformComponent* m_RootComponent;
	};
}



