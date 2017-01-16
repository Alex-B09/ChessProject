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

    TileInformation * GetTileInfo()
    {
        return mTile;
    }
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

    using weightedTiles = TArray<TArray<WeightedTile>>;
    weightedTiles GetWeightedTiles(TileInformation *startingTile);

private:
    weightedTiles CreateWeightedTiles();
    TArray<WeightedTile*> GetNeighbors(weightedTiles & tiles, WeightedTile * tile);
    void ComputeNeighborPaths(weightedTiles & tiles, WeightedTile * tile);
};
