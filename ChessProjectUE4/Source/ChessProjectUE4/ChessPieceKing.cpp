// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPieceKing.h"


AChessPieceKing::AChessPieceKing()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> king(TEXT("StaticMesh'/Game/Art/Pieces/king.king'"));

    if (king.Object)
    {
        mMesh = king.Object;
    }
}

