#include "CPlayer.h"
#include "Global.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/CMontageComponent.h"
#include "Component/CAttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Action/CActionData.h"
#include "Action/CDoAction.h"
#include "Action/CEquipment.h"
#include "Action/CAction.h"
#include "../Enemy/CEnemy.h"






ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	TargetMax = -1.f;

	bJog = false;
	bRun = false;


	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	USkeletalMesh* MeshComp;
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("/Game/Player/Samurai/SK_Samurai"));
	if (MeshAsset.Succeeded())
	{
		MeshComp = MeshAsset.Object;
		GetMesh()->SetSkeletalMesh(MeshComp);
	}

	//Component
	{
		//ActionComponet
		CHelpers::CreateActorComponent(this, &ActionComp, TEXT("ActionComp"));
		//MontageComponet
		CHelpers::CreateActorComponent(this, &MontageComp, TEXT("MontageComp"));
		//StateComponent
		CHelpers::CreateActorComponent(this, &StateComp, TEXT("StateComp"));
		//AttributeComponet
		CHelpers::CreateActorComponent(this, &AttributeComp, TEXT("Attribute"));
	}

	//CameraComponent, SpringArmComponent Upload in memory 
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	//SpringArmComp Setting
	SpringArmComp->SetupAttachment(GetMesh());
	SpringArmComp->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 140));
	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->ProbeChannel= ECollisionChannel::ECC_Camera;


	//CameraComp Setting
	CameraComp->SetupAttachment(SpringArmComp);

	//Player Setting
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetWalkpeed();


	//TakeDown
	CanStealthTakeDown = false;
	//StealthTakeDownCamera = NewObject<ACameraActor>();

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Bind Func
	StateComp->OnStateTypeChanged.AddDynamic(this,&ACPlayer::OnStateTypeChanged);

	//Check DataTable
	if (DataTable == nullptr)
	{
		CLog::Log("DataTable is not Set");
		return;
	}

	//Save Montage
	TArray<FStealthTakeDown*> FromDatasTable;
	DataTable->GetAllRows<FStealthTakeDown>("", FromDatasTable);

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		for (const auto& Data : FromDatasTable)
		{
			if ((EActionType)i == Data->Type)
			{
				StealthTakeDownData[i] = Data;
				break;
			}
		}
	}
	
}

//Construction
void ACPlayer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//Dynamic Material
	{
		//Hand Material
		UObject* HandsKatanaMatAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Player/Materials/Instance/MI_handskatana"));
		CheckNull(HandsKatanaMatAsset);
		UMaterialInstanceConstant* HandsKatanaMatConstant = Cast<UMaterialInstanceConstant>(HandsKatanaMatAsset);
		HandsKatanaMat = UMaterialInstanceDynamic::Create(HandsKatanaMatConstant, nullptr);
		Materials.Add(HandsKatanaMat);

		//CostumeMat Material
		UObject* CostumeMatAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Player/Materials/Instance/MI_costume"));
		CheckNull(CostumeMatAsset);
		UMaterialInstanceConstant* CostumeMatConstant = Cast<UMaterialInstanceConstant>(CostumeMatAsset);
		CostumeMat = UMaterialInstanceDynamic::Create(CostumeMatConstant, nullptr);
		Materials.Add(CostumeMat);

		//HeadMat Material
		UObject* HeadMatAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Player/Materials/Instance/MI_head"));
		CheckNull(HeadMatAsset);
		UMaterialInstanceConstant* HeadMatConstant = Cast<UMaterialInstanceConstant>(HeadMatAsset);
		HeadMat = UMaterialInstanceDynamic::Create(HeadMatConstant, nullptr);
		Materials.Add(HeadMat);

		//EyeMat Material
		UObject* EyeMatAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Player/Materials/Instance/MI_eye"));
		CheckNull(EyeMatAsset);
		UMaterialInstanceConstant* EyeMatConstant = Cast<UMaterialInstanceConstant>(EyeMatAsset);
		EyeMat = UMaterialInstanceDynamic::Create(EyeMatConstant, nullptr);
		Materials.Add(EyeMat);

		//HairMat Material
		UObject* HairMatAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Player/Materials/Instance/MI_hair"));
		CheckNull(HairMatAsset);
		UMaterialInstanceConstant* HairMatConstant = Cast<UMaterialInstanceConstant>(HairMatAsset);
		HairMat = UMaterialInstanceDynamic::Create(HairMatConstant, nullptr);
		Materials.Add(HairMat);

		//PantsMat Material
		UObject* PantsMatAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Player/Materials/Instance/MI_pants"));
		CheckNull(PantsMatAsset);
		UMaterialInstanceConstant* PantsMatConstant = Cast<UMaterialInstanceConstant>(PantsMatAsset);
		PantsMat = UMaterialInstanceDynamic::Create(PantsMatConstant, nullptr);
		Materials.Add(PantsMat);

		//JacketMat Material
		UObject* JacketMatAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Player/Materials/Instance/MI_jacket"));
		CheckNull(JacketMatAsset);
		UMaterialInstanceConstant* JacketMatConstant = Cast<UMaterialInstanceConstant>(JacketMatAsset);
		JacketMat = UMaterialInstanceDynamic::Create(JacketMatConstant, nullptr);
		Materials.Add(JacketMat);
	}

	for (int32 i = 0; i < Materials.Num(); i++)
	{
		GetMesh()->SetMaterial(i, Materials[i]);
	}

	
	
}

