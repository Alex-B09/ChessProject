// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPlayerController.h"
#include "ChessProjectUE4GameMode.h"

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

    InputComponent->BindKey(EKeys::M, IE_Released, this, &AChessPlayerController::rotateCamera);
    InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AChessPlayerController::TestMouseClick);
}

void AChessPlayerController::rotateCamera()
{
    if (auto gameMode = Cast<AChessProjectUE4GameMode>(GetWorld()->GetAuthGameMode()))
    {
        gameMode->EndCurrentPlayerTurn();
    }
}

void AChessPlayerController::TestMouseClick()
{
    // Trace to see what is under the mouse cursor
    FHitResult hit;
    GetHitResultUnderCursor(ECC_Visibility, true, hit);

    auto test1 = hit.Component;
    auto test2 = hit.Distance;
    auto test3 = hit.Component;


    if (hit.bBlockingHit)
    {
        auto actorHit = hit.Actor;
        if (auto chessPiece = Cast<AChessPiece>(actorHit.Get()))
        {
            if (mSelectedPiece && mSelectedPiece != chessPiece)
            {
                mSelectedPiece->setSelected(false);
            }
            mSelectedPiece = chessPiece;
            mSelectedPiece->setSelected(true);

            if (auto chessMode = Cast<AChessProjectUE4GameMode>(GetWorld()->GetAuthGameMode()))
            {
                chessMode->ShowPieceMovement(mSelectedPiece);
            }

            UE_LOG(LogTemp, Warning, TEXT("Selected : %s"), *chessPiece->GetName());
        }
        else if (auto chessBoard = Cast<AChessBoard>(actorHit.Get()))
        {
            auto component = hit.Component;
            if (component.IsValid()) // to be on safe side
            {
                // if it is the selector
                if (auto parent = Cast<UStaticMeshComponent>(component->GetAttachParent()))
                {
                    component = parent;
                }

                if (component.IsValid() && mSelectedPiece)
                {
                    if (auto chessMode = Cast<AChessProjectUE4GameMode>(GetWorld()->GetAuthGameMode()))
                    {
                        chessMode->playTurn(mSelectedPiece, Cast<UStaticMeshComponent>(component.Get()));
                    }
                }
            }
        }
    }
}
