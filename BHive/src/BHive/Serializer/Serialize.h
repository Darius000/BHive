#pragma once
#include "Core/Core.h"

namespace BHive
{
	template<typename T>
	void Serialize(T* obj, const std::string& filepath);

	template<>
	void Serialize(Shader* obj, const std::string& filepath)
	{
		std::ofstream os;
		os.open(filepath, std::ios::out | std::ios::trunc);
		
		for (auto& source : obj->m_Sources)
		{
			std::string type = (std::string("#type ") + ShaderTypesToString[source.first]);
			os << type << "\n";
			for (auto& str : GetLinesFromString(source.second, "\r\n"))
			{
				os << str << "\n";
			}
		}
		os.close();
	}
}