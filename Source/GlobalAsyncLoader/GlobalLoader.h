#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GlobalLoader.generated.h"

UCLASS()
class GLOBALASYNCLOADER_API ULoader final : public UObject
{
	GENERATED_BODY()

public:

	template <class T, typename CallbackType>
	static void Load(TSoftClassPtr<T> SoftClass, CallbackType Callback)
	{
		if (SoftClass.IsNull())
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid SoftClassPtr provided."));
			return;
		}

		if (SoftClass.IsPending())
		{
			FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

			Streamable.RequestAsyncLoad(SoftClass.ToSoftObjectPath(),
				[SoftClass, Callback]()
				{
					Callback(SoftClass.Get());
				});
		}
		else if (SoftClass.IsValid())
		{
			Callback(SoftClass.Get());
		}
	}

	template <class T, typename CallbackType>
	static void Load(TSoftObjectPtr<T> SoftObject, CallbackType Callback)
	{
		if (SoftObject.IsNull())
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid SoftObjectPtr provided."));
			return;
		}

		if (SoftObject.IsPending())
		{
			FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

			Streamable.RequestAsyncLoad(SoftObject.ToSoftObjectPath(),
				[SoftObject, Callback]()
				{
					Callback(SoftObject.Get());
				});
		}
		else if (SoftObject.IsValid())
		{
			Callback(SoftObject.Get());
		}
	}
};
