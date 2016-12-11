// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessTile.h"

void ChessTile::SetSelectorVisibility(bool isVisible)
{
    if (mSelector)
    {
        mSelector->SetVisibility(isVisible);
    }
}

FVector ChessTile::GetGlobalPosition() const
{
    return mTile->GetComponentLocation();
}

FRotator ChessTile::GetGlobalRotation() const
{
    return mTile->GetComponentRotation();
}
