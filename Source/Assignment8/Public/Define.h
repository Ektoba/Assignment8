#pragma once
DECLARE_LOG_CATEGORY_EXTERN(HACKED_LOG, Log, All);

// �� �Լ��� ȣ��� �Լ��� �̸��� ������ ��ũ�η� Stringȭ ��Ŵ
#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

// ���� CALLINFO�� �Բ� �ƹ� ������ ���� �α׸� ��� ��ũ��
#define LOG_S(Verbosity) UE_LOG(HACKED_LOG, Verbosity, TEXT("%s"), *LOG_CALLINFO)

// CALLINFO�� �Բ� �ؽ�Ʈ�� �α׸� ��� ��ũ��
#define LOG(Verbosity, Format, ...) UE_LOG(HACKED_LOG, Verbosity, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(TEXT(Format), ##__VA_ARGS__))

// Screen���ٰ� LOG�� ���� ��� ��ũ��
#define	LOG_SCREEN(Format, ...) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT(Format), ##__VA_ARGS__))

// ���� �Լ��� �ð��� �ִ� ��ũ��. Tick���� DeltaTime�� ���ڷ� ������ ���� ����.
#define	LOG_SCREEN_T(Time, Format, ...) GEngine->AddOnScreenDebugMessage(-1, Time, FColor::Blue, FString::Printf(TEXT(Format), ##__VA_ARGS__))

// LOG�� Verbosity�� ���ڿ��� ���� ��ũ��ȭ ��Ų��. 
#define LOG_WARNING(Format, ...) UE_LOG(HACKED_LOG, Warning, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define LOG_ERROR(Format, ...) UE_LOG(HACKED_LOG, Error, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(TEXT(Format), ##__VA_ARGS__))

// assert()�� ���� ����� �뵵�� ��밡���� ��ũ��. ...���� retval�� ��.
#define CHECK(Expr, ...) {if(!(Expr)) {LOG(Error, "ASSERTION : %s", "'"#Expr"'"); return __VA_ARGS__;}}