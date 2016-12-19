// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPiece.h"

namespace
{
    UMaterial * blackPieceMaterial = nullptr;
    UMaterial * whitePieceMaterial = nullptr;
    UMaterial * outlinerPieceMaterial = nullptr;
};

AChessPiece::AChessPiece(FString modelPathName)
{
    ConstructorHelpers::FObjectFinder<UStaticMesh> asset(*modelPathName);

    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PieceModel"));
        auto outliner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outliner"));
        if (outliner)
        {
            outliner->SetupAttachment(RootComponent);
        }
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
        if (auto modelComponent = getMeshRoot())
        {
            modelComponent->SetStaticMesh(mMesh);
            modelComponent->bRenderCustomDepth = true;

            if (auto outliner = getMeshOutliner())
            {
                outliner->SetStaticMesh(mMesh);

                const float SCALE = 1.02f;
                FTransform transform;
                transform.SetScale3D(FVector(SCALE, SCALE, SCALE));
                outliner->SetRelativeTransform(transform);
            }
        }
    }
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
    Super::BeginPlay();

    if (auto outliner = getMeshOutliner())
    {
        outliner->SetMaterial(0, outlinerPieceMaterial);
        outliner->SetVisibility(false); // to be safe -- not visible at start
    }
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

    static ConstructorHelpers::FObjectFinder<UMaterial> outlinerMaterial(TEXT("Material'/Game/Art/Pieces/OutlinerMaterial.OutlinerMaterial'"));


    if (blackMaterial.Object)
    {
        blackPieceMaterial = blackMaterial.Object;
    }

    if (whiteMaterial.Object)
    {
        whitePieceMaterial = whiteMaterial.Object;
    }

    if (outlinerMaterial.Object)
    {
        outlinerPieceMaterial = outlinerMaterial.Object;
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

void AChessPiece::setSelected(bool isSelected)
{
    if (auto outliner = getMeshOutliner())
    {
        outliner->SetVisibility(isSelected);
    }
}

UStaticMeshComponent * AChessPiece::getMeshRoot() const
{
    return Cast<UStaticMeshComponent>(RootComponent);
}

UStaticMeshComponent * AChessPiece::getMeshOutliner() const
{
    if (auto root = RootComponent)
    {
        return Cast<UStaticMeshComponent>(root->GetChildComponent(0));
    }
    return nullptr;
}

