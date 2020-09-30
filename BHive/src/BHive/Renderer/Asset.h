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

		std::string& GetName();

		virtual std::string GetAssetType() const = 0;
		
		void CreateThumbnail(){};
		virtual const std::string GetThumbnailName() const = 0;

		BName m_Name;
	};
}