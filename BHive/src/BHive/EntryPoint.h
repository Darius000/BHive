#pragma once


#ifdef BH_PLATFORM_WINDOWS

extern BHive::Application* BHive::CreateApplication();

int main(int argc, char** argv)
{
	//printf("BHive Engine Started!");
	auto app = BHive::CreateApplication();
	app->Run();
	delete app;
}

#endif