#include "Statistica.h"

#include "Command.h"

IMod* BMLEntry(IBML* bml) {
	return new Statistica(bml);
}

void Statistica::OnLoad()
{
	m_bml->RegisterCommand(new Command());
}


