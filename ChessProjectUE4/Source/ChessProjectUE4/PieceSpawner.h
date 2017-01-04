// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessProjectUE4.h"

#include <utility>

/**
 *
 */
class CHESSPROJECTUE4_API PieceSpawner
{
public:
    PieceSpawner();
    ~PieceSpawner();

    UBlueprint* GetPieceBPActor(EPieces piece);
private:
    void AddPieceClass(EPieces piece, FString path);
private:
    TArray <std::pair<EPieces, UBlueprint*>> mPieceClasses;

};
