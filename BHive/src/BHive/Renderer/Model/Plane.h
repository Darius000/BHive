#pragma once

#include "Model.h"

namespace BHive
{
	class Plane : public Model 
	{
	public:
		Plane();
		Plane(float width, float height);
	};
}