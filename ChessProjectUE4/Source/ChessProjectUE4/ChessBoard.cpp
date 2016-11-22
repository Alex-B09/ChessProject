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
    const int NB_ROWS = 8;
    const int NB_COLS = 8;
    const float TILE_SIZE_X = 410.f;
    const float TILE_SIZE_Y = 410.f;

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Board"));
    }

    for (int rowId = 0; rowId < NB_ROWS; rowId++)
    {
        for (int colId = 0; colId < NB_COLS; colId++)
        {
            FVector location(rowId * TILE_SIZE_X, colId * TILE_SIZE_Y, 10.f);
            FString componentName = "Tile_" + FString::FromInt(rowId) + "_" + FString::FromInt(colId);

            auto childActor = CreateDefaultSubobject<UChildActorComponent>(*componentName);
            childActor->SetChildActorClass(AChessSquare::StaticClass());
            childActor->SetupAttachment(RootComponent);

        }
    }
}


void AChessBoard::OnConstruction(const FTransform& Transform)
{
    auto root = GetRootComponent();
    auto children = root->GetAttachChildren();
    bool isBlack = true;
    int column = 0;
    int row = 0;

    const FVector SCALE = GetActorScale();

    const float TILE_SIZE_X = 200.f * SCALE.X;
    const float TILE_SIZE_Y = 200.f * SCALE.Y;

    for (auto& child : children)
    {
        if (auto childActor = Cast<UChildActorComponent>(child))
        {
            if (!childActor->GetChildActor())
            {
                childActor->CreateChildActor();
            }

            FVector location(row * TILE_SIZE_X, column * TILE_SIZE_Y, 10.f);
            FTransform relativeTransform;
            relativeTransform.SetLocation(location);
            childActor->AddLocalTransform(relativeTransform);

            if (auto tile = Cast<AChessSquare>(childActor->GetChildActor()))
            {
                tile->SetCheckerMaterial(isBlack);
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
