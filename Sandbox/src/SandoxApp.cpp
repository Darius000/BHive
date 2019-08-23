#include <BHive.h>

#include "imgui/imgui.h"
#include "BHive/Entities/Entity.h"
#include "BHive/Components/Primitives/Triangle.h"
#include "World.h"
#include "Components/BillboardComponent.h"


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

class WorldOne : public BHive::World
{

public:
	virtual void CreateWorld() override
	{
		BH_INFO("Created World 1");
		/*BHive::Camera* MainCam = AddEntity<BHive::Camera>();
		BHive::GameObject* Box = AddEntity<BHive::GameObject>();
		Box->AddComponent<BHive::BillboardComponent>();*/

		BHive::Entity* E0 = AddEntity<BHive::Entity>();
		E0->GetTransform().SetPosition(0.0f, 50.0f, 0.0f);

		BHive::Triangle* T0 = E0->AddComponent<BHive::Triangle>();
		T0->SetPoints(BHive::Vector3(-0.25f, -0.25f, -0.0f), BHive::Vector3(0.25f, -0.25f, 0.0f), BHive::Vector3(0.0f, 0.1f, 0.0f));

		//BHive::Matrix Mat;
		//BH_TRACE("Matrix:{0}", Mat.ToString());

		//BHive::Rotator rot;
		//BHive::Rotator rot2(500.0f, 360.0f, 10.0f);

		//rot += rot2;

		////270, 0, 350
		//BH_TRACE("Rotator:{0}", rot.ToString());
		//BH_TRACE("Rotator:{0}", rot2.ToString());

		//BH_TRACE("{0}", sizeof(int8));
		//BH_TRACE("{0}", sizeof(int16));
		//BH_TRACE("{0}", sizeof(int32));
		//BH_TRACE("{0}", sizeof(int64));

		//BH_TRACE("{0}", sizeof(uint8));
		//BH_TRACE("{0}", sizeof(uint16));
		//BH_TRACE("{0}", sizeof(uint32));
		//BH_TRACE("{0}", sizeof(uint64));
	}
};

class Sandbox : public BHive::Application
{
public:
	Sandbox()
	{
		WorldOne* w = new WorldOne();
		w->SetActive();
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