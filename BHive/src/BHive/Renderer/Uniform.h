#pragma once

namespace BHive
{ 
#define SHADER_UNIFORM_TYPES(types)\
	types(Bool),	\
	types(Int)	,	  \
	types(Float)	,  \
	types(Float2),	  \
	types(Float3),	  \
	types(Float4),	  \
	types(Vec2)	,	  \
	types(Vec3)	 , \
	types(Vec4)	,	  \
	types(Color3) , \
	types(Color4) , \
	types(HDRColor3) , \
	types(HDRColor4 ), \
	types(Mat2)	,	  \
	types(Mat3)	,	  \
	types(Mat4)	,	  \
	types(Sampler)	,  \
	types(SamplerCube)


CREATE_ENUM_CLASS(ShaderUniformTypes, SHADER_UNIFORM_TYPES)

	class Uniform;

	enum class ShaderType : unsigned int
	{
		None = 0,
		FragmentShader = 0x8B30,
		VertexShader = 0x8B31,
		GeometryShader = 0x8DD9
	};

	class Uniform
	{
	public:
		Uniform() = default;
		virtual ~Uniform() = default;

		std::string m_Name = "";
		uint32 m_Location = 0;
		uint64 m_Length = 0;
		uint32 m_Size = 0;
		std::string m_DisplayName = "";

		virtual const ShaderUniformTypes GetType() const = 0;
		virtual void OnRenderGui() = 0;
	};

	template<typename T>
	class TypeUniform : public Uniform
	{
	public:
		TypeUniform():m_Value(){}
		virtual ~TypeUniform(){}

		T m_Value;

		T& Get() { return m_Value; }
		const T& Get() const { return m_Value;}
		void Set(T value)
		{ 
			m_Value = value; 
		}

		const ShaderUniformTypes GetType() const override  = 0;
		void OnRenderGui() override = 0;
	};

	class FloatUniform : public TypeUniform<float>
	{
	public:
		float min = 0.0f;
		float max = 0.0f;
		float speed = 1.0f;

		const ShaderUniformTypes GetType() const override { return ShaderUniformTypes::Float; }

		void OnRenderGui() override
		{
			ImGui::DragFloat(m_DisplayName.c_str(), &m_Value, speed, min, max);
		}
	};

	class SamplerUniform : public TypeUniform<Ref<Texture2D>>
	{
	public:
		int32 m_SamplerIndex = 1;

		const ShaderUniformTypes GetType() const override { return ShaderUniformTypes::Sampler; }

		void OnRenderGui() override
		{
			auto textureID =  m_Value ? m_Value->GetRendererID() : -1;
			ImGui::Image((void*)textureID, ImVec2(50,50), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine();
			if (ImGui::BeginCombo(m_DisplayName.c_str(), m_Value ? m_Value->GetName().c_str() : ""))
			{
				int i = 0;

				if (ImGui::Selectable("None"))
				{
					m_Value = AssetManager::Get<Texture2D>("Default");
				}

				for (auto& asset : AssetManager::GetAssetsOfType<Texture2D>())
				{
					ImGui::PushID(i++);
					std::string name = asset.second->GetName();
					if (ImGui::Selectable(name.c_str(), name == (m_Value ? m_Value->GetName() : std::string(""))))
					{
						m_Value = CastPointer<Texture2D>(asset.second);
					}
					ImGui::PopID();
				}
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			ImGui::InputInt("SamplerIndex", &m_SamplerIndex);
		}
	};

	class SamplerCubeUniform : public TypeUniform<Ref<CubeTexture>>
	{
	public:
		int32 m_SamplerIndex = 0;

		const ShaderUniformTypes GetType() const override { return ShaderUniformTypes::SamplerCube; }

		void OnRenderGui() override
		{
			auto textureID = m_Value ? m_Value->GetRendererID() : -1;
			ImGui::Image((void*)textureID, ImVec2(50, 50), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine();
			if (ImGui::BeginCombo(m_DisplayName.c_str(), m_Value ? m_Value->GetName().c_str() : ""))
			{
				int i = 0;

				if (ImGui::Selectable("None"))
				{
					m_Value = AssetManager::Get<CubeTexture>("Default");
				}

				for (auto& asset : AssetManager::GetAssetsOfType<CubeTexture>())
				{
					ImGui::PushID(i++);
					std::string name = asset.second->GetName();
					if (ImGui::Selectable(name.c_str(), name == (m_Value ? m_Value->GetName() : std::string(""))))
					{
						m_Value = CastPointer<CubeTexture>(asset.second);
					}
					ImGui::PopID();
				}
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			ImGui::InputInt("SamplerIndex", &m_SamplerIndex);
		}
	};

	class BoolUniform : public TypeUniform<bool> 
	{
	public:

		const ShaderUniformTypes GetType() const override { return ShaderUniformTypes::Bool; }

		void OnRenderGui() override
		{
			ImGui::Checkbox(m_DisplayName.c_str(), &m_Value);
		}
	};

	class IntUniform : public TypeUniform<int32>
	{
	public:
		int min = 0;
		int max = 0;
		float speed = 1.0f;

		const ShaderUniformTypes GetType() const override { return ShaderUniformTypes::Int; }

		void OnRenderGui() override
		{
			ImGui::DragInt(m_DisplayName.c_str(), &m_Value, speed, min, max);
		}
	};

	class Vec3Uniform : public TypeUniform<Vector3<float>>
	{
	public:
		float min = 0.0f;
		float max = 0.0f;
		float speed = 1.0f;

		const ShaderUniformTypes GetType() const override{ return ShaderUniformTypes::Vec3; }

		void OnRenderGui() override
		{
			ImGui::ColorEdit3(m_DisplayName.c_str(), *m_Value, 0);
		}
	};

	class Vec4Uniform : public TypeUniform<Vector4<float>>
	{
		public:

		const ShaderUniformTypes GetType() const override { return ShaderUniformTypes::Vec4; }

		void OnRenderGui() override
		{
			ImGui::ColorEdit4(m_DisplayName.c_str(), *m_Value, 0);
		}
	};

	class Vec2Uniform : public TypeUniform<Vector2<float>>
	{
	public:
		float min = 0.0f;
		float max = 0.0f;
		float speed = 1.0f;

		const ShaderUniformTypes GetType() const override { return ShaderUniformTypes::Vec2; }

		void OnRenderGui() override
		{
			ImGui::DragFloat2(m_DisplayName.c_str(), *m_Value, 0);
		}
	};
};