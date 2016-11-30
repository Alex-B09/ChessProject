// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPieceBishop.h"

AChessPieceBishop::AChessPieceBishop()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> bishop(TEXT("StaticMesh'/Game/Art/Pieces/bishop.bishop'"));

    if (bishop.Object)
    {
        mMesh = bishop.Object;
    }
}


