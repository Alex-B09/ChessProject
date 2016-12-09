// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"

#include "ChessPiece.h"

#include "ChessPlayerController.generated.h"

/**
 *
 */
UCLASS()
class CHESSPROJECTUE4_API AChessPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    void SetupInputComponent() override;

private:
    void testCamera();
    void TestMouseClick();

    AChessPiece * mSelectedPiece = nullptr;
};
