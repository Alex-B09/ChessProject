// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "ChessPiece.h"

#include "ChessSquare.generated.h"

UCLASS()
class CHESSPROJECTUE4_API AChessSquare : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AChessSquare();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    AChessPiece * GetPiece() const;
    void SetPiece(AChessPiece * piece);

    // TODO check if usefull to put in engine
    void TriggerSelectorVisibility(bool visibility);

    void SetCheckerMaterial(bool isBlack);

private:
    UPROPERTY(VisibleAnywhere, Category = "Gameplay")
        AChessPiece * mPiece;    // no ownership here

    UPROPERTY(EditAnywhere, Category = "Gameplay")
        UStaticMeshComponent * mSquareMesh;

    UPROPERTY(EditAnywhere, Category = "Gameplay")
        UStaticMeshComponent * mSelectorMesh;
};
