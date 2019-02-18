#include <BHive.h>

class ExampleLayer : public BHive::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//BH_INFO("ExampleLayer::Update");
		if (BHive::Input::IsKeyPressed(BH_KEY_TAB))
			BH_INFO("Tab key is pressed(POLL");
	}

	void OnEvent(BHive::Event& event) override
	{
		if (event.GetEventType() == BHive::EventType::KeyPressed)
		
		{
			BHive::KeyPressedEvent& e = (BHive::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BH_KEY_TAB)
				BH_INFO("Tab key is pressed(Event)");
			BH_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public BHive::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new BHive::RenderLayer());
		PushOverlay(new BHive::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

BHive::Application* BHive::CreateApplication()
{
	return new Sandbox();
}