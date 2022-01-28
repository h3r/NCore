#pragma once
#include "core/core.h"

#ifdef NC_PLATFORM_WINDOWS
extern NC::CApplication* NC::CreateApplication();
//int NC_API main(int argc, char** argv);

int main(int argc, char** argv) {

	NC::CLog::Init();

	auto app = NC::CreateApplication();
	app->Run();
	delete app;

	return 0;

}


#endif
