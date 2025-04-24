#pragma once

enum TerrainState
{
    EMPTY = 0,
    TREE = 1,
    BURNING = 2,
    BURNT = 3,
    WATER = 4
};

enum MovePriority
{
    NONE = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};