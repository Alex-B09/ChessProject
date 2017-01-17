// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "Pathfinding.h"

#include <algorithm>


WeightedTiles::WeightedTiles(TileInformations & tileInfo)
    :mTileInfo(tileInfo)
{
    const int MAX_INDEX = mTileInfo.GetMaxIndex();
    mWeightedTiles.SetNum(MAX_INDEX);

    for (int x = 0; x < MAX_INDEX; x++)
    {
        for (int y = 0; y < MAX_INDEX; y++)
        {
            WeightedTile tile(mTileInfo.GetTileInfo(x, y));
            tile.SetPosition(x, y);
            mWeightedTiles[x].Add(tile);
        }
    }
}

WeightedTile * WeightedTiles::GetWeightedTileFromTile(ChessTile * tileToFind)
{
    for (auto & tileRow : mWeightedTiles)
    {
        for (auto & tile : tileRow)
        {
            if (tile == tileToFind)
            {
                return &tile;
            }
        }
    }

    return nullptr;
}

WeightedTile * WeightedTiles::GetWeightedTileFromTile(TileInformation *tileToFind)
{
    for (auto & tileRow : mWeightedTiles)
    {
        for (auto & tile : tileRow)
        {
            if (tile == tileToFind)
            {
                return &tile;
            }
        }
    }

    return nullptr;
}

WeightedTile * WeightedTiles::Get(const int X, const int Y)
{
    return &mWeightedTiles[X][Y];
}

TArray<WeightedTile*> WeightedTiles::GetFlatArray()
{
    TArray<WeightedTile*> flatArray;

    for (auto & tileRow : mWeightedTiles)
    {
        for (auto & tile : tileRow)
        {
            flatArray.Add(&tile);
        }
    }

    return flatArray;
}

Pathfinding::Pathfinding(TileInformations & tileInfo)
    :mTileInfo(tileInfo)
{
}

Pathfinding::~Pathfinding()
{
}

WeightedTiles Pathfinding::GetWeightedTiles(TileInformation *startingTile)
{
    WeightedTiles tiles(mTileInfo);
    WeightedTile * startingPoint = nullptr;

    startingPoint = tiles.GetWeightedTileFromTile(startingTile);

    if (startingPoint)
    {
        startingPoint->ChangeWeight(0);
        ComputeNeighborPaths(tiles, startingPoint);
    }

    return tiles;
}

void Pathfinding::ComputeNeighborPaths(WeightedTiles & tiles, WeightedTile * tile)
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

TArray<WeightedTile*> Pathfinding::GetNeighbors(WeightedTiles & tiles,
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
                neighbors.Add(tiles.Get(x, y));
            }
        }
    }

    return neighbors;
}
