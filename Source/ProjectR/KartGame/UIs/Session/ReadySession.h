﻿#pragma once

#include "CoreMinimal.h"
#include "CommonUtil.h"
#include "Blueprint/UserWidget.h"
#include "ReadySession.generated.h"

class UTextBlock;
class UCommonButton;
class UReadySessionPlayerWidget;
class UUniformGridPanel;

UCLASS()
class PROJECTR_API UReadySession : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdatePlayers(const TArray<FString>& PlayerList);
	void InitializeData();

	GETTER(TObjectPtr<UCommonButton>, GameStartButton)
	
protected:
	virtual void NativePreConstruct() override;

private:
	const uint8 PlayerInfoGridWidth = 4;
	const uint8 PlayerInfoGridHeight = 2;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> PlayerInfoGrid;

	UPROPERTY(EditDefaultsOnly, Category = "Options|UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<UReadySessionPlayerWidget> PlayerInfoClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButton> GameStartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RoomId;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RoomTitle;

	void InitializeWidget();
};