void ACPlayer::Tick(float DeltaSeconds)
{

	//Wall Location Trace
	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * 200.f);
	TArray<TEnumAsByte<EObjectTypeQuery>> TypeQuery;
	TypeQuery.Add(EObjectTypeQuery::ObjectTypeQuery1);
	TArray<AActor*> IgnoreActor;
	FHitResult HitResult;
	bool CanVault;

	//Wall Trace
	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TypeQuery, false, IgnoreActor, EDrawDebugTrace::None, HitResult, true))
	{
		FVector WallLocation = HitResult.Location;
		FVector WallNormal = HitResult.Normal;
		
		FVector TraceStart = WallLocation  + FVector(0.0f, 0.0f, 200.f);
		FVector TraceEnd = TraceStart - FVector(0.0f, 0.0f, 200.f);

		FHitResult TraceHitResult;

		//Check Height
		if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, TypeQuery, false, IgnoreActor, EDrawDebugTrace::None, TraceHitResult, true))
		{
			FVector Height = TraceHitResult.Location;
			if ((Height - WallLocation).Z < 60.f)
			{
				CanVault = true;
			}
			else
			{
				CanVault = false;
			}

			//Check Wall Death
			FVector DeathStart = WallLocation + (WallNormal * -100.f) + FVector(0.0f, 0.0f, 300.f);
			FVector DeathEnd = DeathStart - FVector(0.0f, 0.0f, 275.f);
			if (!UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), DeathStart, DeathEnd, TypeQuery, false, IgnoreActor, EDrawDebugTrace::None, TraceHitResult, true))
			{
				if (CanVault)
				{
					if (bRun)
					{
						bRun = false;
					FRotator ActorLookRotation = FRotator(GetActorRotation().Pitch, (UKismetMathLibrary::MakeRotFromX(WallNormal).Yaw + 180.f), GetActorRotation().Roll);
					SetActorRotation(ActorLookRotation);
					GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);


					FVector NewLocation = FVector((WallLocation + (WallNormal * 150.f)).X, (WallLocation + (WallNormal * 60.f)).Y, (Height - FVector(0.f,0.0f,10.f)).Z);
					SetActorLocation(NewLocation);
					DisableInput(GetController<APlayerController>());
					StateComp->SetVaultMode();
					MontageComp->PlayVault();

					FTimerHandle VaultHandel;
					FTimerDelegate VaultDelegate;
					VaultDelegate.BindUFunction(this,TEXT("EndVault"));
					GetWorldTimerManager().SetTimer(VaultHandel, VaultDelegate,2.06f,false);
					}
				}
			}
		}
		
	}



	if (LockOnTarget)
	{

	if (1000.f < UKismetMathLibrary::Vector_Distance(GetActorLocation(), LockOnTarget->GetActorLocation()))
	{
		LockOnTarget->TagetWidgetOff();
		MostLearestActor = nullptr;
	}
	}

	CheckTrue(ActionComp->IsUnarmedMode());
	if (MostLearestActor)
	{
		LockOnTarget = MostLearestActor;
		FRotator ContorlRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LockOnTarget->GetActorLocation());
		GetController()->SetControlRotation(ContorlRotator);
	}
	
}

