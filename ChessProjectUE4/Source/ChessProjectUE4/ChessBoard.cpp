// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessBoard.h"

#include <Components/StaticMeshComponent.h>

namespace
{
    UMaterial * blackCheckerMaterial = nullptr;
    UMaterial * whiteCheckerMaterial = nullptr;
    UStaticMesh * tileAsset = nullptr;
    UStaticMesh * selectorAsset = nullptr;
};


// Sets default values
AChessBoard::AChessBoard()
{
    PrimaryActorTick.bCanEverTick = true;
    mBoardSquares.SetNum(NB_SQUARES);

    // generate the squares
    const int NB_ROWS = 8;
    const int NB_COLS = 8;

    loadCheckerMaterial();

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Board"));
    }

    for (int rowId = 0; rowId < NB_ROWS; rowId++)
    {
        for (int colId = 0; colId < NB_COLS; colId++)
        {
            FString componentNameTile = "Tile_" + FString::FromInt(rowId) + "_" + FString::FromInt(colId);
            FString componentNameSelector = "Selector_" + FString::FromInt(rowId) + "_" + FString::FromInt(colId);

            auto tileActor = CreateDefaultSubobject<UStaticMeshComponent>(*componentNameTile);
            tileActor->SetupAttachment(RootComponent);
            tileActor->SetStaticMesh(tileAsset);

            auto selectorActor = CreateDefaultSubobject<UStaticMeshComponent>(*componentNameSelector);
            selectorActor->SetupAttachment(tileActor);
            selectorActor->SetStaticMesh(selectorAsset);
        }
    }
}


void AChessBoard::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    auto root = GetRootComponent();
    auto children = root->GetAttachChildren();
    bool isBlack = true;
    int column = 0;
    int row = 0;

    //const FVector SCALE = GetActorScale();

    const float TILE_SIZE_X = 200.f;
    const float TILE_SIZE_Y = 200.f;

    for (auto& child : children)
    {
        FVector location(row * TILE_SIZE_X, column * TILE_SIZE_Y, 10.f);
        FTransform relativeTransform;
        relativeTransform.SetLocation(location);
        child->AddLocalTransform(relativeTransform);

        if (auto mesh = Cast<UStaticMeshComponent>(child))
        {
            if (isBlack)
            {
                mesh->SetMaterial(0, blackCheckerMaterial);
            }
            else
            {
                mesh->SetMaterial(0, whiteCheckerMaterial);
            }
            isBlack = !isBlack;
        }
        ++column;

        if (column == 8)
        {
            column = 0;
            row++;
            isBlack = !isBlack;
        }

    }
}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
    Super::BeginPlay();
}

AChessSquare * AChessBoard::GetSquare(int col, int row)
{
    return nullptr;
}

AChessSquare * AChessBoard::GetSquareFromIndex(int index)
{
    return nullptr;
}

void AChessBoard::loadCheckerMaterial()
{
    static ConstructorHelpers::FObjectFinder<UMaterial> blackMaterial(TEXT("Material'/Game/Art/Board/Tile/CheckerBlack.CheckerBlack'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> whiteMaterial(TEXT("Material'/Game/Art/Board/Tile/CheckerWhite.CheckerWhite'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> staticTile(TEXT("StaticMesh'/Game/Art/Board/Tile/chessTile.chessTile'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> staticSelector(TEXT("StaticMesh'/Game/Art/Board/Tile/chessTileSelector.chessTileSelector'"));


    if (!whiteCheckerMaterial)
    {
        whiteCheckerMaterial = whiteMaterial.Object;
    }
    if (!blackCheckerMaterial)
    {
        blackCheckerMaterial = blackMaterial.Object;
    }
    if (!tileAsset)
    {
        tileAsset = staticTile.Object;
    }
    if (!selectorAsset)
    {
        selectorAsset = staticSelector.Object;
    }

}
