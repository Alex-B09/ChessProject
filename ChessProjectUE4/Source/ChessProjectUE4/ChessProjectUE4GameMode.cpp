// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessProjectUE4GameMode.h"
#include "ChessBoard.h"


#include "ChessPlayerController.h"
#include "EngineUtils.h"

AChessProjectUE4GameMode::AChessProjectUE4GameMode()
{
    PlayerControllerClass = AChessPlayerController::StaticClass();
}

void AChessProjectUE4GameMode::StartPlay()
{
    auto board = getChessBoard();
    if (board)
    {
        mBoardLogic = std::make_unique<BoardLogic>(board, GetWorld());
    }

    Super::StartPlay();
}

AChessBoard * AChessProjectUE4GameMode::getChessBoard() const
{
    AChessBoard * board = nullptr;
    if (auto world = GetWorld())
    {
        TArray<AActor*> foundActors;
        UGameplayStatics::GetAllActorsOfClass(world, AChessBoard::StaticClass(), foundActors);

        if (foundActors.Num() > 0)
        {
            board = Cast<AChessBoard>(foundActors[0]);
        }
    }

    if (!board)
    {
        UE_LOG(LogTemp, Warning, TEXT("AChessProjectUE4GameMode::getChessBoard() board not found"));
    }
    return board;
}
