/**
 * @file RRROS2ActorsRvizMarkerPublisher.h
 * @brief Rviz marker array publisher class.
 * @copyright Copyright 2020-2022 Rapyuta Robotics Co., Ltd.
 */

#pragma once

// UE
#include "CoreMinimal.h"

// rclUE
#include "Msgs/ROS2MarkerArray.h"
#include "ROS2Publisher.h"

#include "RRROS2ActorsRvizMarkerPublisher.generated.h"

class AROS2Node;

/**
 * @brief SRviz marker array publisher class. This class publishes are markers for given actors.
 * Expected to create child class in BP/C++ to set marker params and actor class.
 */
UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class RAPYUTASIMULATIONPLUGINS_API URRROS2ActorsRvizMarkerPublisher : public UROS2Publisher
{
    GENERATED_BODY()

public:
    /**
    * @brief Construct a new URRROS2ActorsRvizMarkerPublisher object
    *
    */
    URRROS2ActorsRvizMarkerPublisher();

    //! Actor class name
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ActorClass;

    //! List of Actors whose pose are published as marker
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<AActor*> Actors;

    //! Marker pose become relative pose from this Actor.
    //! If it is nullptr, simply use world origin.
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    AActor* ReferenceActor = nullptr;

    //! Update Actors with GetAllActorsOfClass or not in UpdateMessages
    //! Enable this may cause delay since GetAllActorsOfClass is slow operation.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUpdateActorsList = false;

    //! Common parameters among Markers
    //! Parameters are used from this one except for name and pose.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FROSMarker BaseMarker;

    void InitializeWithROS2(AROS2Node* InROS2Node) override;
    void UpdateMessage(UROS2GenericMsg* InMessage) override;
};
