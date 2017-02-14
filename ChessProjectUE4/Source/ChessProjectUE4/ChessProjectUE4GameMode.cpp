// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessProjectUE4GameMode.h"
#include "ChessBoard.h"
#include "EditorRessourceBank.h"


#include "ChessPlayerController.h"
#include "EngineUtils.h"

AChessProjectUE4GameMode::AChessProjectUE4GameMode()
{
    PlayerControllerClass = AChessPlayerController::StaticClass();
    EditorRessourceBank::CreateSingleton();
}

void AChessProjectUE4GameMode::StartPlay()
{
    if (auto board = getChessBoard())
    {
        mBoardLogic = std::make_unique<BoardLogic>(board, GetWorld());
    }

    Super::StartPlay();
}

AChessBoard * AChessProjectUE4GameMode::getChessBoard() const
{
    AChessBoard * board = nullptr;
    if (auto world = GetWorld())
    {
        TArray<AActor*> foundActors;
        UGameplayStatics::GetAllActorsOfClass(world, AChessBoard::StaticClass(), foundActors);

        if (foundActors.Num() > 0)
        {
            board = Cast<AChessBoard>(foundActors[0]);
        }
    }

    if (!board)
    {
        UE_LOG(LogTemp, Warning, TEXT("AChessProjectUE4GameMode::getChessBoard() board not found"));
    }
    return board;
}

void AChessProjectUE4GameMode::EndCurrentPlayerTurn()
{
    mIsWhiteTurn = !mIsWhiteTurn;

    if (mIsWhiteTurn)
    {
        EndOfTurn();
    }
    LookAtSide();
}

void AChessProjectUE4GameMode::EndOfTurn()
{
    // TODO
    // this is where we will move the pieces
}

void AChessProjectUE4GameMode::LookAtSide()
{
    if (auto board = getChessBoard())
    {
        board->switchCamera(mIsWhiteTurn);
    }
}

void AChessProjectUE4GameMode::LookAtCenter()
{
    // TODO
    // set camera from the middle to see the moves
}

bool AChessProjectUE4GameMode::playTurn(AChessPiece * piece, UStaticMeshComponent* destination)
{
    bool isMoveValid = false;
    if (piece->IsWhite() == mIsWhiteTurn)
    {
        if (auto tile = mBoardLogic->getChessTileFromComponent(destination))
        {
            isMoveValid = mBoardLogic->MovePiece(piece, tile);
        }
    }
    return isMoveValid;
}

void AChessProjectUE4GameMode::ShowPiecePossibleMovement(AChessPiece * piece)
{
    mBoardLogic->HighlingPossiblePlacement(piece);
}

bool AChessProjectUE4GameMode::IsWhiteTurn() const
{
    return mIsWhiteTurn;
}

