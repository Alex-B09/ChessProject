// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessSquare.h"

namespace
{
    UMaterial * blackCheckerMaterial = nullptr;
    UMaterial * whiteCheckerMaterial = nullptr;
};

// Sets default values
AChessSquare::AChessSquare()
    :mPiece(nullptr)
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> staticTile(TEXT("StaticMesh'/Game/Art/Board/Tile/chessTile.chessTile'"));
    UStaticMesh * tileAsset = staticTile.Object;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> staticSelector(TEXT("StaticMesh'/Game/Art/Board/Tile/chessTileSelector.chessTileSelector'"));
    UStaticMesh * selectorAsset = staticSelector.Object;

    static ConstructorHelpers::FObjectFinder<UMaterial> blackMaterial(TEXT("Material'/Game/Art/Board/Tile/CheckerBlack.CheckerBlack'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> whiteMaterial(TEXT("Material'/Game/Art/Board/Tile/CheckerWhite.CheckerWhite'"));


    if (!whiteCheckerMaterial)
    {
        whiteCheckerMaterial = whiteMaterial.Object;
    }
    if (!blackCheckerMaterial)
    {
        blackCheckerMaterial = blackMaterial.Object;
    }

    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    }
    if (!mSquareMesh)
    {
        mSquareMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
    }
    if (!mSelectorMesh)
    {
        mSelectorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Selector"));
    }

    if (tileAsset)
    {
        mSquareMesh->SetStaticMesh(tileAsset);
        mSquareMesh->SetupAttachment(RootComponent);
        if (mSelectorMesh)
        {
            mSelectorMesh->SetStaticMesh(selectorAsset);
            mSelectorMesh->SetupAttachment(mSquareMesh);

            FTransform relativeTransform;
            relativeTransform.SetLocation(FVector(-200.f, -200.f, 35.f)); // hack
            relativeTransform.SetScale3D(FVector(1.f, 1.f, .65f));

            mSelectorMesh->AddLocalTransform(relativeTransform);
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

void AChessSquare::SetCheckerMaterial(bool isBlack)
{
    if (isBlack)
    {
        mSquareMesh->SetMaterial(0, blackCheckerMaterial);
    }
    else
    {
        mSquareMesh->SetMaterial(0, whiteCheckerMaterial);
    }
}