void ACPlayer::StealTakeDown(bool InCrouch, EActionType InActionType)
{

	switch (InActionType)
	{
	case EActionType::Sword :
		{
			InCrouch ? OnSwordCrouchStealthTakeDown(InCrouch,InActionType): OnSwordStealthTakeDown(InCrouch,InActionType);
			break;
		}
	case EActionType::UnArmed:
	{
		
		OnUnArmdStandingStealthTakeDown(InCrouch, InActionType);
		break;
		
	}
	default:
		break;
	}
	
}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//BindAxis
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayer::OnLockUp);
	PlayerInputComponent->BindAxis("LookHorizone", this, &ACPlayer::OnLockRight);
	

	PlayerInputComponent->BindAction("Run",EInputEvent::IE_Pressed,this,&ACPlayer::OnRun);
	PlayerInputComponent->BindAction("Run",EInputEvent::IE_Released,this,&ACPlayer::OnWalk);
	PlayerInputComponent->BindAction("Sword", EInputEvent::IE_Pressed,this, &ACPlayer::OnSword);
	PlayerInputComponent->BindAction("Pistol", EInputEvent::IE_Pressed,this, &ACPlayer::OnPistol);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed,this, &ACPlayer::OnReload);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed,this, &ACPlayer::OnJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released,this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("PrimaryAct", EInputEvent::IE_Pressed,this, &ACPlayer::OnPrimaryAct);
	PlayerInputComponent->BindAction("SecondaryAct", EInputEvent::IE_Pressed,this, &ACPlayer::OnSecondaryAct);
	PlayerInputComponent->BindAction("SecondaryAct", EInputEvent::IE_Released,this, &ACPlayer::OffSecondaryAct);
	PlayerInputComponent->BindAction("Target_On", EInputEvent::IE_Pressed,this, &ACPlayer::Target_On);
	PlayerInputComponent->BindAction("TakeDown", EInputEvent::IE_Pressed,this, &ACPlayer::TakeDown);
	PlayerInputComponent->BindAction("Jog", EInputEvent::IE_Pressed,this, &ACPlayer::OnJog);

}

FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId();
}




void ACPlayer::OnMoveForward(float Axis)
{
	CheckFalse(AttributeComp->IsMove());

	FRotator ControlRotation = FRotator(0,GetControlRotation().Yaw,0);
	FVector Direction = FQuat(ControlRotation).GetForwardVector();
	AddMovementInput(Direction,Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	CheckFalse(AttributeComp->IsMove());

	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRotation).GetRightVector();
	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnLockUp(float Axix)
{
	AddControllerPitchInput(Axix);
}

void ACPlayer::OnLockRight(float Axix)
{
	AddControllerYawInput(Axix);

	
}


//Player Speed Setting
void ACPlayer::OnRun()
{
	CheckFalse(StateComp->IsIdleMode());
	bJog = false;
	
	if (ActionComp->IsSwordMode())
	{
	
	MontageComp->PlayEvade();
	StateComp->SetEvadeMode();
	FTimerDynamicDelegate Delegate;
	Delegate.BindUFunction(this,TEXT("OnStartRun"));
	GetWorldTimerManager().SetTimer(RunTimer, Delegate,0.7f,false);
	return;
	}
	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetSprintpeed();
}

void ACPlayer::OnStartRun()
{
	bRun = true;
	GetCapsuleComponent()->SetCapsuleHalfHeight(88.f);
	StopAnimMontage();
	StateComp->SetIdleMode();
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetSprintpeed();
}

void ACPlayer::OnWalk()
{
	bRun = false;
	if (ActionComp->IsSwordMode())
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		bUseControllerRotationYaw = true;
	}
	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetWalkpeed();
}

