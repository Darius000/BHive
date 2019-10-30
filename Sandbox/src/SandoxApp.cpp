#include <BHive.h>
#include "SandBox2D.h"
#include "BHive/Core/EntryPoint.h"


class Sandbox : public BHive::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandBox2D());
	}
	~Sandbox()
	{

	}
};

BHive::Application* BHive::CreateApplication()
{
	return new Sandbox();
}