// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChessSquare.h"
#include "ChessPiece.h"

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


public:
    // Sets default values for this actor's properties
    AChessBoard();

    virtual void OnConstruction(const FTransform& Transform) override;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintPure, Category = "Board")
        AChessSquare * GetSquare(int col, int row);

    UFUNCTION(BlueprintPure, Category = "Board")
        AChessSquare * GetSquareFromIndex(int index);

private:
    UPROPERTY(VisibleAnywhere, Category = "Board")
        TArray<AChessSquare*> mBoardSquares;

    // commented for now...i'm not planing using anything dynamics for a long time
    UPROPERTY(VisibleAnywhere, Category = "Board")
        TArray<AChessPiece*> mBoardPieces;      // the owner of the all the pieces

    const int NB_SQUARES = 64;
    const int NB_PIECES_PER_SIDE = 16;
};
