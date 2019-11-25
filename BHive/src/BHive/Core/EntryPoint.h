#pragma once


#ifdef BH_PLATFORM_WINDOWS

extern BHive::Application* BHive::CreateApplication();

int main(int argc, char** argv)
{
	//Initialize the logger for spdlog
	BHive::Log::Init();
	

	BH_PROFILE_BEGIN_SESSION("Startup", "BHive_StartUp.json");
	auto app = BHive::CreateApplication();
	BH_PROFILE_END_SESSION();

	BH_PROFILE_BEGIN_SESSION("Runtime", "BHive_Runtime.json");
	app->Run();
	BH_PROFILE_END_SESSION();

	BH_PROFILE_BEGIN_SESSION("Shutdown", "BHive_Shutdown.json");
	delete app;
	BH_PROFILE_END_SESSION();
}

#endif