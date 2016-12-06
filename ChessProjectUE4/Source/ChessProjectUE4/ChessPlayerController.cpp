// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPlayerController.h"

#include "ChessBoard.h"


void AChessPlayerController::BeginPlay()
{
    if (auto world = GetWorld())
    {
        TArray<AActor*> foundActors;
        UGameplayStatics::GetAllActorsOfClass(world, AChessBoard::StaticClass(), foundActors);

        if (foundActors.Num() > 0)
        {
            SetViewTarget(foundActors[0]);
        }
    }
}

void AChessPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindKey(EKeys::M, IE_Released, this, &AChessPlayerController::testCamera);
}

void AChessPlayerController::testCamera()
{
    if (auto world = GetWorld())
    {
        TArray<AActor*> foundActors;
        UGameplayStatics::GetAllActorsOfClass(world, AChessBoard::StaticClass(), foundActors);

        if (foundActors.Num() > 0)
        {
            if (auto board = Cast<AChessBoard>(foundActors[0]))
            {
                static bool optionCamera = false;
                board->switchCamera(optionCamera);
                optionCamera = !optionCamera;
            }
        }
    }
}
