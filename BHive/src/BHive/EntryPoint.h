#pragma once


#ifdef BH_PLATFORM_WINDOWS

extern BHive::Application* BHive::CreateApplication();

int main(int argc, char** argv)
{
	//Initialize the logger for spdlog
	BHive::Log::Init();
	BH_CORE_WARN("Initialized Core Logger!");

	//printf("BHive Engine Started!");
	auto app = BHive::CreateApplication();
	app->Run();
	delete app;
}

#endif