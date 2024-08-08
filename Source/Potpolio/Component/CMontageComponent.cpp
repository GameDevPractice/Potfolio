#include "CMontageComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCMontageComponent::UCMontageComponent()
{
	
}


void UCMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	//Check DataTable
	if (DataTable == nullptr)
	{
		CLog::Log("DataTable is not Set");
		return;
	}

	//Save Montage
	TArray<FMontageData*> FromDatasTable;
	DataTable->GetAllRows<FMontageData>("", FromDatasTable);

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (const auto& Data : FromDatasTable)
		{
			if ((EStateType)i == Data->Type)
			{
				Datas[i] = Data;
				break;
			}
		}
	}

}

void UCMontageComponent::PlayReload()
{
	PlayAnimMontage(EStateType::Reload);
}

void UCMontageComponent::PlayHitted()
{
	PlayAnimMontage(EStateType::Hitted);
}

void UCMontageComponent::PlayDead()
{
	PlayAnimMontage(EStateType::Dead);
}

void UCMontageComponent::PlayAnimMontage(EStateType NewType)
{
	ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerChar);

	const FMontageData* Data = Datas[(int32)NewType];
	if (Data && Data->Montage)
	{
		OwnerChar->PlayAnimMontage(Data->Montage,Data->PlayRate,Data->StartSection);
	}
}
