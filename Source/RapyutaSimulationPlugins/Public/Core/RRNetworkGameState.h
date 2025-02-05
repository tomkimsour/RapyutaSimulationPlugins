/**
 * @file RRNetworkGameState.h
 * @todo add doc
 * @copyright Copyright 2020-2022 Rapyuta Robotics Co., Ltd.
 */
#pragma once

// UE
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"

#include "RRNetworkGameState.generated.h"

/**
 * @brief Network Game State for client-server
 * @sa [GameMode and GameState](https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/Framework/GameMode/
 */
UCLASS()
class RAPYUTASIMULATIONPLUGINS_API ARRNetworkGameState : public AGameState
{
    GENERATED_BODY()

public:
    ARRNetworkGameState();

    /**
     * @brief Get the Server World Time Seconds object
     * 
     * @return float 
     */
    virtual float GetServerWorldTimeSeconds() const override;
};
