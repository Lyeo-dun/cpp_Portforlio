#include "Message.h"
#include "DoubleBuffer.h"

Message::Message()
{
}

Message::~Message()
{
}

void Message::Initialize()
{
	Texture[0] = (char*)" ______  __ __   ____  ____   __  _      __ __   ___   __ __  __ ";
	Texture[1] = (char*)"|      ||  |  | /    ||    \\ |  |/ ]    |  |  | /   \\ |  |  ||  |";
	Texture[2] = (char*)"|      ||  |  ||  o  ||  _  ||  ' /     |  |  ||     ||  |  ||  |";
	Texture[3] = (char*)"|_|  |_||  _  ||     ||  |  ||    \\     |  ~  ||  O  ||  |  ||__|";

	TransInfo.Scale = Vector3((float)strlen(Texture[2]), 4);
	TransInfo.Position = Vector3(TransInfo.Scale.x / 2, 10.5f- TransInfo.Scale.y / 2);

	Color = 0;
	ColorAlpaValue = 0;
}

void Message::Update()
{
	if (TransInfo.Position.x < 41)
	{
		TransInfo.Position.x += Speed;
	}
	else
	{
		TransInfo.Position.x = 41.0f;
	}

	if (ColorAlpaValue < 3)
	{
		ColorAlpaValue += 0.2f;
	}

	switch ((int)ColorAlpaValue)
	{
	case 0:
		Color = 0;
		break;
	case 1:
		Color = 8;
		break;
	case 2:
		Color = 7;
		break;
	case 3:
		Color = 15;
		break;
	}
}

void Message::Render()
{
	for (int i = 0; i < 4; i++)
	{
		DoubleBuffer::GetInstance()->WriteBuffer(int(TransInfo.Position.x - TransInfo.Scale.x/2), int(TransInfo.Position.y - TransInfo.Scale.y / 2) + i, Texture[i], Color);
	}
}

void Message::Release()
{
}
