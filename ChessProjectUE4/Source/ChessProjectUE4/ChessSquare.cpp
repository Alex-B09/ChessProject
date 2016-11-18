// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessSquare.h"


// Sets default values
AChessSquare::AChessSquare()
    :mPiece(nullptr)
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> staticTile(TEXT("StaticMesh'/Game/Art/Board/Tile/chessTile.chessTile'"));
    UStaticMesh * tileAsset = staticTile.Object;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> staticSelector(TEXT("StaticMesh'/Game/Art/Board/Tile/chessTileSelector.chessTileSelector'"));
    UStaticMesh * selectorAsset = staticSelector.Object;

    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    mSquareMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
    mSelectorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Selector"));

    auto root = GetRootComponent();
    root = mSquareMesh;

    if (tileAsset)
    {
        mSquareMesh->SetStaticMesh(tileAsset);
        if (mSelectorMesh)
        {
            mSelectorMesh->SetStaticMesh(selectorAsset);
            mSelectorMesh->SetupAttachment(root);
            mSelectorMesh->AddLocalOffset(FVector(-200.f, -200.f, 35.f)); // hack
            mSelectorMesh->SetWorldScale3D(FVector(1.0f, 1.0f, .75f));
        }
    }
}

// Called when the game starts or when spawned
void AChessSquare::BeginPlay()
{
    Super::BeginPlay();
}

AChessPiece * AChessSquare::GetPiece() const
{
    return mPiece;
}

void AChessSquare::SetPiece(AChessPiece * piece)
{
    mPiece = piece;
}

// TODO check if usefull to put in engine
void AChessSquare::TriggerSelectorVisibility(bool visibility)
{
    if (mSelectorMesh)
    {
        // TODO
    }
}
