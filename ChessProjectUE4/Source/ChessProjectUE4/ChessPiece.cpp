// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPiece.h"

namespace
{
    UMaterial * blackPieceMaterial = nullptr;
    UMaterial * whitePieceMaterial = nullptr;
};

AChessPiece::AChessPiece(FString modelPathName)
{
    ConstructorHelpers::FObjectFinder<UStaticMesh> asset(*modelPathName);

    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PieceModel"));
    }

    loadMaterials();

    if (asset.Object)
    {
        mMesh = asset.Object;
    }
}

void AChessPiece::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (mMesh)
    {
        if (auto modelComponent = Cast<UStaticMeshComponent>(RootComponent))
        {
            modelComponent->SetStaticMesh(mMesh);
        }
    }
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AChessPiece::loadMaterials()
{
    static ConstructorHelpers::FObjectFinder<UMaterial> blackMaterial(TEXT("Material'/Game/Art/Pieces/PieceBlack.PieceBlack'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> whiteMaterial(TEXT("Material'/Game/Art/Pieces/PieceWhite.PieceWhite'"));

    if (blackMaterial.Object)
    {
        blackPieceMaterial = blackMaterial.Object;
    }

    if (whiteMaterial.Object)
    {
        whitePieceMaterial = whiteMaterial.Object;
    }
}

void AChessPiece::setMaterial(bool isBlack)
{
    UMaterial * mat = nullptr;
    if (isBlack)
    {
        mat = blackPieceMaterial;
    }
    else
    {
        mat = whitePieceMaterial;
    }

    if (auto modelComponent = Cast<UStaticMeshComponent>(RootComponent))
    {
        modelComponent->SetMaterial(0, mat);
    }
}

