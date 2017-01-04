// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessBoard.h"
#include "ChessPiece.h"
#include "ChessTile.h"
#include "PieceSpawner.h"

/**
 * BoardLogic

    class containing the logic of the board
        - movement
        - tiles
        - pieces
 */

class CHESSPROJECTUE4_API BoardLogic
{
    //TArray<AChessPiece*> mPieces;
    AChessBoard* mBoardActor;       // non-owning ptr
    UWorld* mWorld;                 // non-owning ptr
    TArray<AChessPiece*> mPieces;  // the owner of the all the pieces
    TArray<ChessTile> mTiles;

public:
    BoardLogic() = default;
    BoardLogic(AChessBoard* board, UWorld* world, PieceSpawner & spawner);

private:
    void CreateTiles();
    void PlacePieces(PieceSpawner & spawner);
};
