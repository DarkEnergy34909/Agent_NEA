#pragma once

enum Levels {
	LEVEL_1,
	LEVEL_2,
	LEVEL_3
};

struct LevelData {
	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;

	int TOTAL_TILES;
	int TOTAL_TILE_TYPES;

	int HORIZONTAL_TILES;
	int VERTICAL_TILES;

	// Other constants ...
};

static const LevelData LEVEL_1_DATA = { 800, 640, 80, 12, 10, 8 };
static const LevelData LEVEL_2_DATA = { 640, 480, 48, 12, 8, 6 };
static const LevelData LEVEL_3_DATA = { 800, 640, 80, 12, 10, 8 };

static const std::string PATH = "C:/Users/Sebastian Kember/OneDrive - King Edward VI Grammar School/CS A-Level/NEA/Media/";

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

static const int LEVEL_WIDTH = 800;
static const int LEVEL_HEIGHT = 640;

static const int TILE_WIDTH = 80;
static const int TILE_HEIGHT = 80;

static const int TOTAL_TILES = 80;
static const int TOTAL_TILE_TYPES = 12;

static const int HORIZONTAL_TILES = 10;
static const int VERTICAL_TILES = 8;

