// Copyright (c) 2023-2025 Xist.GG LLC

#include "XcgsLog.h"

#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"


DEFINE_LOG_CATEGORY(LogXcgs);
DEFINE_LOG_CATEGORY(LogXcgsUI);


const FString FalseString(TEXT("false"));
const FString TrueString(TEXT("true"));


FString XcgsGetClientServerContextString(UObject* ContextObject)
{
	ENetRole Role = ROLE_None;

	if (AActor* Actor = Cast<AActor>(ContextObject))
	{
		Role = Actor->GetLocalRole();
	}
	else if (UActorComponent* Component = Cast<UActorComponent>(ContextObject))
	{
		Role = Component->GetOwnerRole();
	}

	if (Role != ROLE_None)
	{
		return (Role == ROLE_Authority) ? TEXT("Server") : TEXT("Client");
	}
	else
	{
#if WITH_EDITOR
		if (GIsEditor)
		{
			extern ENGINE_API FString GPlayInEditorContextString;
			return GPlayInEditorContextString;
		}
#endif
	}

	return TEXT("[]");
}
