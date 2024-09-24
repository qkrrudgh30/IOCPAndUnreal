#pragma once

#include "CharacterBase.h"

class USClientSession;
class USRoom;

class USPlayerCharacter : public USCharacterBase
{
public:
	USPlayerCharacter();
	virtual ~USPlayerCharacter();

public:
	weak_ptr<USClientSession> ClientSession;

};

