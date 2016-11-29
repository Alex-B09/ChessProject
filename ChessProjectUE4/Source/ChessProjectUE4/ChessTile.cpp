// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessTile.h"

void ChessTile::SetSelectorVisibility(bool isVisible)
{
    mSelector->SetVisibility(isVisible);
}
