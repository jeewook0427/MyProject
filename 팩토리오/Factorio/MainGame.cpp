#include "MainGame.h"
#include "macroFunction.h"
#include "Image.h"
#include "MapManager.h"
#include "Coal.h"
#include "pch.h"
#include "InGameScene.h"
#include "TitleScene.h"
#include "LoadingScene.h"

FPOINT g_pos;
bool gameOver;
float cameraScale;
bool isLaunch;
float playTime;
FPOINT p_pos;

HRESULT MainGame::Init()
{
	
	srand(time(NULL));
	gameOver = false;
	isLaunch = false;

	hdc = GetDC(g_hWnd);
	cameraScale = 1.3;
	// backBuffer
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimeManager::GetSingleton()->Init();
	SoundManager::GetSingleton()->Init();
	

	// 이미지 리소스 초기화
	// Terrain
	ImageManager::GetSingleton()->AddImage("grass", "Image/terrain/grass/grass.bmp", 0, 0, 256, 512, 8, 16, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("titleBg", "Image/UI/background-image.bmp", WINSIZE_X, WINSIZE_Y);
	ImageManager::GetSingleton()->AddImage("loadingLogo", "Image/UI/background-image-logo.bmp", 800, 132, true, RGB(0,0,0));
	ImageManager::GetSingleton()->AddImage("menu", "Image/UI/main-menu.bmp", 500, WINSIZE_Y / 2);
	ImageManager::GetSingleton()->AddImage("playBt", "Image/UI/play-button.bmp", 0, 0, 433, 144, 1, 2);
	ImageManager::GetSingleton()->AddImage("blue-rectangle", "Image/UI/bluerectangle.bmp", 0, 0, 160, 160, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("tree", "Image/tree/tree.bmp", 0, 0, 640, 640, 5, 5, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("playerrun", "Image/player/player-basic-run.bmp", 0, 0, 1056, 568, 22, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("playerstop", "Image/player/player-basic-idle.bmp", 0, 0, 1166, 584, 22, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("playermine", "Image/player/player-basic-mine.bmp", 0, 0, 672, 456, 14, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("inventory", "Image/UI/inventory.bmp", 0, 0, 857, 422, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("fastinventory", "Image/UI/fast-inventory.bmp", 0, 0, 500, 63, 1, 1);
	ImageManager::GetSingleton()->AddImage("coal-ore", "Image/resource/coal.bmp", 0, 0, 152, 304, 4, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("iron-ore", "Image/resource/iron-ore.bmp", 0, 0, 152, 304, 4, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mousecursor", "Image/cursor/cursor-boxes.bmp", 0, 0, 128, 32, 8, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("copper-ore", "Image/resource/copper-ore.bmp", 0, 0, 152, 304, 4, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("objectinven", "Image/UI/objectinven.bmp", 0, 0, 500, 600, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-transport-belt", "Image/object/basic-transport-belt/basic-transport-belt.bmp", 0, 0, 640, 480, 16, 12, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("stone-furnace", "Image/object/sthone-furnace/stone-furnace.bmp", 0, 0, 81, 64, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("stone-furnace-fire", "Image/object/sthone-furnace/stone-furnace-fire.bmp", 0, 0, 276, 27, 12, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("burner-inserter-platform", "Image/object/burner-inserter/burner-inserter-platform.bmp", 0, 0, 184, 50, 4, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("burner-inserter-hand-base", "Image/object/burner-inserter/burner-inserter-hand-base.bmp", 0, 0, 8, 34, 1, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("burner-inserter-hand-closed", "Image/object/burner-inserter/burner-inserter-hand-closed.bmp", 0, 0, 18, 41, 1, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("burner-inserter-hand-open", "Image/object/burner-inserter/burner-inserter-hand-open.bmp", 0, 0, 18, 41, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("burner-mining-drill-east", "Image/object/burner-mining-drill/east.bmp", 0, 0, 376, 592, 4, 8, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("water", "Image/terrain/water/water.bmp", 0, 0, 256, 1056, 8, 33, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("intermediate-products", "Image/item-group/intermediate-products.bmp", 0, 0, 64, 128, 1, 2, false, NULL);
	ImageManager::GetSingleton()->AddImage("logistics", "Image/item-group/logistics.bmp", 0, 0, 64, 128, 1, 2, false, NULL);
	ImageManager::GetSingleton()->AddImage("military", "Image/item-group/military.bmp", 0, 0, 64, 128, 1, 2, false, NULL);
	ImageManager::GetSingleton()->AddImage("production", "Image/item-group/production.bmp", 0, 0, 64, 128, 1, 2, false, NULL);
	ImageManager::GetSingleton()->AddImage("stone", "Image/resource/stone.bmp", 0, 0, 152, 304, 4, 8, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("small-electric-pole", "Image/object/small-electric-pole/small-electric-pole.bmp", 0, 0, 479, 124, 4, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("bridge", "Image/terrain/bridge.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("electric-furnace", "Image/object/electric-furnace/electric-furnace-basic.bmp", 0, 0, 96, 96, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-mining-drill-east", "Image/object/basic-mining-drill/east.bmp", 0, 0, 1032, 800, 8, 8, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("assembling-machine", "Image/object/assembling-machine-1/assembling-machine-1.bmp", 0, 0, 792, 408, 8, 4, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("assemblinginven", "Image/UI/assemblinginven.bmp", 0, 0, 209, 199, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-inserter-platform", "Image/object/basic-inserter/basic-inserter-platform.bmp", 0, 0, 184, 50, 4, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("basic-inserter-hand-base", "Image/object/basic-inserter/basic-inserter-hand-base.bmp", 0, 0, 8, 34, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-inserter-hand-open", "Image/object/basic-inserter/basic-inserter-hand-open.bmp", 0, 0, 18, 41, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-inserter-hand-closed", "Image/object/basic-inserter/basic-inserter-hand-closed.bmp", 0, 0, 18, 41, 1, 1, true, RGB(255, 255, 255));

	ImageManager::GetSingleton()->AddImage("orangeBox", "Image/UI/orangeBox.bmp", 0, 0, 41, 41, 1, 1, false, NULL);
	ImageManager::GetSingleton()->AddImage("grayBox", "Image/UI/grayBox.bmp", 0, 0, 100, 100, 1, 1, false, NULL);
	ImageManager::GetSingleton()->AddImage("greenBox", "Image/UI/greenBox.bmp", 0, 0, 100, 100, 1, 1, false, NULL);
	ImageManager::GetSingleton()->AddImage("endingMenu", "Image/UI/endingMenu.bmp", 400, 700);
	ImageManager::GetSingleton()->AddImage("replayBt", "Image/UI/replayBt.bmp", 0, 0, 100, 100, 1, 2, false, NULL);
	ImageManager::GetSingleton()->AddImage("quitBt", "Image/UI/quitBt.bmp", 0, 0, 100, 100, 1, 2, false, NULL);
	// 로켓
	ImageManager::GetSingleton()->AddImage("rocket", "Image/object/rocket/rocket.bmp", 0, 0, 192, 288, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("rocket-jet-flame", "Image/object/rocket/rocket-jet-flame.bmp", 0, 0, 704, 132, 8, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("rocket-door-back", "Image/object/rocket/rocket-door-back.bmp", 0, 0, 198, 108, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("rocket-door-front", "Image/object/rocket/rocket-door-front.bmp", 0, 0, 192, 112, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("rocket-base", "Image/object/rocket/rocket-base.bmp", 0, 0, 352, 384, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("rocket-base-shadow", "Image/object/rocket/rocket-base-shadow.bmp", 0, 0, 448, 352, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("rocket-effect", "Image/object/rocket/rocket-effect.bmp", 0, 0, 545, 466, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("rocket-hole-light", "Image/object/rocket/rocket-hole-light.bmp", 0, 0, 224, 128, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("rocket-hole", "Image/object/rocket/rocket-hole.bmp", 0, 0, 224, 128, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("rocket-silo-front", "Image/object/rocket/rocket-silo-front.bmp", 0, 0, 352, 96, 1, 1, true, RGB(255, 0, 255));


	// 증기기관
	ImageManager::GetSingleton()->AddImage("steam-engine-vertical", "Image/object/steam-engine/steam-engine-vertical.bmp", 0, 0, 1240, 744, 8, 4, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("steam-engine-horizontal", "Image/object/steam-engine/steam-engine-horizontal.bmp", 0, 0, 1968, 548, 8, 4, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("boiler-left", "Image/object/steam-engine/boiler-left.bmp", 0, 0, 46, 46, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("boiler-down", "Image/object/steam-engine/boiler-down.bmp", 0, 0, 66, 72, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("boiler-fire-left", "Image/object/steam-engine/boiler-fire-left.bmp", 0, 0, 70, 7, 12, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("boiler-fire-right", "Image/object/steam-engine/boiler-fire-right.bmp", 0, 0, 84, 9, 12, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("offshore-pump", "Image/object/steam-engine/offshore-pump.bmp", 0, 0, 640, 102, 4, 1, true, RGB(255, 0, 255));
	// 아이콘 // 
	ImageManager::GetSingleton()->AddImage("clock-icon", "Image/icon/clock-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("coal-icon", "Image/icon/coal-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("iron-icon", "Image/icon/iron-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("copper-icon", "Image/icon/copper-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("raw-wood-icon", "Image/icon/raw-wood-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("stone-icon", "Image/icon/stone-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("burner-inserter-icon", "Image/icon/burner-inserter-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("burner-mining-drill-icon", "Image/icon/burner-mining-drill-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-transport-belt-icon", "Image/icon/basic-transport-belt-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("stone-furnace-icon", "Image/icon/stone-furnace-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("iron-axe-icon", "Image/icon/iron-axe-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(200, 200, 200));
	ImageManager::GetSingleton()->AddImage("iron-gear-wheel-icon", "Image/icon/iron-gear-wheel-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("iron-plate-icon", "Image/icon/iron-plate-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("lab-icon", "Image/icon/lab-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(200, 200, 200));
	ImageManager::GetSingleton()->AddImage("steel-chest-icon", "Image/icon/steel-chest-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(200, 200, 200));
	ImageManager::GetSingleton()->AddImage("wooden-chest-icon", "Image/icon/wooden-chest-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(200, 200, 200));
	ImageManager::GetSingleton()->AddImage("copper-plate-icon", "Image/icon/copper-plate-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("electronic-circuit-icon", "Image/icon/electronic-circuit-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(200, 200, 200));
	ImageManager::GetSingleton()->AddImage("iron-stick-icon", "Image/icon/iron-stick-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("copper-cable-icon", "Image/icon/copper-cable-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("wood-icon", "Image/icon/wood-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("rocket-icon", "Image/icon/rocket-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("small-electric-pole-icon", "Image/icon/small-electric-pole-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("steam-engine-icon", "Image/icon/steam-engine-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("electric-furnace-icon", "Image/icon/electric-furnace-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("basic-inserter-icon", "Image/icon/basic-inserter-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-mining-drill-icon", "Image/icon/basic-mining-drill-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("fuel-icon-red", "Image/UI/fuel-icon-red.bmp", 0, 0, 100, 89, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("electricity-icon-yellow", "Image/UI/electricity-icon-yellow.bmp", 0, 0, 100, 89, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("assembling-machine-icon", "Image/icon/assembling-machine-1-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("advanced-circuit-icon", "Image/icon/advanced-circuit.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-splitter-icon", "Image/icon/basic-splitter-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mini-assembling-machine-icon", "Image/mapIcon/mini-assembling-machine-icon.bmp", 0, 0, 9, 9, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mini-electric-pole-icon", "Image/mapIcon/mini-electric-pole-icon.bmp", 0, 0, 3, 3, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mini-inserter-icon", "Image/mapIcon/mini-inserter-icon.bmp", 0, 0, 3, 3, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mini-rocket-icon", "Image/mapIcon/mini-rocket-icon.bmp", 0, 0, 27, 27, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mini-splitter-icon", "Image/mapIcon/mini-splitter-icon.bmp", 0, 0, 24, 6, 4, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mini-steam-engine-icon", "Image/mapIcon/mini-steam-engine-icon.bmp", 0, 0, 9, 9, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mini-steel-chest-icon", "Image/mapIcon/mini-steel-chest-icon.bmp", 0, 0, 3, 3, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mini-wooden-chest-icon", "Image/mapIcon/mini-wooden-chest-icon.bmp", 0, 0, 3, 3, 1, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("basic-splitter-east", "Image/object/basic-splitter/basic-splitter-east.bmp", 0, 0, 736, 162, 16, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-splitter-west", "Image/object/basic-splitter/basic-splitter-west.bmp", 0, 0, 752, 158, 16, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-splitter-south", "Image/object/basic-splitter/basic-splitter-south.bmp", 0, 0, 1312, 72, 16, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("basic-splitter-north", "Image/object/basic-splitter/basic-splitter-north.bmp", 0, 0, 1280, 70, 16, 2, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("worldmapBuffer", WINSIZE_X, WINSIZE_Y);
	// 맵 아이콘
	ImageManager::GetSingleton()->AddImage("mini-furnace-icon", "Image/mapIcon/mini-furnace-icon.bmp", 0, 0, 6, 6, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mini-mining-drill-icon", "Image/mapIcon/mini-mining-drill-icon.bmp", 0, 0, 6, 6, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mini-transport-belt-icon", "Image/mapIcon/mini-transport-belt-icon.bmp", 0, 0, 3, 3, 1, 1, true, RGB(255, 0, 255));

	//추가
	ImageManager::GetSingleton()->AddImage("long-handed-inserter-icon", "Image/icon/long-handed-inserter-icon.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("long-handed-inserter-hand-base", "Image/object/long-handed-inserter/long-handed-inserter-hand-base.bmp", 0, 0, 8, 34, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("long-handed-inserter-hand-open", "Image/object/long-handed-inserter/long-handed-inserter-hand-open.bmp", 0, 0, 18, 58, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("long-handed-inserter-platform", "Image/object/long-handed-inserter/long-handed-inserter-platform.bmp", 0, 0, 184, 50, 4, 1, true, RGB(255, 0, 255));


	//사운드

	SoundManager::GetSingleton()->AddSound("launchrocket", "Sound/silo-rocket.ogg", false, false);
	SoundManager::GetSingleton()->AddSound("raiserocket", "Sound/silo-raise-rocket.ogg", false, false);
	SoundManager::GetSingleton()->AddSound("longinserterworking", "Sound/inserter-long-handed-2.ogg", false, false);
	SoundManager::GetSingleton()->AddSound("basicinserterworking", "Sound/inserter-basic-1.ogg", false, false);
	SoundManager::GetSingleton()->AddSound("stonefurnace", "Sound/furnace.ogg", false, true);
	SoundManager::GetSingleton()->AddSound("playerwalking", "Sound/grass-02.ogg", false, true);
	SoundManager::GetSingleton()->AddSound("playermine", "Sound/axe-mining-ore-1.ogg", false, true);
	SoundManager::GetSingleton()->AddSound("build", "Sound/build-large.ogg", false, false);
	SoundManager::GetSingleton()->AddSound("remove", "Sound/build-small.ogg", false, false);
	SoundManager::GetSingleton()->AddSound("basictransportbelt", "Sound/basic-transport-belt.ogg", false, true);
	SoundManager::GetSingleton()->AddSound("steamengine", "Sound/steam-engine-90bpm.ogg", false, true);
	SoundManager::GetSingleton()->AddSound("electricminingdrill", "Sound/electric-mining-drill.ogg", false, true);
	SoundManager::GetSingleton()->AddSound("burnerminingdrill", "Sound/burner-mining-drill.ogg", false, true);
	SoundManager::GetSingleton()->AddSound("invenopen", "Sound/machine-open.ogg", false, false);
	SoundManager::GetSingleton()->AddSound("invenclose", "Sound/machine-close.ogg", false, false);
	SoundManager::GetSingleton()->AddSound("gameclear", "Sound/game-won.ogg", false, false);
	SoundManager::GetSingleton()->AddSound("assemblingmachine", "Sound/assembling-machine-t1-1.ogg", false, true);
	SoundManager::GetSingleton()->AddSound("electricfurnace", "Sound/electric-furnace.ogg", false, true);
	SoundManager::GetSingleton()->AddSound("playerminewood", "Sound/mining-wood-1.ogg", false, true);
	SoundManager::GetSingleton()->AddSound("BGM1", "Sound/are-we-alone.ogg", true, false);
	SoundManager::GetSingleton()->AddSound("BGM2", "Sound/automation.ogg", true, false);
	SoundManager::GetSingleton()->AddSound("BGM3", "Sound/beyond-factory-outskirts.ogg", true, false);
		

	// 씬
	titleScene = new TitleScene();
	SceneManager::GetSingleton()->AddScene("titleScene", titleScene);
	inGameScene = new InGameScene();
	SceneManager::GetSingleton()->AddScene("inGameScene", inGameScene);

	// 로딩 씬
	loadingScene = new LoadingScene();
	SceneManager::GetSingleton()->AddLoadingScene("loadingScene", loadingScene);

	// 현재 씬
	SceneManager::GetSingleton()->ChangeScene("titleScene");

	isInit = true;

	return S_OK;
}

void MainGame::Release()
{
	SceneManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->ReleaseSingleton();

	SoundManager::GetSingleton()->Release();
	SoundManager::GetSingleton()->ReleaseSingleton();

	TimeManager::GetSingleton()->Release();
	TimeManager::GetSingleton()->ReleaseSingleton();

	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	ObjectManager::GetSingleton()->Release();
	ObjectManager::GetSingleton()->ReleaseSingleton();
	
	SoundManager::GetSingleton()->Release();
	backBuffer->Release();
	delete backBuffer;

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SoundManager::GetSingleton()->Update();
	SceneManager::GetSingleton()->Update();
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	SceneManager::GetSingleton()->Render(backBuffer->GetMemDC());
	TimeManager::GetSingleton()->Render(backBuffer->GetMemDC());
	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;


	switch (iMessage)
	{
	case WM_MOUSEWHEEL:
		if ((SHORT)HIWORD(wParam) > 0)
		{
			cameraScale += 0.1;
			if (cameraScale >= 3)
				cameraScale = 3;
		}
			
		else
		{
			cameraScale -= 0.1;
			if (cameraScale <= 1)
				cameraScale = 1;
		}
			
		break;

	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_TIMER:
		if (isInit)
			this->Update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
	
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
	: isInit(false)
{
}


MainGame::~MainGame()
{
}
