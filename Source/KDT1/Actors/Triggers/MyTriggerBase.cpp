// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Triggers/MyTriggerBase.h"
#include "MyTriggerObjectBase.h"
#include "Misc/NameTable.h"

// Sets default values
AMyTriggerBase::AMyTriggerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

	ActiveRadius->OnComponentBeginOverlap.AddDynamic(this, &AMyTriggerBase::OnActiveRadiusBeginOverlap);
	ActiveRadius->OnComponentEndOverlap.AddDynamic(this, &AMyTriggerBase::OnActiveRadiusEndOverlap);
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyTriggerBase::OnTriggerBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AMyTriggerBase::OnTriggerEndOverlap);

	{
		// DefaultSceneRoot (RootComponent)
		// - ActiveRadius
		// - Trigger
		// - TriggerObject
	}
}

// Called when the game starts or when spawned
void AMyTriggerBase::BeginPlay()
{
	Super::BeginPlay();

	Inactive();
}

AMyTriggerObjectBase* AMyTriggerBase::GetTriggerObject() const
{
	AActor* Actor = TriggerObject->GetChildActor();
	if (!IsValid(Actor))
	{
		ensureAlwaysMsgf(false, TEXT("Actor is nullptr"));
		return nullptr;
	}

	AMyTriggerObjectBase* TriggerObjectBase = Cast<AMyTriggerObjectBase>(Actor);
	if (!IsValid(TriggerObjectBase))
	{
		ensureAlwaysMsgf(false, TEXT("Class must subclass of AMyTriggerObjectBase"));
		return nullptr;
	}

	return TriggerObjectBase;
}

void AMyTriggerBase::Active()
{
	AMyTriggerObjectBase* TriggerObjectBase = GetTriggerObject();
	if (!TriggerObjectBase) { return; }

	TriggerObjectBase->Active();
}

void AMyTriggerBase::Inactive()
{
	AMyTriggerObjectBase* TriggerObjectBase = GetTriggerObject();
	if (!TriggerObjectBase) { return; }

	TriggerObjectBase->Inactive();
}

void AMyTriggerBase::InTrigger()
{
	AMyTriggerObjectBase* TriggerObjectBase = GetTriggerObject();
	if (!TriggerObjectBase) { return; }

	TriggerObjectBase->InTrigger();
}

void AMyTriggerBase::OutTrigger()
{
	AMyTriggerObjectBase* TriggerObjectBase = GetTriggerObject();
	if (!TriggerObjectBase) { return; }

	TriggerObjectBase->OutTrigger();
}

// Called every frame
void AMyTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTriggerBase::OnActiveRadiusBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Active();
}

void AMyTriggerBase::OnActiveRadiusEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Inactive();
}

void AMyTriggerBase::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InTrigger();
}

void AMyTriggerBase::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OutTrigger();
}

