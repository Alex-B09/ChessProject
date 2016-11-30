// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessPiece.h"


// Sets default values
AChessPiece::AChessPiece()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PieceModel"));
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

