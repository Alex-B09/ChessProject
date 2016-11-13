// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessBoard.h"


// Sets default values
AChessBoard::AChessBoard()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    mBoardSquares.SetNum(NB_SQUARES);
    //mBoardPieces.SetNum(NB_PIECES_PER_SIDE * 2); // TODO spawn actors at 0,0 maybe..or their respective squares?
}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AChessBoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

AChessSquare * AChessBoard::GetSquare(int col, int row)
{
    return nullptr;
}

AChessSquare * AChessBoard::GetSquareFromIndex(int index)
{
    return nullptr;
}
