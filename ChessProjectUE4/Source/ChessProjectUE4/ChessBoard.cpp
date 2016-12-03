// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessBoard.h"

#include "ChessPiecePawn.h"
#include "ChessPieceRook.h"
#include "ChessPieceKnight.h"
#include "ChessPieceBishop.h"
#include "ChessPieceQueen.h"
#include "ChessPieceKing.h"

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
    LoadCheckerMaterial();
    SetupComponents();
}

void AChessBoard::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    CreateBoardLayout();

    mPiecesPlacement.SetNum(NB_SQUARES);
}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
    Super::BeginPlay();
    CreateTiles();

    for (auto & tile : mTiles)
    {
        tile.SetSelectorVisibility(false);
    }

    // set pieces to right spot
    for (int i = 0; i < NB_SQUARES; ++i)
    {
        AChessPiece * chessPiece = nullptr;
        int currentPlacement = mPiecesPlacement[i];
        int currentPiece = currentPlacement % 10;
        bool isBlack = currentPlacement > 10;

        auto currentTile = mTiles[i];

        auto spawnPosition = currentTile.GetGlobalPosition() + FVector(0.f, 0.f, 20.f);
        auto spawnRotation = currentTile.GetGlobalRotation();

        if (isBlack)
        {
            // personal note : if there is no values associated with Roll/Pitch/Yah,
            //                  there will be garbage values
            FRotator additionalRotation(0.f, 180.f, 0.f);
            spawnRotation += additionalRotation;
        }

        switch (currentPiece)
        {
        case 0:
            // nothing
            break;
        case PAWN:
            chessPiece = GetWorld()->SpawnActor<AChessPiecePawn>(spawnPosition, spawnRotation);
            break;
        case ROOK:
            chessPiece = GetWorld()->SpawnActor<AChessPieceRook>(spawnPosition, spawnRotation);
            break;
        case KNIGHT:
            chessPiece = GetWorld()->SpawnActor<AChessPieceKnight>(spawnPosition, spawnRotation);
            break;
        case BISHOP:
            chessPiece = GetWorld()->SpawnActor<AChessPieceBishop>(spawnPosition, spawnRotation);
            break;
        case QUEEN:
            chessPiece = GetWorld()->SpawnActor<AChessPieceQueen>(spawnPosition, spawnRotation);
            break;
        case KING:
            chessPiece = GetWorld()->SpawnActor<AChessPieceKing>(spawnPosition, spawnRotation);
            break;
        default:
            break;
        }

        if (chessPiece)
        {
            chessPiece->setMaterial(isBlack);
        }
    }
}

void AChessBoard::LoadCheckerMaterial()
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

void AChessBoard::CreateBoardLayout()
{
    auto root = GetRootComponent();
    auto children = root->GetAttachChildren();
    bool isBlack = true;
    int column = 0;
    int row = 0;

    //selector location
    FTransform transform;
    transform.SetScale3D(FVector(1.5f, 1.5f, 1.f));
    transform.SetLocation(FVector(0.f, 0.f, 25.f));

    const float TILE_SIZE_X = 400.f;
    const float TILE_SIZE_Y = 400.f;

    for (auto& child : children)
    {
        if (auto selector = child->GetChildComponent(0))
        {
            selector->SetRelativeTransform(transform);
        }

        FVector location(row * TILE_SIZE_X, column * TILE_SIZE_Y, 0.f);
        child->SetRelativeLocation(location);

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

void AChessBoard::CreateTiles()
{
    mTiles.RemoveAll([](ChessTile &)
    {
        return true;
    });

    auto root = GetRootComponent();
    auto children = root->GetAttachChildren();

    for (auto child : children)
    {
        if (auto tile = Cast<UStaticMeshComponent>(child))
        {
            if (auto selector = Cast<UStaticMeshComponent>(tile->GetChildComponent(0)))
            {
                mTiles.Add({ tile, selector });
            }
        }
    }
}

void AChessBoard::SetupComponents()
{
    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Board"));
    }

    const int ROWS = 8;
    const int COLS = 8;
    for (int rowId = 0; rowId < ROWS; rowId++)
    {
        for (int colId = 0; colId < COLS; colId++)
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
