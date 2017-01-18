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
    LoadCheckerMaterial();
    SetupComponents();
}

void AChessBoard::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    CreateBoardLayout();
    ComputeCameraSettings();

    mPiecesPlacement.SetNum(mNbTiles);
}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
    Super::BeginPlay();
    ComputeCameraSettings();
}

void AChessBoard::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (mIsSwitchingCamera)
    {
        auto springArm = GetSpringArm();
        auto location = springArm->GetRelativeTransform().GetLocation();
        auto rotation = springArm->RelativeRotation;

        mTimeSwitching += (DeltaSeconds / 3); // a bit slower 
        auto newRotation = FMath::Lerp(rotation, mTargetLookAtRotation, mTimeSwitching);
        auto newLocation = FMath::Lerp(location, mTargetLookAtLocation, mTimeSwitching);

        springArm->SetRelativeLocationAndRotation(newLocation, newRotation);

        if (mTimeSwitching >= 1.0f)
        {
            mIsSwitchingCamera = false;
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

int AChessBoard::getNbTiles()const
{
    return mNbTiles;
}

TArray<int> AChessBoard::getPiecesPlacement() const
{
    return mPiecesPlacement;
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

    auto springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
    auto camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    if (springArm && camera)
    {
        springArm->SetupAttachment(RootComponent);
        camera->SetupAttachment(springArm);
    }
}

void AChessBoard::ComputeCameraSettings()
{
    ComputeCameraLocation();

    auto child = GetSpringArm();

    if (auto springArm = Cast<USpringArmComponent>(child))
    {
        springArm->SetRelativeLocation(mCurrentLookAtLocation);
        springArm->bAbsoluteRotation = true; // Don't want arm to rotate when character does
        springArm->TargetArmLength = 3000.f;
        springArm->SetRelativeRotation(mCurrentLookAtRotation);
        springArm->bDoCollisionTest = false; // Don't want to pull camera in when collides with level

        if (auto camera = Cast<UCameraComponent>(springArm->GetChildComponent(0)))
        {
            camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
        }
    }
}

void AChessBoard::ComputeCameraLocation()
{
    //get Position of 35th element and 26th element
    auto root = RootComponent;

    auto firstChild = root->GetChildComponent(27);
    auto secondChild = root->GetChildComponent(36);

    auto firstChildLocation = firstChild->GetRelativeTransform().GetLocation();
    auto secondChildLocation = secondChild->GetRelativeTransform().GetLocation();

    FVector averageLocation = (firstChildLocation + secondChildLocation) / 2;

    mCenterLocation = averageLocation;

    FVector whiteDelta(-400.f, 0.f, 0.f);
    mWhiteLookAtLocation = mCenterLocation + whiteDelta;

    FVector blackDelta(400.f, 0.f, 0.f);
    mBlackLookAtLocation = mCenterLocation + blackDelta;

    FVector middleDelta(0.f, 400.f, 0.f); // check if -400 or 400
    mMiddleLookAtLocation = mCenterLocation + middleDelta;

    mWhiteLookAtRotation = FRotator(0.f, 0.f, 0.f) + FRotator(-45.f, 0.f, 0.f);
    mBlackLookAtRotation = FRotator(0.f, 180.f, 0.f) + FRotator(-45.f, 0.f, 0.f);
    mMiddleLookAtRotation = FRotator(0.f, 270.f, 0.f) + FRotator(-45.f, 0.f, 0.f);

    mCurrentLookAtLocation = mWhiteLookAtLocation;
    mCurrentLookAtRotation = mWhiteLookAtRotation;
}

void AChessBoard::switchCamera(bool lookingWhite)
{
    if (lookingWhite)
    {
        mTargetLookAtRotation = mWhiteLookAtRotation;
        mTargetLookAtLocation = mWhiteLookAtLocation;
    }
    else
    {
        mTargetLookAtRotation = mBlackLookAtRotation;
        mTargetLookAtLocation = mBlackLookAtLocation;
    }
    mTimeSwitching = 0.0f;
    mIsSwitchingCamera = true;
}

void AChessBoard::setCameraMiddle()
{
    mTargetLookAtRotation = mMiddleLookAtRotation;
    mTargetLookAtLocation = mMiddleLookAtLocation;

    mTimeSwitching = 0.0f;
    mIsSwitchingCamera = true;
}

USpringArmComponent * AChessBoard::GetSpringArm()
{
    return Cast<USpringArmComponent>(RootComponent->GetChildComponent(mNbTiles));
}

