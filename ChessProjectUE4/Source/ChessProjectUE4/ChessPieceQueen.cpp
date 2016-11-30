// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPieceQueen.h"

AChessPieceQueen::AChessPieceQueen()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> queen(TEXT("StaticMesh'/Game/Art/Pieces/queen.queen'"));

    if (queen.Object)
    {
        mMesh = queen.Object;
    }
}


