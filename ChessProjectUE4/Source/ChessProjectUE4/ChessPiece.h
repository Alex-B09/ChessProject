// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "ChessProjectUE4.h"

#include "GameFramework/PawnMovementComponent.h"

#include "ChessPiece.generated.h"

UCLASS()
class CHESSPROJECTUE4_API AChessPiece : public APawn
{
    GENERATED_BODY()

public:
    AChessPiece();

    void OnConstruction(const FTransform& Transform) override;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    // TODO Something special for battle...
    //      like when into battle
    //      or when charging
    //      or when diying

    void setMaterial(bool isBlack);
    void setSelected(bool isSelected);

    int GetMovementValue() const;
private:
    void loadMaterials();

    UStaticMeshComponent * getMeshRoot() const;
    UStaticMeshComponent * getMeshOutliner() const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Logic")
        UStaticMesh * mPieceMesh = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Logic")
        int mMovementRange = 0;

    // Moral will represent the HP of the piece
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Logic")
        int mMorale = 10;

    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Logic")
        EPieces mPieceType;

    ///** Movement component used for movement logic in various movement modes (walking, falling, etc), containing relevant settings and functions to control movement. */
    //UPROPERTY(Category = "Movement", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    //    UPawnMovementComponent* mPieceMovement;
};
