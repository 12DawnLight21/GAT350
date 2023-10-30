#include "World01.h"
#include "World02.h"
#include "World03.h"
#include "World04.h"
#include "World05.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
	INFO_LOG("Initialize Engine...");


	//String assignment here
	string s1 = "are we equal";
	string s2 = "ARE WE EQUAL";
	
	nc::StringUtils strUtil = nc::StringUtils();
	cout << strUtil.toUpper(s1) << "\n";
	cout << strUtil.toLower(s2) << "\n";

	cout << strUtil.isEqualIgnoreCase(s1, s2) << "\n"; // 0 false, 1 true

	cout << strUtil.createUnique(s1) << "\n";
	cout << strUtil.createUnique(s1) << "\n";
	cout << strUtil.createUnique(s1) << "\n";



	//nc::MemoryTracker::Initialize();
	nc::seedRandom((unsigned int)time(nullptr));
	nc::setFilePath("assets");

	ENGINE.Initialize();

	auto world = make_unique<nc::World05>();
	world->Initialize();

	// main loop
	bool quit = false;
	while (!quit)
	{
		// update
		ENGINE.Update();
		quit = ENGINE.IsQuit();

		world->Update(ENGINE.GetTime().GetDeltaTime()); //breaks here 10/25/23

		// draw
		world->Draw(*ENGINE.GetSystem<nc::Renderer>());
	}

	world->Shutdown();
	ENGINE.Shutdown();

	return 0;
}
