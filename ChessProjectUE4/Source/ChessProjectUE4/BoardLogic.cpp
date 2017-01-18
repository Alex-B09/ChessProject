// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "BoardLogic.h"
#include "EditorRessourceBank.h"
#include "Pathfinding.h"


#include "EngineUtils.h"

BoardLogic::BoardLogic(AChessBoard* board, UWorld* world)
    : mBoardActor(board)
    , mWorld(world)
    , mTileInfos(mBoardActor->getNbTiles())
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
    const int MAX_INDEX_ROW = mTileInfos.GetMaxIndex();
    // set pieces to right spot
    for (int i = 0; i < piecesPlacement.Num(); ++i)
    {
        AChessPiece * chessPiece = nullptr;
        auto tileInfo = mTileInfos.GetTileInfo(i / MAX_INDEX_ROW, i % MAX_INDEX_ROW);
        int currentPlacement = piecesPlacement[i];
        int currentPiece = currentPlacement % 10;
        bool isBlack = currentPlacement > 10;

        auto & currentTile = mTiles[i];
        tileInfo->tile = &currentTile;

        auto spawnPosition = currentTile.GetGlobalPosition() + zDelta;
        auto spawnRotation = currentTile.GetGlobalRotation();

        if (isBlack)
        {
            spawnRotation += blackRotation;
        }

        if (currentPiece != 0)
        {
            using RessourceBlueprints = EditorRessourceBank::RessourceBlueprints;

            RessourceBlueprints type = RessourceBlueprints::PIECE_PAWN;

            switch (currentPiece)
            {
                case 1:
                    type = RessourceBlueprints::PIECE_PAWN;
                    break;
                case 2:
                    type = RessourceBlueprints::PIECE_ROOK;
                    break;
                case 3:
                    type = RessourceBlueprints::PIECE_KNIGHT;
                    break;
                case 4:
                    type = RessourceBlueprints::PIECE_BISHOP;
                    break;
                case 5:
                    type = RessourceBlueprints::PIECE_QUEEN;
                    break;
                case 6:
                    type = RessourceBlueprints::PIECE_KING;
                    break;
                default:
                    break;
            }

            if (auto pieceActor = EditorRessourceBank::GetBlueprintRessource(type))
            {
                chessPiece = mWorld->SpawnActor<AChessPiece>(
                    pieceActor->GeneratedClass,
                    spawnPosition,
                    spawnRotation);

                if (chessPiece)
                {
                    chessPiece->setMaterial(isBlack);
                    mPieces.Add(chessPiece);
                    tileInfo->piece = chessPiece;
                    if (isBlack)
                    {
                        mBlackPieces.Add(chessPiece);
                    }
                    else
                    {
                        mWhitePieces.Add(chessPiece);
                    }
                }
            }
        }
    }
}

bool BoardLogic::MovePiece(AChessPiece* piece, ChessTile * tileDestination)
{
    bool isValidMove = false;
    auto oldTile = mTileInfos.GetTileInfoFromPiece(piece);
    auto newTile = mTileInfos.GetTileInfoFromTile(tileDestination);

    if (mCurrentSelectionPathfinding)
    {
        auto weightedDestination = mCurrentSelectionPathfinding->GetWeightedTileFromTile(tileDestination);
        const int MAX_MOVEMENT = piece->GetMovementValue();
        if (weightedDestination->GetWeight() <= MAX_MOVEMENT)
        {
            oldTile->piece = nullptr;
            newTile->piece = piece;

            piece->SetActorLocation(tileDestination->GetGlobalPosition());
            mCurrentSelectionPathfinding.reset(nullptr);
            HideAllSelectors();
            isValidMove = true;
        }
    }

    return isValidMove;
}

bool BoardLogic::IsValidMove(AChessPiece* piece, ChessTile * tileDestination)
{
    bool isValidMove = false;

    if (mCurrentSelectionPathfinding)
    {
        auto weightedDestination = mCurrentSelectionPathfinding->GetWeightedTileFromTile(tileDestination);
        const int MAX_MOVEMENT = piece->GetMovementValue();
        isValidMove = weightedDestination->GetWeight() <= MAX_MOVEMENT;
    }

    return isValidMove;
}

ChessTile * BoardLogic::getChessTileFromComponent(UStaticMeshComponent * component)
{
    auto foundTile = mTiles.FindByPredicate([component](ChessTile & tile)
    {
        return tile.isSameTile(component);
    });

    return foundTile;
}

bool BoardLogic::isRightColor(AChessPiece * piece, bool isWhite)
{
    if (isWhite)
    {
        return mWhitePieces.Contains(piece);
    }
    return mBlackPieces.Contains(piece);
}

void BoardLogic::HighlingPossiblePlacement(AChessPiece * piece)
{
    Pathfinding pathfinding(mTileInfos);
    auto tileInfo = mTileInfos.GetTileInfoFromPiece(piece);

    auto weightedTiles = pathfinding.GetWeightedTiles(tileInfo);

    HideAllSelectors();

    for (auto & tile : weightedTiles.GetFlatArray())
    {
        int weight = tile->GetWeight();
        if (weight <= piece->GetMovementValue() && weight > 0)
        {
            tile->GetTileInfo()->tile->SetSelectorVisibility(true);
        }
    }

    mCurrentSelectionPathfinding = std::make_unique<WeightedTiles>(std::move(weightedTiles));
}

void BoardLogic::HideAllSelectors()
{
    for (auto & tile : mTiles)
    {
        tile.SetSelectorVisibility(false);
    }
}
