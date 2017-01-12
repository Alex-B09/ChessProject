// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "TileInformations.h"

TileInformations::TileInformations(const int NB_TILES)
    :MAX_INDEX(static_cast<int>(FMath::Sqrt(NB_TILES)))
{
    mInformations.SetNum(MAX_INDEX);

    for (int i = 0; i < MAX_INDEX; ++i)
    {
        mInformations[i].SetNum(MAX_INDEX);
    }
}

TileInformation * TileInformations::GetTileInfo(int x, int y)
{
    if (IsIndexOK(x) && IsIndexOK(y))
    {
        return &(mInformations[x][y]);
    }
    return nullptr;
}

TileInformation * TileInformations::GetTileFromPiece(AChessPiece * piece)
{
    if (piece)
    {
        auto findByPiece = [piece](TileInformation & tileInfo)
                            {
                                return tileInfo.piece == piece;
                            };

        for (int i = 0; i < MAX_INDEX; ++i)
        {
            if (auto tileInfo = mInformations[i].FindByPredicate(findByPiece))
            {
                return tileInfo;
            }
        }
    }
    return nullptr;
}

bool TileInformations::IsIndexOK(int index) const
{
    return index >= MIN_INDEX
        && index < MAX_INDEX;
}
