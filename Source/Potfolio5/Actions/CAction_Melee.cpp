#include "Actions/CAction_Melee.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"
#include "Component/CAttributeComponent.h"
#include "Character/CPlayer.h"
#include "Character/CEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/CAIController.h"

UCAction_Melee::UCAction_Melee()
{
    ActionVaule = 0;
    bCombo = false;
    bSuccess = false;
    bIsRunning = false;
    StopRate = 1.0f;
    Damage = 10.f;
}

// ----------------------
// 공격 시작
// ----------------------
void UCAction_Melee::StartAction_Implementation(AActor* Instigator)
{
    ACPlayer* Player = Cast<ACPlayer>(Instigator);
    ACEnemy* Enemy = Cast<ACEnemy>(Instigator);
    ACharacter* Character = Cast<ACharacter>(Instigator);

    // Overlap 바인딩
    if (Player && !Player->OnBeginOverlap.IsBound())
        Player->OnBeginOverlap.AddDynamic(this, &UCAction_Melee::MeleeOverlap);

    if (Enemy && !Enemy->OnBeginOverlap.IsBound())
        Enemy->OnBeginOverlap.AddDynamic(this, &UCAction_Melee::MeleeOverlap);

    // StopTimer 설정
    FTimerDelegate StopDelegate = FTimerDelegate::CreateUObject(this, &UCAction_Melee::StopAction_Implementation, Instigator);
    if (!GetWorld(Instigator)->GetTimerManager().IsTimerActive(StopTimer))
        GetWorld(Instigator)->GetTimerManager().SetTimer(StopTimer, StopDelegate, StopRate, false);

    // AuraTimer 초기화
    if (GetWorld(Instigator)->GetTimerManager().IsTimerActive(AuraTimer))
        GetWorld(Instigator)->GetTimerManager().ClearTimer(AuraTimer);

    // 콤보 연결
    if (bCombo)
    {
        bSuccess = true;
        return;
    }

    if (!CanAction(Instigator))
        return;

    // 애니메이션 재생
    if (IsValid(ActionMontages[0]))
    {
        Character->PlayAnimMontage(ActionMontages[0]);
        bIsRunning = true;

        if (Player)
        {
            Player->SetActorRotation(FRotator(0, Player->GetControlRotation().Yaw, 0));
            Player->PlayEquip();
        }

        Super::StartAction_Implementation(Instigator);
    }
}

// ----------------------
// 공격 종료
// ----------------------
void UCAction_Melee::StopAction_Implementation(AActor* Instigator)
{
    Super::StopAction_Implementation(Instigator);

    ActionVaule = 0;
    bIsRunning = false;
    bCombo = false;

    if (GetWorld(Instigator)->GetTimerManager().IsTimerActive(StopTimer))
        GetWorld(Instigator)->GetTimerManager().ClearTimer(StopTimer);

    // UnEquip 설정
    FTimerDelegate UnEquipDelegate = FTimerDelegate::CreateUObject(this, &UCAction_Melee::PlayUnEquip, Instigator);
    if (!GetWorld(Instigator)->GetTimerManager().IsTimerActive(AuraTimer))
        GetWorld(Instigator)->GetTimerManager().SetTimer(AuraTimer, UnEquipDelegate, 10.f, false);

    // Overlap 해제
    if (ACPlayer* Player = Cast<ACPlayer>(Instigator))
        Player->OnBeginOverlap.Clear();

    if (ACEnemy* Enemy = Cast<ACEnemy>(Instigator))
    {
        Enemy->OnBeginOverlap.Clear();
        if (ACAIController* AIController = Cast<ACAIController>(Enemy->GetController()))
            AIController->GetBlackboardComponent()->SetValueAsBool("AttackingKey", false);
    }

    HitActors.Empty();
}

// ----------------------
// UnEquip 처리
// ----------------------
void UCAction_Melee::PlayUnEquip(AActor* Instigator)
{
    if (ACPlayer* Player = Cast<ACPlayer>(Instigator))
    {
        if (Player->IsEquip() && !bIsRunning)
            Player->PlayUnEquip();
    }

    if (!GetWorld(Instigator)->GetTimerManager().IsTimerActive(AuraTimer))
        GetWorld(Instigator)->GetTimerManager().ClearTimer(AuraTimer);
}

// ----------------------
// 충돌 처리
// ----------------------
void UCAction_Melee::MeleeOverlap(UPrimitiveComponent* OverlappedComp, const FHitResult& SweepResult)
{
    if (AActor* OtherActor = SweepResult.GetActor())
    {
        int32 Index = HitActors.Num();
        HitActors.AddUnique(OtherActor);
        if (Index >= HitActors.Num()) return;

        if (UCAttributeComponent* AttributeComp = Cast<UCAttributeComponent>(OtherActor->GetComponentByClass(UCAttributeComponent::StaticClass())))
        {
            AttributeComp->DamageHealth(Damage, OtherActor, GetOwner()->GetOwner(), GetOwner()->GetOwner()->GetInstigatorController());
        }
    }
}

// ----------------------
// 다음 콤보 실행 (애니노티파이에서 호출)
// ----------------------
void UCAction_Melee::NextCombo(AActor* Instigator)
{
    if (!bSuccess) return;

    bSuccess = false;
    HitActors.Empty();
    GetWorld(Instigator)->GetTimerManager().ClearTimer(StopTimer);

    ActionVaule++;
    ActionVaule = FMath::Clamp(ActionVaule, 0, ActionMontages.Num() - 1);

    if (ACharacter* Character = Cast<ACharacter>(Instigator))
    {
        if (IsValid(ActionMontages[ActionVaule]))
        {
            Character->SetActorRotation(FRotator(0, Character->GetControlRotation().Yaw, 0));
            Character->PlayAnimMontage(ActionMontages[ActionVaule]);
        }
    }
}

// ----------------------
// 콤보 입력 기록
// ----------------------
void UCAction_Melee::OnCombo() { bCombo = true; }
void UCAction_Melee::OffCombo() { bCombo = false; }