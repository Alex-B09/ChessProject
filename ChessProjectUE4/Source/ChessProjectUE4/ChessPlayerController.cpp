// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPlayerController.h"

#include "ChessBoard.h"
#include "ChessPiece.h"


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

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

void AChessPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindKey(EKeys::M, IE_Released, this, &AChessPlayerController::testCamera);
    InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AChessPlayerController::TestMouseClick);
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

void AChessPlayerController::TestMouseClick()
{
    // Trace to see what is under the mouse cursor
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit)
    {
        auto actorHit = Hit.Actor;
        if (auto chessPiece = Cast<AChessPiece>(actorHit.Get()))
        {
            UE_LOG(LogTemp, Warning, TEXT("%s"), *chessPiece->GetName());
        }
    }
}
