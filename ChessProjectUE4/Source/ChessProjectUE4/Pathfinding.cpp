// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "Pathfinding.h"

#include <algorithm>

Pathfinding::Pathfinding(TileInformations & tileInfo)
    :mTileInfo(tileInfo)
{
}

Pathfinding::~Pathfinding()
{
}

Pathfinding::weightedTiles Pathfinding::GetWeightedTiles(TileInformation *startingTile)
{
    weightedTiles tiles = CreateWeightedTiles();
    WeightedTile * startingPoint = nullptr;

    for (auto & tileRow : tiles)
    {
        for (auto & tile : tileRow)
        {
            if (tile == startingTile)
            {
                startingPoint = &tile;
                break;
            }
        }
    }

    if (startingPoint)
    {
        startingPoint->ChangeWeight(0);
        ComputeNeighborPaths(tiles, startingPoint);
    }

    return tiles;
}

Pathfinding::weightedTiles Pathfinding::CreateWeightedTiles()
{
    weightedTiles tiles;

    const int MAX_INDEX = mTileInfo.GetMaxIndex();
    tiles.SetNum(MAX_INDEX);

    for (int x = 0; x < MAX_INDEX; x++)
    {
        for (int y = 0; y < MAX_INDEX; y++)
        {
            WeightedTile tile(mTileInfo.GetTileInfo(x, y));
            tile.SetPosition(x, y);
            tiles[x].Add(tile);
        }
    }

    return tiles;
}

void Pathfinding::ComputeNeighborPaths(weightedTiles & tiles, WeightedTile * tile)
{
    auto neighbors = GetNeighbors(tiles, tile);
    int neighborWeight = tile->GetWeight() + 1;
    TArray<WeightedTile*> changedNeighbors;

    for (auto neighbor : neighbors)
    {
        bool isOccupiedtest = neighbor->IsOccupied();
        if (!neighbor->IsOccupied())
        {
            if (neighbor->ChangeWeight(neighborWeight))
            {
                changedNeighbors.Add(neighbor);
            }
        }
    }

    for (auto neighbor : changedNeighbors)
    {
        ComputeNeighborPaths(tiles, neighbor);
    }
}

TArray<WeightedTile*> Pathfinding::GetNeighbors(Pathfinding::weightedTiles & tiles,
                                                WeightedTile * tile)
{
    TArray<WeightedTile*> neighbors;

    const int X = tile->GetPositionX();
    const int Y = tile->GetPositionY();

    int minX = std::max(X - 1, 0);
    int maxX = std::min(X + 1, mTileInfo.GetMaxIndex() - 1);
    int minY = std::max(Y - 1, 0);
    int maxY = std::min(Y + 1, mTileInfo.GetMaxIndex() - 1);

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            if (!(x == X && y == Y))
            {
                neighbors.Add(&(tiles[x][y]));
            }
        }
    }

    return neighbors;
}
