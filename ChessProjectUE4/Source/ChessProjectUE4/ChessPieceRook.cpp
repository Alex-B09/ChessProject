// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPieceRook.h"


AChessPieceRook::AChessPieceRook()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> rook(TEXT("StaticMesh'/Game/Art/Pieces/rook.rook'"));

    if (rook.Object)
    {
        mMesh = rook.Object;
    }
}
