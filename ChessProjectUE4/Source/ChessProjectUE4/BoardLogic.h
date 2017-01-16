// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessBoard.h"
#include "ChessPiece.h"
#include "ChessTile.h"

#include "TileInformations.h"

/**
 * BoardLogic

    class containing the logic of the board
        - movement
        - tiles
        - pieces
 */

class CHESSPROJECTUE4_API BoardLogic
{
    AChessBoard* mBoardActor;       // non-owning ptr
    UWorld* mWorld;                 // non-owning ptr

    TArray<AChessPiece*> mPieces;  // the owner of the all the pieces
    TArray<AChessPiece*> mWhitePieces;
    TArray<AChessPiece*> mBlackPieces;

    TArray<ChessTile> mTiles;
    TileInformations mTileInfos;

public:
    BoardLogic() = default;
    BoardLogic(AChessBoard* board, UWorld* world);

    void MovePiece(AChessPiece* piece, ChessTile * tileDestination);
    ChessTile * getChessTileFromComponent(UStaticMeshComponent * component);

    bool isRightColor(AChessPiece * piece, bool isWhite);
    void HighlingPossiblePlacement(AChessPiece * piece);

private:
    void CreateTiles();
    void PlacePieces();
    void HideAllSelectors();
};
