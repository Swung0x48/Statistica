#include "Statistica.h"

#include "Command.h"

IMod* BMLEntry(IBML* bml) {
	return new Statistica(bml);
}

void Statistica::OnLoad()
{
	m_bml->RegisterCommand(new Command());
	m_bml->GetInputManager()->EnableKeyboardRepetition(TRUE);
}

void Statistica::OnProcess()
{
	char buffer[200];
	//if (m_bml->IsIngame()) {
		if (m_bml->GetInputManager()->IsKeyDown(CKKEY_CAPITAL, &_inputLat)) {
			/*m_bml->GetCKContext()->GetProfileStats(&stats);
			int num = m_bml->GetInputManager()->GetNumberOfKeyInBuffer();
			int time = stats.TotalFrameTime;*/
			//sprintf(buffer, "Number: %d, Time: %dms, Latency: %lfms, KeyboardRepetitionEnabled: %d", num, time, (double)time / (double)num, m_bml->GetInputManager()->IsKeyboardRepetitionEnabled() ? 1 : 0);
			sprintf(buffer, "%f", m_bml->GetTimeManager()->GetTime());
			m_bml->SendIngameMessage(buffer);
		}
	//}
}


