#pragma once

namespace BHive
{

	struct TransformComponent
	{
		TransformComponent()
		{
			
		}

		void OnImGuiRender(const std::string& ID);

		Transform m_Transform;
	};
}