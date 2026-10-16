// Copyright © 2017-2022 Esri R&D Center Zurich. All rights reserved.

#pragma once

#include "Algo/AllOf.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInterface.h"
#include "UObject/Object.h"

#include "MaterialReplacement.generated.h"

USTRUCT(BlueprintType)
struct FMaterialReplacementData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Vitruvio")
	FString MaterialIdentifier;

	UPROPERTY(EditAnywhere, Category = "Vitruvio")
	UMaterialInterface* ReplacementMaterial;

	/**
	 * Optional vector parameter on the replacement material that receives the CGA colour (the generated material's
	 * diffuseColor). When set, the replacement is applied as a dynamic instance per component so each model keeps its
	 * own colour (e.g. a building's wallColour). Leave empty to apply the replacement material as is.
	 */
	UPROPERTY(EditAnywhere, Category = "Vitruvio")
	FName ColorParameterName;

	FMaterialReplacementData() : ReplacementMaterial(nullptr) {}

	bool HasReplacement() const
	{
		return ReplacementMaterial != nullptr;
	}

	friend bool operator==(const FMaterialReplacementData& Lhs, const FMaterialReplacementData& Rhs)
	{
		return Lhs.MaterialIdentifier == Rhs.MaterialIdentifier && Lhs.ReplacementMaterial == Rhs.ReplacementMaterial &&
			   Lhs.ColorParameterName == Rhs.ColorParameterName;
	}

	friend bool operator!=(const FMaterialReplacementData& Lhs, const FMaterialReplacementData& Rhs)
	{
		return !(Lhs == Rhs);
	}
};

UCLASS(BlueprintType)
class VITRUVIO_API UMaterialReplacementAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Vitruvio")
	TArray<FMaterialReplacementData> Replacements;

	bool IsValid() const
	{
		return Algo::AllOf(Replacements, [](const FMaterialReplacementData& ReplacementData) { return ReplacementData.HasReplacement(); });
	}
};
