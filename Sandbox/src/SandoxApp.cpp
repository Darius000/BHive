#include <BHive.h>

#include "imgui/imgui.h"

class ExampleLayer : public BHive::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
		
	}

	void OnAttach() override
	{
	}

	void OnUpdate() override
	{
		//BH_INFO("ExampleLayer::Update");
		if (BHive::Input::IsKeyPressed(BH_KEY_TAB))
			BH_INFO("Tab key is pressed(POLL");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Example");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(BHive::Event& event) override
	{
		if (event.GetEventType() == BHive::EventType::KeyPressed)
		
		{
			BHive::KeyPressedEvent& e = (BHive::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BH_KEY_TAB)
				BH_INFO("Tab key is pressed(Event)");
			BH_TRACE("{0}", (char)e.GetKeyCode());
			//BH_TRACE("{0}", event.ToString());
		}
	}
};

class Sandbox : public BHive::Application
{
public:
	Sandbox()
	{
		PushLayer(new BHive::RenderLayer());
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

BHive::Application* BHive::CreateApplication()
{
	return new Sandbox();
}