// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPieceKnight.h"

AChessPieceKnight::AChessPieceKnight()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> knight(TEXT("StaticMesh'/Game/Art/Pieces/knight.knight'"));

    if (knight.Object)
    {
        mMesh = knight.Object;
    }
}

