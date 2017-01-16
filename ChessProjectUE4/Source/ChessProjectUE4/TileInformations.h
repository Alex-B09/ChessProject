// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessPiece.h"
#include "ChessTile.h"

struct TileInformation
{
    ChessTile * tile = nullptr;
    AChessPiece * piece = nullptr;
};

/**
 *
 */
class CHESSPROJECTUE4_API TileInformations
{
    TArray<TArray<TileInformation>> mInformations;
    const int MAX_INDEX;
    const int MIN_INDEX = 0;

public:
    TileInformations(const int NB_TILES);
    ~TileInformations() = default;

    // return a non-owning pointer
    TileInformation * GetTileInfo(int x, int y);
    TileInformation * GetTileInfoFromPiece(AChessPiece * piece);
    TileInformation * GetTileInfoFromTile(ChessTile * tile);

    const int GetMaxIndex()const
    {
        return MAX_INDEX;
    }
    const int GetMinIndex()const
    {
        return MIN_INDEX;
    }



private:
    bool IsIndexOK(int index) const;
};

