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

public:
    AChessProjectUE4GameMode();

    void StartPlay() override;

private:
    AChessBoard * getChessBoard() const;
};