void ACPlayer::OnSword()
{
	CheckFalse(StateComp->IsIdleMode());
	ActionComp->SetSwordMode();
}


void ACPlayer::OnPistol()
{
	CheckFalse(StateComp->IsIdleMode());
	ActionComp->SetPistolMode();
}

void ACPlayer::OnPrimaryAct()
{
	if (ActionComp->IsSwordMode())
	{
	ActionComp->DoAction();
	return;
	}
	CheckFalse(StateComp->IsIdleMode());
	ActionComp->DoAction();
}

void ACPlayer::OnSecondaryAct()
{
	CheckTrue(ActionComp->IsUnarmedMode())
	ActionComp->DoSubAction(true);
}

void ACPlayer::OffSecondaryAct()
{
	CheckTrue(ActionComp->IsUnarmedMode())
	ActionComp->DoSubAction(false);

}

void ACPlayer::OnJump()
{
	CheckFalse(StateComp->IsIdleMode());
	if ( ActionComp->IsSwordMode())
	{
		return;
	}
	StateComp->SetJumpMode();
	Jump();
}

void ACPlayer::OnReload()
{
	CheckFalse(StateComp->IsIdleMode());
	CheckFalse(ActionComp->IsPistolMode());
	StateComp->SetReloadMode();
}

void ACPlayer::Begin_Reload()
{
	MontageComp->PlayReload();
}

void ACPlayer::Target_On()
{
	CheckTrue(ActionComp->IsUnarmedMode());

	FVector Center = GetActorLocation();
	FVector End = GetActorLocation() + FVector(0,0,10);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Add(EObjectTypeQuery::ObjectTypeQuery3);

	TArray<AActor*> IgnoreActor;
	IgnoreActor.Add(this);
	TArray<FHitResult> TraceResult;

	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Center, End, 1000.f, ObjectType, false, IgnoreActor, EDrawDebugTrace::ForDuration, TraceResult, true))
	{
		for (const auto& Result : TraceResult)
		{
			TargetActors.AddUnique(Result.Actor.Get());
		}

		for (const auto& Actor : TargetActors)
		{ 
			float Dot = GetActorLocation() | Actor->GetActorLocation();
			if (Dot >= TargetMax)
			{
				TargetMax = Dot;
				MostLearestActor = Cast<ACEnemy>(Actor);
			}
		}
		if (MostLearestActor)
		{
			LockOnTarget = MostLearestActor;
			LockOnTarget->TagetWidgetOn();
		}
	}

	
}

void ACPlayer::OnJog()
{
	CheckFalse(ActionComp->IsSwordMode());
	bJog = !bJog;
	if (bJog)
	{
		GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetSneakpeed();
		
	}
	else
	{
	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetWalkpeed();
	}
}

