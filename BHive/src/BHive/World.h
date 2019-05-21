#pragma once

#include "BHive/Entities/EntityManager.h"

namespace BHive
{
	class BHive_API World : public EntityManager
	{

	public:
		World();

		//Override Create World in subclasses. Default includes preview
		virtual void CreateWorld() {};

		void SetActive();	
	};
}


