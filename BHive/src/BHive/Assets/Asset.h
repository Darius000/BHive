#pragma once

#include "BHive/Core/Core.h"


namespace BHive
{

	#define CLASSTYPE(className) #className
	#define DEFINE_ASSET_BODY(type, thumbnailTextureName)\
	public:\
		std::string& SetName(const std::string& name) override { m_Name = name; return m_Name; };\
		const std::string& GetName() const override { return m_Name; }\
		std::string GetAssetTypeName() const override { return #type;}\
		std::string GetThumbnailName() const override { return thumbnailTextureName;}\
	protected:\
			std::string m_Name;\
	public:
	

	//Interface for asset types

	class IAssetType
	{
	public:
		virtual std::string& SetName(const std::string& name)  = 0;
		virtual const std::string& GetName() const = 0;
		virtual std::string GetAssetTypeName() const = 0;
		virtual void CreateThumbnail(){};
		virtual std::string GetThumbnailName() const = 0;
	};
}