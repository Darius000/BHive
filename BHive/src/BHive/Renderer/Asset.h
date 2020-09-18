#pragma once


namespace BHive
{
	class Texture2D;

	enum class AssetType : uint8
	{
		None, Texture, Shader, Mesh
	};

	class Asset
	{
	public:
		Asset() = default;
		Asset(const std::string& name);
		virtual ~Asset() = default;

		std::string GetName() const;

		virtual AssetType GetAssetType() const { return AssetType::None; }
		
		void CreateThumbnail(){};
		Texture2D* GetThumbnail() const;
		uint32 GetThumnailID() const;

		BName m_Name;
		Texture2D* m_Thumbnail;
	};
}