// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

UENUM(BlueprintType)
enum class EPieces : uint8
{
    PE_PAWN         UMETA(DisplayName = "Pawn"),
    PE_ROOK         UMETA(DisplayName = "Rook"),
    PE_KNIGHT       UMETA(DisplayName = "Knight"),
    PE_BISHOP       UMETA(DisplayName = "Bishop"),
    PE_QUEEN        UMETA(DisplayName = "Queen"),
    PE_KING         UMETA(DisplayName = "King"),
};
