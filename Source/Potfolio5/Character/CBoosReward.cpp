// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/CBoosReward.h"
#include "Components/BoxComponent.h"

ACBoosReward::ACBoosReward()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void ACBoosReward::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBoosReward::SetMesh(USkeletalMesh* NewMesh)
{
	Mesh = NewMesh;
}

