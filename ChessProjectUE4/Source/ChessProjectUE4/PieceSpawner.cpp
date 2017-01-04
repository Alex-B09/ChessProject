// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "PieceSpawner.h"

#include "ChessPiece.h"

PieceSpawner::PieceSpawner()
{
    AddPieceClass(EPieces::PE_PAWN, FString("Material'/Game/Blueprints/Pieces/BP_Pawn'"));
    AddPieceClass(EPieces::PE_ROOK, FString("Material'/Game/Blueprints/Pieces/BP_Rook'"));
    AddPieceClass(EPieces::PE_KNIGHT, FString("Material'/Game/Blueprints/Pieces/BP_Knight'"));
    AddPieceClass(EPieces::PE_BISHOP, FString("Material'/Game/Blueprints/Pieces/BP_Bishop'"));
    AddPieceClass(EPieces::PE_QUEEN, FString("Material'/Game/Blueprints/Pieces/BP_Queen'"));
    AddPieceClass(EPieces::PE_KING, FString("Material'/Game/Blueprints/Pieces/BP_King'"));
}

PieceSpawner::~PieceSpawner()
{
}

void PieceSpawner::AddPieceClass(EPieces piece, FString path)
{
    ConstructorHelpers::FObjectFinder<UBlueprint> pieceBP(*path);

    if (pieceBP.Succeeded())
    {
        mPieceClasses.Add({ piece, pieceBP.Object });
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid : %s"), *path);
    }
}

UBlueprint* PieceSpawner::GetPieceBPActor(EPieces piece)
{
    auto foundElem = mPieceClasses.FindByPredicate(
        [&](std::pair<EPieces, UBlueprint*> elem)
    {
        return elem.first == piece;
    });

    if (foundElem)
    {
        return foundElem->second;
    }
    return nullptr;
}
