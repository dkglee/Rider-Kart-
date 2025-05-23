﻿#include "SessionCreatePopupWidget.h"

#include "EnumUtil.h"
#include "SessionUtil.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/EditableText.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "KartGame/Games/Component/WidgetControlComponent.h"
#include "KartGame/Games/Modes/Lobby/LobbyPlayerController.h"

void USessionCreatePopupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(
			this, &ThisClass::OnSessionCreated);
	
	CreateRoomButton->OnClicked.AddDynamic(this, &ThisClass::OnClickCreateRoomButton);
	ModeSwitchButton->OnClicked.AddDynamic(this, &ThisClass::OnClickModeSwitchButton);
	
	RoomPlayerCountSlider->OnValueChanged.AddDynamic(this, &ThisClass::OnChangePlayerCount);
	RoomPlayerCount->SetText(FText::FromString(FString::FromInt(
		FMath::Floor(RoomPlayerCountSlider->GetValue()))));

	PC = Cast<ALobbyPlayerController>(GetOwningPlayer());
}

void USessionCreatePopupWidget::OpenSessionCreate()
{
	// 숨겨져 있는 상태인 경우에 대한 처리
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		return;
	}
	
	SetVisibility(ESlateVisibility::Visible);
	if (PC)
	{
		PC->GetWidgetControlComponent()->OnTriggerInputKey_Esc_Notified
			.AddDynamic(this, &ThisClass::RemoveSessionCreate);
	}
}

void USessionCreatePopupWidget::RemoveSessionCreate()
{
	SetVisibility(ESlateVisibility::Hidden);
	if (PC)
	{
		PC->GetWidgetControlComponent()->OnTriggerInputKey_Esc_Notified
			.RemoveDynamic(this, &ThisClass::RemoveSessionCreate);
	}
}

void USessionCreatePopupWidget::OnClickCreateRoomButton()
{
	FSessionCreateData CreateData;
	CreateData.IsPublic = GamePublicCheckBox->GetCheckedState() == ECheckBoxState::Checked;
	CreateData.MatchType = SelectedMode;
	CreateData.MaxPlayer = FMath::Floor(RoomPlayerCountSlider->GetValue());
	CreateData.RoomName = RoomTitle->GetText().ToString();
	CreateData.OnCreateSessionCompleteDelegate = OnCreateSessionCompleteDelegate;
	
	FSessionUtil::CreateSession(CreateData);
}

void USessionCreatePopupWidget::OnSessionCreated(FName SessionName, bool IsCreateSuccess)
{
	if (IsCreateSuccess)
	{
		RemoveSessionCreate();
		GetWorld()->ServerTravel(FString("/Game/Games/Session/SessionMap?listen"));
	}
}

void USessionCreatePopupWidget::OnChangePlayerCount(float Value)
{
	RoomPlayerCount->SetText(FText::FromString(FString::FromInt(FMath::Floor(Value))));
}

void USessionCreatePopupWidget::OnClickModeSwitchButton()
{
	SelectedMode = (SelectedMode == EMatchType::Item)
		? EMatchType::Speed : EMatchType::Item;
	
	ModeText->SetText(
		FText::FromString(
			SelectedMode == EMatchType::Item ? TEXT("아이템전") : TEXT("스피드전")));
}
