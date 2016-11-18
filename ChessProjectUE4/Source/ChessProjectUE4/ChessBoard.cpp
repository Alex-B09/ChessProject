// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessBoard.h"


// Sets default values
AChessBoard::AChessBoard()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    mBoardSquares.SetNum(NB_SQUARES);

    // generate the squares
    const int NB_TILES = 64;
    const int NB_ROWS = 8;
    const int NB_COLS = 8;
    const float TILE_SIZE_X = 400.f;
    const float TILE_SIZE_Y = 400.f;

    FString test1 = "Hello";
    test1.AppendInt(1);
    auto root = GetRootComponent();
    root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board"));

    for (int rowId = 0; rowId < NB_ROWS; rowId++)
    {
        for (int colId = 0; colId < NB_COLS; colId++)
        {
            FVector location(rowId * TILE_SIZE_X, colId * TILE_SIZE_Y, 10.f);
            FString componentName = "Tile_" + FString::FromInt(rowId) + "_" + FString::FromInt(colId);

            auto childActor = CreateDefaultSubobject<UChildActorComponent>(*componentName);
            childActor->SetChildActorClass(AChessSquare::StaticClass());
            childActor->RelativeLocation = location;

            childActor->SetupAttachment(root);
        }
    }
}


void AChessBoard::OnConstruction(const FTransform& Transform)
{
    auto root = GetRootComponent();
    auto children = root->GetAttachChildren();
    bool isBlack = true;
    for (auto& child : children)
    {
        if (auto childActor = Cast<UChildActorComponent>(child))
        {
            if (auto tile = Cast<AChessSquare>(childActor->GetChildActor()))
            {
                tile->SetCheckerMaterial(isBlack);
                isBlack = !isBlack;
            }
        }
    }

    int k = 0;
}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AChessBoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

AChessSquare * AChessBoard::GetSquare(int col, int row)
{
    return nullptr;
}

AChessSquare * AChessBoard::GetSquareFromIndex(int index)
{
    return nullptr;
}
