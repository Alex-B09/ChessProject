// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "BoardLogic.h"
#include "ChessPiecePawn.h"
#include "ChessPieceRook.h"
#include "ChessPieceKnight.h"
#include "ChessPieceBishop.h"
#include "ChessPieceQueen.h"
#include "ChessPieceKing.h"

#include "EngineUtils.h"

BoardLogic::BoardLogic(AChessBoard* board, UWorld* world)
    : mBoardActor(board)
    , mWorld(world)
{
    CreateTiles();
    PlacePieces();
}

void BoardLogic::CreateTiles()
{
    mTiles.Empty(0); // just to be sure
    mTiles.Reserve(mBoardActor->getNbTiles());

    auto root = mBoardActor->GetRootComponent();
    auto children = root->GetAttachChildren();

    for (auto child : children)
    {
        if (auto tile = Cast<UStaticMeshComponent>(child))
        {
            if (auto selector = Cast<UStaticMeshComponent>(tile->GetChildComponent(0)))
            {
                mTiles.Add({ tile, selector });
            }
        }
    }

    for (auto & tile : mTiles)
    {
        tile.SetSelectorVisibility(false);
    }
}

void BoardLogic::PlacePieces()
{
    auto piecesPlacement = mBoardActor->getPiecesPlacement();
    FVector zDelta(0.f, 0.f, 20.f);

    // personal note : if there is no values associated with Roll/Pitch/Yah,
    //                  there will be garbage values
    FRotator blackRotation(0.f, 180.f, 0.f);

    // set pieces to right spot
    for (int i = 0; i < piecesPlacement.Num(); ++i)
    {
        AChessPiece * chessPiece = nullptr;
        int currentPlacement = piecesPlacement[i];
        int currentPiece = currentPlacement % 10;
        bool isBlack = currentPlacement > 10;

        auto currentTile = mTiles[i];

        auto spawnPosition = currentTile.GetGlobalPosition() + zDelta;
        auto spawnRotation = currentTile.GetGlobalRotation();

        if (isBlack)
        {
            spawnRotation += blackRotation;
        }

        switch (currentPiece)
        {
        case 0:
            // nothing
            break;
        case PAWN:
            chessPiece = mWorld->SpawnActor<AChessPiecePawn>(spawnPosition, spawnRotation);
            break;
        case ROOK:
            chessPiece = mWorld->SpawnActor<AChessPieceRook>(spawnPosition, spawnRotation);
            break;
        case KNIGHT:
            chessPiece = mWorld->SpawnActor<AChessPieceKnight>(spawnPosition, spawnRotation);
            break;
        case BISHOP:
            chessPiece = mWorld->SpawnActor<AChessPieceBishop>(spawnPosition, spawnRotation);
            break;
        case QUEEN:
            chessPiece = mWorld->SpawnActor<AChessPieceQueen>(spawnPosition, spawnRotation);
            break;
        case KING:
            chessPiece = mWorld->SpawnActor<AChessPieceKing>(spawnPosition, spawnRotation);
            break;
        default:
            break;
        }

        if (chessPiece)
        {
            chessPiece->setMaterial(isBlack);
            mPieces.Add(chessPiece);
        }
    }
}
