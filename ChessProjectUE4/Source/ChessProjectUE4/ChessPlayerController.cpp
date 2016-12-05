// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPlayerController.h"

#include "ChessBoard.h"


void AChessPlayerController::BeginPlay()
{
    if (auto world = GetWorld())
    {
        //TSubclassOf<AChessBoard> classToFind;
        TArray<AActor*> foundActors;
        UGameplayStatics::GetAllActorsOfClass(world, AChessBoard::StaticClass(), foundActors);

        if (foundActors.Num() > 0)
        {
            SetViewTarget(foundActors[0]);
        }
    }
}

