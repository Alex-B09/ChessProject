// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "BoardLogic.h"

#include <memory>
#include "ChessProjectUE4GameMode.generated.h"

/**
 *
 */
UCLASS()
class CHESSPROJECTUE4_API AChessProjectUE4GameMode : public AGameModeBase
{
    GENERATED_BODY()

private:
    std::unique_ptr<BoardLogic> mBoardLogic;
    bool mIsWhiteTurn = true;

public:
    AChessProjectUE4GameMode();

    void StartPlay() override;
    void EndCurrentPlayerTurn();

private:
    AChessBoard * getChessBoard() const;

    void EndOfTurn();

    // set the pipeline to look at the right place
    void LookAtSide();
    void LookAtCenter();

};
