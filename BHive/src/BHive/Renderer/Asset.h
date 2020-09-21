#pragma once


namespace BHive
{
	class Texture2D;

	class Asset
	{
	public:
		Asset() = default;
		Asset(const std::string& name);
		virtual ~Asset() = default;

		std::string GetName() const;

		virtual std::string GetAssetType() const = 0;
		
		void CreateThumbnail(){};
		Texture2D* GetThumbnail() const;
		uint32 GetThumnailID() const;

		BName m_Name;
		Texture2D* m_Thumbnail;
	};
}