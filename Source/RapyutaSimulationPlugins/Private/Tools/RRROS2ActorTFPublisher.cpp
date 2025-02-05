// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#include "Tools/RRROS2ActorTFPublisher.h"

// RapyutaSimulationPlugins
#include "Core/RRUObjectUtils.h"

void URRROS2ActorTFPublisher::InitializeWithROS2(AROS2Node* InROS2Node)
{
    Super::InitializeWithROS2(InROS2Node);

    // register delegates to node
    FServiceCallback TriggerPublishSrvCallback;
    TriggerPublishSrvCallback.BindDynamic(this, &URRROS2ActorTFPublisher::TriggerPublishSrv);
    InROS2Node->AddServiceServer(TriggerServiceName, UROS2SetBoolSrv::StaticClass(), TriggerPublishSrvCallback);
}

void URRROS2ActorTFPublisher::TriggerPublishSrv(UROS2GenericSrv* Service)
{
    UROS2SetBoolSrv* TriggerPublishService = Cast<UROS2SetBoolSrv>(Service);

    FROSSetBoolReq Request;
    TriggerPublishService->GetRequest(Request);
    if (Request.bData)
    {
        StartPublishTimer();
    }
    else
    {
        StopPublishTimer();
    }

    FROSSetBoolRes Response;
    Response.bSuccess = true;
    TriggerPublishService->SetResponse(Response);
}

void URRROS2ActorTFPublisher::BeginPlay()
{
    Super::BeginPlay();
}

void URRROS2ActorTFPublisher::SetReferenceActorByName(const FString& InName)
{
    ReferenceActor = URRUObjectUtils::FindActorByName<AActor>(GetWorld(), InName);
    ReferenceActorName = InName;
}

void URRROS2ActorTFPublisher::SetReferenceActorByActor(AActor* InActor)
{
    ReferenceActor = InActor;
    ReferenceActorName = ReferenceActor->GetName();
}

void URRROS2ActorTFPublisher::SetTargetActorByName(const FString& InName)
{
    TargetActor = URRUObjectUtils::FindActorByName<AActor>(GetWorld(), InName);
    TargetActorName = InName;
}

void URRROS2ActorTFPublisher::SetTargetActorByActor(AActor* InActor)
{
    TargetActor = InActor;
    TargetActorName = TargetActor->GetName();
}

void URRROS2ActorTFPublisher::UpdateMessage(UROS2GenericMsg* InMessage)
{
    if (TargetActor == nullptr)
    {
        if (bIsValid)
        {
            // warning output once
            UE_LOG(LogRapyutaCore, Warning, TEXT("Target Actor %s is not valid."), *TargetActor->GetName());
        }
        bIsValid = false;
        return;
    }

    if (!URRGeneralUtils::GetRelativeTransform(ReferenceActorName, ReferenceActor, TargetActor->GetTransform(), TF))
    {
        if (bIsValid)
        {
            // warning output once
            UE_LOG(LogRapyutaCore, Warning, TEXT("Reference Actor %s is not valid."), *ReferenceActorName);
        }
        bIsValid = false;
        return;
    }

    bIsValid = true;
    Super::UpdateMessage(InMessage);
}
