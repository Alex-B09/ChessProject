// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChessPiece.h"
#include "ChessTile.h"

#include "ChessBoard.generated.h"

UCLASS()
class CHESSPROJECTUE4_API AChessBoard : public AActor
{
    GENERATED_BODY()

        // The board will always be with the (queen) black rook piece at 0,0 (so top left)
        // and the (king) white rook at 7,7

        /*
        row :   0   1   2   3   4   5   6   7
        col 0   BR  Bk  BB  BQ  BK  BB  Bk  BR
        col 1   BP  BP  BP  BP  BP  BP  BP  BP
        col 2   E   E   E   E   E   E   E   E
        col 3   E   E   E   E   E   E   E   E
        col 4   E   E   E   E   E   E   E   E
        col 4   E   E   E   E   E   E   E   E
        col 6   WP  WP  WP  WP  WP  WP  WP  WP
        col 7   WR  Wk  WB  WQ  WK  WB  Wk  WR
        */

private:
    enum PiecesEnum
    {
        PAWN = 1,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    };

public:
    // Sets default values for this actor's properties
    AChessBoard();

    void OnConstruction(const FTransform& Transform) override;
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    void LoadCheckerMaterial();
    void CreateBoardLayout();
    void CreateTiles();
    void SetupComponents();
    void ComputeCameraSettings();
    void ComputeCameraLocation();

private:
    // commented for now...i'm not planing using anything dynamics for a long time
    UPROPERTY(VisibleAnywhere, Category = "Board")
        TArray<AChessPiece*> mBoardPieces;      // the owner of the all the pieces

    UPROPERTY(EditAnywhere, Category = "Board")
        TArray<int> mPiecesPlacement;      // where are the pieces

    FVector mCenterLocation;
    FVector mWhiteLookLocation;
    FVector mBlackLookLocation;

    FRotator mRotationWhite;
    FRotator mRotationBlack;

    const int NB_SQUARES = 64;
    TArray<ChessTile> mTiles;
};
