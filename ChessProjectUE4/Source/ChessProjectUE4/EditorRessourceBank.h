// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>
#include <vector>

/**
 *
 */
class CHESSPROJECTUE4_API EditorRessourceBank
{
    EditorRessourceBank();
    ~EditorRessourceBank();

    // i dont want anything to do with copy of any sorts
    EditorRessourceBank(const EditorRessourceBank &) = delete;
    EditorRessourceBank & operator= (const EditorRessourceBank &) = delete;

public:
    enum class RessourceMaterials
    {

    };

    enum class RessourceMeshes
    {

    };

    enum class RessourceBlueprints
    {
        PIECE_PAWN = 0,
        PIECE_ROOK,
        PIECE_KNIGHT,
        PIECE_BISHOP,
        PIECE_QUEEN,
        PIECE_KING
    };

    static UBlueprint* GetBlueprintRessource(RessourceBlueprints type);

    static void CreateSingleton() // control creation time
    {
        static EditorRessourceBank bank; // no need to delete since its a "local" static variable
        if (!mSingleton)
        {
            mSingleton = &bank;
        }
    }

private:
    static EditorRessourceBank * mSingleton;

    std::vector<std::pair<RessourceBlueprints, UBlueprint*>> mBlueprints;
};
