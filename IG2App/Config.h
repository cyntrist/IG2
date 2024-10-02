#pragma once

constexpr float WALL_LENGTH = 20;
constexpr double PEARL_SIZE = 0.15;
const std::string WALL_NAME = "wall";
const std::string PEARL_NAME = "pearl";
const std::string WALL_MESH = "cube.mesh";
const std::string PEARL_MESH = "sphere.mesh";
const std::string LAB_PATH = "../media/labyrinths/stage1.txt";
constexpr float LAB_DEPTH = -1500;
constexpr float LAB_XSET = -800;
constexpr float LAB_YSET = -900;
constexpr int H_DEPTH = -1500;
constexpr int H_XSET = 0;
constexpr int H_YSET = 0;

static Ogre::Vector3 sWallSize = {WALL_LENGTH,WALL_LENGTH,WALL_LENGTH};
static double sLabWidth = 0;
static double sLabHeight = 0;
