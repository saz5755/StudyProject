// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Triggers/MyTriggerBaseInterface.h"
#include "TriggerInterface.h"
#include "Misc/NameTable.h"

// Sets default values
AMyTriggerBaseInterface::AMyTriggerBaseInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.TickInterval = 0.1f;
	bGenerateOverlapEventsDuringLevelStreaming = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	ActiveRadius = CreateDefaultSubobject<USphereComponent>(TEXT("ActiveRadius"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	TriggerObject = CreateDefaultSubobject<UChildActorComponent>(TEXT("TriggerObject"));

	ActiveRadius->SetupAttachment(GetRootComponent());
	Trigger->SetupAttachment(GetRootComponent());
	TriggerObject->SetupAttachment(GetRootComponent());

	ActiveRadius->SetSphereRadius(600.f);	// 6m
	Trigger->SetSphereRadius(120.f);		// 1.2m

	// FText: 국가별(한국: 안녕; 영어: Hello) 처리가 가능한 문자열
	// FString: 문자열 (c++ wstring)
	// 
	// FName: 문자열을 해슁(특정 타입을 정수로 변환해서 들고 있는 것)
	//		  대소문자 구분이 없다
	//		  검색 속도를 향상시키기 위해서 사용
	//		  문자열 비교보다 정수 비교가 더 빠르기 때문에
	// "Hello" -> 001002031203
	// "Hello" -> 001002031203
	// int64 HashValue = HashFunction("Hello");
	ActiveRadius->SetCollisionProfileName(NameTable::Collision::PlayerTrigger);
	Trigger->SetCollisionProfileName(NameTable::Collision::PlayerTrigger);

	ActiveRadius->OnComponentBeginOverlap.AddDynamic(this, &AMyTriggerBaseInterface::OnActiveRadiusBeginOverlap);
	ActiveRadius->OnComponentEndOverlap.AddDynamic(this, &AMyTriggerBaseInterface::OnActiveRadiusEndOverlap);
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyTriggerBaseInterface::OnTriggerBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AMyTriggerBaseInterface::OnTriggerEndOverlap);

	{
		// DefaultSceneRoot (RootComponent)
		// - ActiveRadius
		// - Trigger
		// - TriggerObject
	}
}

// Called when the game starts or when spawned
void AMyTriggerBaseInterface::BeginPlay()
{
	Super::BeginPlay();

	Inactive();
}

AActor* AMyTriggerBaseInterface::GetTriggerObject() const
{
	AActor*const Actor = TriggerObject->GetChildActor();
	if (!IsValid(Actor))
	{
		ensureAlwaysMsgf(false, TEXT("Actor is nullptr"));
		return nullptr;
	}

	// interface를 가지고 있는지 쿼리(질의; 물어본다)
	const bool bIsImplemented = Actor->GetClass()->ImplementsInterface(UTriggerInterface::StaticClass());
	if (!bIsImplemented)
	{
		ensureAlwaysMsgf(false, TEXT("Class must ImplementsInterface ITriggerInterface"));
		return nullptr;
	}

	return Actor;
}

void AMyTriggerBaseInterface::Active()
{
	ReceiveActive();

	AActor* Actor = GetTriggerObject();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface->Active();
	}
	else
	{
		ITriggerInterface::Execute_ReceiveActive(Actor);
	}
}

void AMyTriggerBaseInterface::Inactive()
{
	ReceiveInactive();

	AActor* Actor = GetTriggerObject();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface->Inactive();
	}
	else
	{
		ITriggerInterface::Execute_ReceiveInactive(Actor);
	}
}

void AMyTriggerBaseInterface::InTrigger()
{
	ReceiveInTrigger();

	AActor* Actor = GetTriggerObject();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface->InTrigger();
	}
	else
	{
		ITriggerInterface::Execute_ReceiveInTrigger(Actor);
	}
}

void AMyTriggerBaseInterface::OutTrigger()
{
	ReceiveOutTrigger();

	AActor* Actor = GetTriggerObject();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface->OutTrigger();
	}
	else
	{
		ITriggerInterface::Execute_ReceiveOutTrigger(Actor);
	}
}

// Called every frame
void AMyTriggerBaseInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTriggerBaseInterface::OnActiveRadiusBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Active();
}

void AMyTriggerBaseInterface::OnActiveRadiusEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Inactive();
}

void AMyTriggerBaseInterface::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InTrigger();
}

void AMyTriggerBaseInterface::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OutTrigger();
}

