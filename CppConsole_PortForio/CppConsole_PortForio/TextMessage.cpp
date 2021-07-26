#include "TextMessage.h"
#include "ObjectFactory.h"
#include "UnderMessage.h"
#include "Message.h"

TextMessage::TextMessage()
{
}

TextMessage::~TextMessage()
{
	Release();
}

void TextMessage::Initialize()
{
	TopText = ObjectFactory<Message>::CreateObject();
	UnderText = ObjectFactory<UnderMessage>::CreateObject();

	TransInfo.Position = Vector3(41, 11);
	TransInfo.Scale = Vector3(TopText->GetScale().x, 7);
}

void TextMessage::Update()
{
	TopText->Update();
	UnderText->Update();
}

void TextMessage::Render()
{
	TopText->Render();
	UnderText->Render();
}

void TextMessage::Release()
{
	SAFE_RELEASE(TopText);
	SAFE_RELEASE(UnderText);
}