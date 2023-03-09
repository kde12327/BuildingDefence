// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "BDPerson.h"
#include "BDCounterWidget.h"


// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaveEndTrigger = CreateDefaultSubobject< UBoxComponent>(TEXT("WAVEEND"));
    WaveEndTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWaveManager::OnWaveEndTriggerBeginOverlap);
    WaveEndTrigger->SetCollisionProfileName(TEXT("OverlapAll"));


    RootComponent = WaveEndTrigger;

    WaveCount = 5;


}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    /*TimeCount += DeltaTime;

    if (TimeCount > 2 && !TempFlag )
    {
        WaveStart();
        TempFlag = true;
    }*/
}

void AWaveManager::WaveStart()
{
	BDLOG_S(Warning);

    WaveLeftCount = WaveCount;
    if (UWorld* world = GetWorld())
    {
        CounterWidget->UpdateWaveLeftText(WaveLeftCount);

        // UABGameInstance::CheckUObjectAlive 콜백 함수를
        // 최초 1회엔 5초 뒤에, 그 다음부턴 매 1초마다 수행되게 하는 타이머 등록
        world->GetTimerManager().SetTimer(
            SpawnPersonTimer,    // TimerHandle
            FTimerDelegate::CreateUObject(this, &AWaveManager::OnPersonSpawn),    // FTimerDelegate (TimerManager.h 확인)
            3.0f,    // Interval
            true    // 반복 여부 (false : 1회만)
        );
    }

}

void AWaveManager::WaveEnd()
{
    BDLOG_S(Warning);
    CounterWidget->OnWaveEnd();
    OnWaveEnd.Broadcast();
}

void AWaveManager::OnPersonSpawn()
{
    BDLOG_S(Warning);
    if (WaveCount > 0)
    {
        if (WavePoints.Num() > 0)
        {
            auto Person = GetWorld()->SpawnActor<ABDPerson>(WavePoints[0]->GetTargetLocation(), FRotator::ZeroRotator);
            BDCHECK(Person != nullptr);
            Person->WavePoints = WavePoints;
        }

        WaveCount--;
        
    }
    else{
        if (UWorld* world = GetWorld())
        {
            FTimerManager& timerManager = world->GetTimerManager();

            timerManager.ClearTimer(SpawnPersonTimer);
        }
    }
}

void AWaveManager::OnWaveEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{

    BDLOG_S(Warning);

    if (static_cast<ABDPerson*>(OtherActor) != nullptr)
    {
        
         OtherActor->Destroy();
         WaveLeftCount--;
         CounterWidget->UpdateWaveLeftText(WaveLeftCount);

         BDLOG(Warning, TEXT("WaveLeftCount %d"), WaveLeftCount);

         if (WaveLeftCount == 0)
         {
             WaveEnd();
         }
    }

}

void AWaveManager::SetWaveNum(int32 Num)
{
    WaveCount = Num;
}