#pragma once

#include "Uniform.h"
#include "Assets/Asset.h"
#include "BHive/Managers/AssetManagers.h"
//#include "Core/Core.h"

namespace BHive
{
	
	static std::unordered_map<ShaderType, const char*> ShaderTypesToString = {{ShaderType::None,"None"}, 
	{ShaderType::VertexShader, "Vertex"}, { ShaderType::FragmentShader,"Fragment"}, {ShaderType::GeometryShader, "Geometry"}};

	class BHive_API Shader : public IAssetType
	{
	public:
		
		DEFINE_ASSET_BODY(Shader, "scripticon")

		using ShaderSource = std::unordered_map<ShaderType, std::string>;
		using ShaderIDs = std::unordered_map<ShaderType, uint32>;
		
	public:
		Shader(){}
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void Compile() = 0;

		virtual void SetBool(const BString& name, bool value) const = 0;
		virtual void SetInt(const BString& name, int value) const = 0;
		virtual void SetFloat(const BString& name, float value) const = 0;
		virtual void SetFloat2(const BString& name, float value0, float value1) const = 0;
		virtual void SetVec2(const BString& name, const FVector2& vec) const = 0;
		virtual void SetFloat3(const BString& name, float value0, float value1, float value2) const = 0;
		virtual void SetVec3(const BString& name, const FVector3& vec) const = 0;
		virtual void SetFloat4(const BString& name, float value0, float value1, float value2, float value3) const = 0;
		virtual void SetVec4(const BString& name, const FVector4& vec) const = 0;
		virtual void SetMat2(const BString& name, const glm::mat2& mat) const = 0;
		virtual void SetMat3(const BString& name, const glm::mat3& mat) const = 0;
		virtual void SetMat4(const BString& name, const glm::mat4& mat) const = 0;
		virtual uint32& GetID() = 0;

		static Ref<Shader> Create(const WinPath& filePath);
		static Ref<Shader> Create(const BName& name, const BString& vertexSrc, const BString& fragmentSrc);

		static bool IsExtensionSupported(const std::string& ext);

	protected:
		ShaderSource m_Sources;// = {{ShaderType::VertexShader, ""}, {ShaderType::FragmentShader, ""}};
		ShaderIDs m_Ids;

	private:
		static std::vector<std::string> s_SupportedExtension;
		
		friend class ShaderEditorCustomizationDetails;
		friend class Material;

		template<typename T>
		friend void Serialize(T* obj, const std::string& filepath);
	};
}
