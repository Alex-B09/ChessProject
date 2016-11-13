// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

UCLASS()
class CHESSPROJECTUE4_API AChessPiece : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AChessPiece();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    // TODO Something special for battle...
    //      like when into battle
    //      or when charging
    //      or when diying

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Logic")
        int mMovementRange = 0;

    // Moral will represent the HP of the piece
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Logic")
        int mMorale = 10;
};
