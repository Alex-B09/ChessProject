// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/StaticMeshComponent.h>

/**
 *
 */
class CHESSPROJECTUE4_API ChessTile
{
public:
    ChessTile(UStaticMeshComponent * tile, UStaticMeshComponent * selector)
        : mTile(tile)
        , mSelector(selector)
    {
    }

    void SetSelectorVisibility(bool isVisible);
    FVector GetGlobalPosition() const;
    FRotator GetGlobalRotation() const;

    bool isSameTile(UStaticMeshComponent * tile);
    void setShadowMesh(UStaticMesh * mesh);

private:
    UStaticMeshComponent * mTile;
    UStaticMeshComponent * mSelector;
    UStaticMeshComponent * mShadownMesh;
};
