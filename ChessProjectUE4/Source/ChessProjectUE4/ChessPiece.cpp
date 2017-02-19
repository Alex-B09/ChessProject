// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPiece.h"

#include "PieceMovementComponent.h"

namespace
{
    UMaterial * blackPieceMaterial = nullptr;
    UMaterial * whitePieceMaterial = nullptr;
};

AChessPiece::AChessPiece()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PieceModel"));

        if (auto movement = CreateDefaultSubobject<UPieceMovementComponent>(TEXT("Movement")))
        {
            movement->UpdatedComponent = RootComponent;
            movement->Velocity = FVector(50.f, 50.f, 0.f);
        }
    }

    loadMaterials();
}

void AChessPiece::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (mPieceMesh)
    {
        if (auto modelComponent = getMeshRoot())
        {
            modelComponent->SetStaticMesh(mPieceMesh);
            modelComponent->SetRenderCustomDepth(false);
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

    if (auto modelComponent = getMeshRoot())
    {
        modelComponent->SetMaterial(0, mat);
    }
}

int AChessPiece::GetMovementValue() const
{
    return mMovementRange;
}

void AChessPiece::setSelected(bool isSelected)
{
    if (auto outliner = getMeshRoot())
    {
        outliner->SetRenderCustomDepth(isSelected);
    }
}

UStaticMeshComponent * AChessPiece::getMeshRoot() const
{
    return Cast<UStaticMeshComponent>(RootComponent);
}

bool AChessPiece::IsWhite()const
{
    return mIsWhite;
}

void AChessPiece::setIsWhite(bool isWhite)
{
    mIsWhite = isWhite;
    setMaterial(!isWhite);
}

