// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "ChessProjectUE4GameMode.h"

#include "ChessPlayerController.h"

AChessProjectUE4GameMode::AChessProjectUE4GameMode()
{
    PlayerControllerClass = AChessPlayerController::StaticClass();
}

