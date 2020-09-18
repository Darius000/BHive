#pragma once

namespace BHive
{ 
	class DetailsBuilder
	{
	public:
		DetailsBuilder() = default;
		DetailsBuilder(const DetailsBuilder&) = default;

		Entity GetEntityBeingEdited(){ return m_Entity; }
		void SetEntity(Entity& entity);

		void Label(const char* label);

		//Creates a String Property Editor
		void StringProperty(const char* label, std::string& st);

		//Creates a Vector3 Property Editor
		bool Vector3Property(const char* label, FVector3& v);
		bool Color3Property(const char* label, FVector3& v);

		//Creates a Rotator Property Editor
		bool RotatorProperty(const char* label, Rotator& r);

		//Creates a Transform Property Editor
		void TransformProperty(const char* label, Transform& t);

		//Creates a float property Editor
		bool FloatProperty(const char* label, float& f);

		//Creates a bool property Editor
		bool  BoolProperty(const char* label, bool& b);

		//template<typename Enum>
		bool EnumProperty(const char* label, Projection& e);

		template<typename T>
		void AssetProperty(const char* label, Ref<T>& a);

		void MeshProperty(const char* label, Ref<Model>& m);

		Entity m_Entity;
	};

	template<typename T>
	void DetailsBuilder::AssetProperty(const char* label, Ref<T>& a)
	{
		if (ImGui::BeginCombo(label, a.get() ? a->GetName().c_str() : ""))
		{
			int i = 0;
			for (auto& asset : AssetManager::GetAssets<T>())
			{
				ImGui::PushID(i++);
				std::string name = asset.second->GetName();
				if (ImGui::Selectable(name.c_str(), name == (a.get() ? a->GetName() : std::string(""))))
				{
					a = asset.second;
				}
				ImGui::PopID();
			}
			ImGui::EndCombo();
		}
	};

	
	class DetailsCustomization
	{
	public:
		DetailsCustomization() = default;
		DetailsCustomization(const DetailsCustomization&) = default;
		virtual ~DetailsCustomization() = default;

		virtual void CreateCustomizedDetails(DetailsBuilder& detailsBuilder){};
	};

	template<typename T, typename... Args>
	inline Ref<T> MakeInstance(Args&&... args)
	{
		return Make_Ref<T>(std::forward<Args>(args)...);
	}

	class ClassPropertyRegistry
	{
	public:
		ClassPropertyRegistry() = default;

		static void RegisterClassDetails(const char* classname, Ref<DetailsCustomization> detailsCustomization);
		static Ref<DetailsCustomization> GetDetailsCustomizationInstance(const char* className);
		static std::unordered_map<const char*, Ref<DetailsCustomization>> s_DetailsRegistry;
	};
}