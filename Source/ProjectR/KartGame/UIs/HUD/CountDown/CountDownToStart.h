﻿#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountDownToStart.generated.h"

class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStartNotified);

UCLASS()
class PROJECTR_API UCountDownToStart : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnGameStartNotified OnGameStartNotified;

	void StartCountDown();
	
protected:
	virtual void NativePreConstruct() override;

private:
	UPROPERTY()
	FWidgetAnimationDynamicEvent OnCountEndNotified;
	UPROPERTY()
	FWidgetAnimationDynamicEvent OnCountStartNotified;
	
	// TODO: 해당 로직은 추후 GameState로 이전되어 연동될 예정
	UPROPERTY(EditDefaultsOnly, Category = "Options|UI", meta = (AllowPrivateAccess = true))
	uint8 CountDownNum = 3;
	
	UPROPERTY(EditDefaultsOnly, Category = "Options|UI", meta = (AllowPrivateAccess = true))
	FString StartText = TEXT("GO!");
	
	UPROPERTY(EditDefaultsOnly, Category = "Options|Sound", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> CountDownSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Options|Sound", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> GameStartSound;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CountDownText;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> CountDownAnimation;

	UFUNCTION()
	void OnCountDownAnimationStart();
	
	UFUNCTION()
	void OnCountDownAnimationEnd();

	void UpdateCountDownText();
};