void ACPlayer::OnSwordCrouchStealthTakeDown(bool InCrouch, EActionType InActionType)
{
	FStealthTakeDown* Data = StealthTakeDownData[(int32)InActionType];

	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + GetActorForwardVector() * 250.f;

	ETraceTypeQuery TakeDownTraceType;
	TakeDownTraceType = ETraceTypeQuery::TraceTypeQuery1;

	TArray<AActor*> IngnoreActors;
	IngnoreActors.Add(this);

	FHitResult HitResult;

	//Trace - True : TakeDown
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TakeDownTraceType, false, IngnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		GetCharacterMovement()->DisableMovement();
		ACEnemy* Enemy = Cast<ACEnemy>(HitResult.Actor);
		if (Enemy == nullptr)
		{
			return;
		}

		//Player Set Location , Rotation
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;;

		FVector TakeDownLocation = Enemy->GetActorLocation() + (Enemy->GetActorForwardVector() * -50.f) + (Enemy->GetActorRightVector() * 65.f);
		FRotator TakeDownRotation = Enemy->GetActorRotation();
		//UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Enemy->GetActorLocation());

		SetActorLocation(TakeDownLocation);
		SetActorRotation(TakeDownRotation);

		//Spawn Camera & ViewTarget
		FVector Location = GetActorLocation() + (GetActorForwardVector() * 250.f) + (GetActorRightVector() * -50.f) + (GetActorUpVector() * 50.f);
		FTransform CameraTransForm;
		CameraTransForm.SetLocation(Location);

		StealthTakeDownCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraTransForm);
		StealthTakeDownCamera->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Location, GetActorLocation()));

		APlayerController* PC = Cast<APlayerController>(GetController());
		PC->SetViewTargetWithBlend(StealthTakeDownCamera);
		StealthTakeDownCamera->GetCameraComponent()->bConstrainAspectRatio = false;

		Enemy->TakeDown(bJog, InActionType);

		
		if (Data && Data->Montage[(int32)InCrouch])
		{
		float MontageTime = PlayAnimMontage(Data->Montage[(int32)InCrouch],Data->PlayRate,Data->StartSection);
		GetCharacterMovement()->DisableMovement();
		FTimerDelegate TakeDownDelegate;
		TakeDownDelegate.BindUFunction(this, TEXT("EndTakeDown"));
		GetWorldTimerManager().SetTimer(StealthTakeDownHandle, TakeDownDelegate, MontageTime, false);
		}
	}
}

void ACPlayer::OnUnArmdStandingStealthTakeDown(bool InCrouch, EActionType InActionType)
{
	FStealthTakeDown* Data = StealthTakeDownData[(int32)InActionType];

	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + GetActorForwardVector() * 250.f;

	ETraceTypeQuery TakeDownTraceType;
	TakeDownTraceType = ETraceTypeQuery::TraceTypeQuery1;

	TArray<AActor*> IngnoreActors;
	IngnoreActors.Add(this);

	FHitResult HitResult;

	//Trace - True : TakeDown
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TakeDownTraceType, false, IngnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		GetCharacterMovement()->DisableMovement();
		ACEnemy* Enemy = Cast<ACEnemy>(HitResult.Actor);
		if (Enemy == nullptr)
		{
			return;
		}

		//Player Set Location , Rotation
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;;

		FVector TakeDownLocation = Enemy->GetActorLocation() + (Enemy->GetActorForwardVector() * -50.f) + (Enemy->GetActorRightVector() * 25.f);
		FRotator TakeDownRotation = Enemy->GetActorRotation();
		//UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Enemy->GetActorLocation());

		SetActorLocation(TakeDownLocation);
		SetActorRotation(TakeDownRotation);

		//Spawn Camera & ViewTarget
		FVector Location = GetActorLocation() + (GetActorForwardVector() * 400.f) ;
		FTransform CameraTransForm;
		CameraTransForm.SetLocation(Location);

		StealthTakeDownCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraTransForm);
		StealthTakeDownCamera->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Location, GetActorLocation()));

		APlayerController* PC = Cast<APlayerController>(GetController());
		PC->SetViewTargetWithBlend(StealthTakeDownCamera);
		StealthTakeDownCamera->GetCameraComponent()->bConstrainAspectRatio = false;

		Enemy->TakeDown(bJog, InActionType);


		if (Data && Data->Montage[(int32)InCrouch])
		{
			float MontageTime = PlayAnimMontage(Data->Montage[(int32)InCrouch], Data->PlayRate, Data->StartSection);
			GetCharacterMovement()->DisableMovement();
			FTimerDelegate TakeDownDelegate;
			TakeDownDelegate.BindUFunction(this, TEXT("EndTakeDown"));
			GetWorldTimerManager().SetTimer(StealthTakeDownHandle, TakeDownDelegate, MontageTime, false);
		}
	}
}

