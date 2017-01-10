// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessProjectUE4.h"
#include "EditorRessourceBank.h"

#include <algorithm>

EditorRessourceBank * EditorRessourceBank::mSingleton = nullptr;

namespace
{
    template <class C, class I>
    void AddElement(std::vector<std::pair<I, C>> & toAddInto, I key, FString path)
    {
        ConstructorHelpers::FObjectFinder<std::remove_pointer<C>::type> element(*path);

        if (element.Succeeded())
        {
            toAddInto.push_back({ key, element.Object });
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid : %s"), *path);
        }
    }
}

EditorRessourceBank::EditorRessourceBank()
{
    // must be done in constructor... to test later on
    AddElement(mBlueprints, RessourceBlueprints::PIECE_PAWN, FString("Material'/Game/Blueprints/Pieces/BP_Pawn'"));
    AddElement(mBlueprints, RessourceBlueprints::PIECE_ROOK, FString("Material'/Game/Blueprints/Pieces/BP_Rook'"));
    AddElement(mBlueprints, RessourceBlueprints::PIECE_KNIGHT, FString("Material'/Game/Blueprints/Pieces/BP_Knight'"));
    AddElement(mBlueprints, RessourceBlueprints::PIECE_BISHOP, FString("Material'/Game/Blueprints/Pieces/BP_Bishop'"));
    AddElement(mBlueprints, RessourceBlueprints::PIECE_QUEEN, FString("Material'/Game/Blueprints/Pieces/BP_Queen'"));
    AddElement(mBlueprints, RessourceBlueprints::PIECE_KING, FString("Material'/Game/Blueprints/Pieces/BP_King'"));
}

EditorRessourceBank::~EditorRessourceBank()
{
}

UBlueprint* EditorRessourceBank::GetBlueprintRessource(RessourceBlueprints type)
{
    auto & blueprints = mSingleton->mBlueprints;

    auto findByType = [type](std::pair<RessourceBlueprints, UBlueprint*> elem)
    {
        return elem.first == type;
    };

    auto result = std::find_if(blueprints.cbegin(), blueprints.cend(), findByType);

    if (result != blueprints.cend())
    {
        return (*result).second;
    }
    return nullptr;
}
