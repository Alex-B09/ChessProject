// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPiecePawn.h"

AChessPiecePawn::AChessPiecePawn()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> pawn(TEXT("StaticMesh'/Game/Art/Pieces/pawn.pawn'"));

    if (pawn.Object)
    {
        mMesh = pawn.Object;
    }
}
