#include <BHive.h>


class Sandbox : public BHive::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

BHive::Application* BHive::CreateApplication()
{
	return new Sandbox();
}