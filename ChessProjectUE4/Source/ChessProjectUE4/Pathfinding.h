// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TileInformations.h"

class WeightedTile
{
    TileInformation * mTile = nullptr;
    int mWeight = 9999;
    int mX = 0;
    int mY = 0;

public:
    WeightedTile(TileInformation * tile)
        :mTile(tile)
    {
    }

    void SetPosition(const int x, const int y)
    {
        mX = x;
        mY = y;
    }

    int GetPositionX() const
    {
        return mX;
    }

    int GetPositionY() const
    {
        return mY;
    }

    bool IsOccupied() const
    {
        return mTile && mTile->piece;
    }

    bool ChangeWeight(int weight)
    {
        if (weight < mWeight)
        {
            mWeight = weight;
            return true;
        }
        return false;
    }

    int GetWeight() const
    {
        return mWeight;
    }

    bool operator==(TileInformation * tile)
    {
        return tile == mTile;
    }

    bool operator==(WeightedTile * tile)
    {
        return tile->mTile == mTile;
    }

    bool operator==(ChessTile * chessTile)
    {
        return mTile->tile == chessTile;
    }

    TileInformation * GetTileInfo()
    {
        return mTile;
    }
};

class WeightedTiles
{
    TArray<TArray<WeightedTile>> mWeightedTiles;
    TileInformations & mTileInfo;
public:


    WeightedTiles(TileInformations & tileInfo);
    WeightedTile * GetWeightedTileFromTile(ChessTile * tile);
    WeightedTile * GetWeightedTileFromTile(TileInformation *tile);

    WeightedTile * Get(const int X, const int Y);

    TArray<WeightedTile*> GetFlatArray();
};

/**
 *
 */
class CHESSPROJECTUE4_API Pathfinding
{
    TileInformations & mTileInfo;

public:
    Pathfinding(TileInformations & tileInfo);
    ~Pathfinding();

    WeightedTiles GetWeightedTiles(TileInformation *startingTile);

private:
    TArray<WeightedTile*> GetNeighbors(WeightedTiles & tiles, WeightedTile * tile);
    void ComputeNeighborPaths(WeightedTiles & tiles, WeightedTile * tile);
};
