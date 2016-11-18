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
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    mSquareMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
    mSelectorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Selector"));

    if (tileAsset)
    {
        mSquareMesh->SetStaticMesh(tileAsset);
        mSquareMesh->SetupAttachment(RootComponent);
        if (mSelectorMesh)
        {
            mSelectorMesh->SetStaticMesh(selectorAsset);
            mSelectorMesh->SetupAttachment(RootComponent);

            FTransform relativeTransform;
            relativeTransform.SetLocation(FVector(-200.f, -200.f, 35.f)); // hack
            relativeTransform.SetScale3D(FVector(.9f, 0.9f, .65f));

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
    static ConstructorHelpers::FObjectFinder<UMaterial> blackMaterial(TEXT("Material'/Game/Art/Board/Tile/CheckerBlack.CheckerBlack'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> whiteMaterial(TEXT("Material'/Game/Art/Board/Tile/CheckerWhite.CheckerWhite'"));


    if (isBlack)
    {
        mSquareMesh->SetMaterial(0, blackMaterial.Object);
    }
    else
    {
        mSquareMesh->SetMaterial(0, whiteMaterial.Object);
    }
}