void ACPlayer::OnSwordStealthTakeDown(bool InCrouch ,EActionType InActionType)
{
	FStealthTakeDown* Data = StealthTakeDownData[(int32)InActionType];

	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + GetActorForwardVector() * 250.f;

	ETraceTypeQuery TakeDownTraceType;
	TakeDownTraceType = ETraceTypeQuery::TraceTypeQuery1;

	TArray<AActor*> IngnoreActors;
	IngnoreActors.Add(this);

	FHitResult HitResult;

	//Trace - True : TakeDown
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TakeDownTraceType, false, IngnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		GetCharacterMovement()->DisableMovement();
		ACEnemy* Enemy = Cast<ACEnemy>(HitResult.Actor);
		if (Enemy == nullptr)
		{
			return;
		}

		//Player Set Location , Rotation
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;;

		FVector TakeDownLocation = Enemy->GetActorLocation() + (Enemy->GetActorForwardVector() * -100.f) + (Enemy->GetActorRightVector() * 25.f);
		FRotator TakeDownRotation = Enemy->GetActorRotation();
		//UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Enemy->GetActorLocation());

		SetActorLocation(TakeDownLocation);
		SetActorRotation(TakeDownRotation);

		//Spawn Camera & ViewTarget
		FVector Location = GetActorLocation() +(GetActorForwardVector() * 250.f) + (GetActorUpVector() * 100.f);
		FTransform CameraTransForm;
		CameraTransForm.SetLocation(Location);

		StealthTakeDownCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraTransForm);
		StealthTakeDownCamera->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Location, GetActorLocation()));

		APlayerController* PC = Cast<APlayerController>(GetController());
		PC->SetViewTargetWithBlend(StealthTakeDownCamera);
		StealthTakeDownCamera->GetCameraComponent()->bConstrainAspectRatio = false;

		Enemy->TakeDown(bJog, InActionType);

		
		if (Data && Data->Montage[(int32)InCrouch])
		{
			float MontageTime = PlayAnimMontage(Data->Montage[(int32)InCrouch], Data->PlayRate, Data->StartSection);

			GetCharacterMovement()->DisableMovement();
			FTimerDelegate TakeDownDelegate;
			TakeDownDelegate.BindUFunction(this, TEXT("EndTakeDown"));
			GetWorldTimerManager().SetTimer(StealthTakeDownHandle, TakeDownDelegate, MontageTime, false);
		}
	}
}



void ACPlayer::End_Jump()
{
	StateComp->SetIdleMode();
}

void ACPlayer::End_Parkour()
{
}

void ACPlayer::End_Reload()
{
	StateComp->SetIdleMode();
}

void ACPlayer::OnTakeDown()
{
	CanStealthTakeDown = true;
}

void ACPlayer::OffTakeDown()
{
	CanStealthTakeDown = false;
}

float ACPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	DamageInstigator = EventInstigator;

	//ActionComp->Abort();
	AttributeComp->OnDecreseHealth(Damage);

	if (AttributeComp->GetCurrentHealth() <= 0)
	{
		StateComp->SetDeadMode();
		return 0.0f;
	}

	StateComp->SetHittedMode();

	return DamageValue;
}



void ACPlayer::EndVault()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	EnableInput(GetController<APlayerController>());
}

void ACPlayer::Hitted()
{
	MontageComp->PlayHitted();
}

void ACPlayer::TakeDown()
{
	if (CanStealthTakeDown == false)
	{
		return;
	}
	if (DataTable == nullptr)
	{
		return;
	}
	CanStealthTakeDown = false;
	StealTakeDown(bJog, ActionComp->GetCurrentType());
}


void ACPlayer::EndTakeDown()
{
	GetWorldTimerManager().ClearTimer(StealthTakeDownHandle);
	StealthTakeDownCamera->Destroy();
	if (ActionComp->GetCurrentAction()->GetEquipment()->GetSetForward())
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	APlayerController* PC = Cast<APlayerController>(GetController());
	PC->SetViewTargetWithBlend(CameraComp->GetAttachmentRootActor());
	
}

//Change State
void ACPlayer::OnStateTypeChanged(EStateType PreType, EStateType NewType)
{
	switch (NewType)
	{
	case EStateType::Reload:
	{
		Begin_Reload();
		break;
	}
	case EStateType::Hitted:
	{
		Hitted();
		break;
	}
	case EStateType::Dead:
	{
		break;
	}
	default:
		break;
	}
}
