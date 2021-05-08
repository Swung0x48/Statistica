#include "Statistica.h"

#include "Command.h"

IMod* BMLEntry(IBML* bml) {
	return new Statistica(bml);
}

void PrintTime(Hiperf_Timer* hiperf_timer, IBML* bml) {
	char buffer[100];
	sprintf(buffer, "%I64d", hiperf_timer->GetTime());
	bml->SendIngameMessage(buffer);
	sprintf(buffer, "%lf ms", bml->GetTimeManager()->GetLastDeltaTime());
	bml->SendIngameMessage(buffer);
}

void Statistica::OnLoad()
{
	/*auto thr = std::thread([&]() {
		while (true) {
			m_bml->GetRenderContext()->Clear();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			m_bml->GetRenderManager()->Process();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	});
	thr.detach();*/
	//m_bml->GetTimeManager()->SetTimeScaleFactor(2.0);
	m_bml->RegisterCommand(new Command());
	//m_bml->GetInputManager()->EnableKeyboardRepetition(TRUE);
}

void Statistica::OnProcess()
{
	char buffer[200];
	//if (m_bml->IsIngame()) {
		if (m_bml->GetInputManager()->IsKeyDown(CKKEY_TAB, &_inputLat)) {
			auto* ball = m_bml->Get3dObjectByName("Ball_Wood");
			VxRect viewport;
			m_bml->GetRenderContext()->GetViewRect(viewport);
			VxRect rect;
			ball->GetRenderExtents(rect);
			GetLogger()->Info("%.2f, %.2f, %.2f, %.2f", rect.top, rect.bottom, rect.left, rect.right);
			GetLogger()->Info("%.2f, %.2f, %.2f, %.2f", viewport.top, viewport.bottom, viewport.left, viewport.right);
			GetLogger()->Info("%.2f, %.2f, %.2f, %.2f", rect.top / viewport.bottom, rect.bottom / viewport.bottom, rect.left / viewport.right, rect.right / viewport.right);
			panel_->SetPosition(Vx2DVector(rect.left / viewport.right, rect.top / viewport.bottom));
			//m_bml->GetRenderContext()->GetAttachedCamera()->ComputeProjectionMatrix(proj_mat_);
			
			/*proj_mat_ = m_bml->GetRenderContext()->GetProjectionTransformationMatrix();
			VxMatrix world = m_bml->GetRenderContext()->GetWorldTransformationMatrix();
			VxMatrix world_to_view = m_bml->GetRenderContext()->GetViewTransformationMatrix();
			GetLogger()->Info(m_bml->GetRenderContext()->GetAttachedCamera()->GetName());
			VxMatrix view_proj;
			Vx3DMultiplyMatrix(view_proj, proj_mat_, world_to_view);

			VxVector4 pos4;
			ball->GetPosition(&pos4);
			pos4[3] = 1;
			VxVector4 vec4;
			Vx3DMultiplyMatrixVector4(&vec4, view_proj, pos4);
			GetLogger()->Info("3D coord: %.2f, %.2f, %.2f, %.2f", pos4.x, pos4.y, pos4.z, pos4.w);
			GetLogger()->Info("clipped: %.2f, %.2f, %.2f, %.2f", vec4.x, vec4.y, vec4.z, vec4.w);
			if (fabs(vec4.w) < 0.1)
				return;
			VxVector NDC(vec4.x / vec4.w, vec4.y / vec4.w, vec4.z / vec4.w);
			GetLogger()->Info("normalized: %.2f, %.2f, %.2f", NDC.x, NDC.y, NDC.z);
			const float WIDTH = 1.0f;
			const float HEIGHT = 1.0f;

			float x = (WIDTH / 2 * NDC.x) + (NDC.x + WIDTH / 2);
			float y = 1 -(-(HEIGHT / 2 * NDC.y) + (NDC.y + HEIGHT / 2));
			GetLogger()->Info("%.2f, %.2f", x, y);
			panel_->SetPosition(Vx2DVector(x, y));

			/*VxVector vec;
			m_bml->GetRenderContext()->Transform(&vec, &pos4);
			GetLogger()->Info("Trans: %.2f, %.2f, %.2f", vec.x, vec.y, vec.z);*/
		}

		/*if (m_bml->IsIngame()) {
			auto* cur_level = m_bml->GetArrayByName("CurrentLevel");
			CK3dObject* ball = static_cast<CK3dObject*>(cur_level->GetElementObject(0, 1));
			VxVector pos;
			VxQuaternion rot;
			ball->GetPosition(&pos);
			ball->GetQuaternion(&rot);
			GetLogger()->Info("pos: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
			GetLogger()->Info("rot: (%.2f, %.2f, %.2f, %.2f)", rot.x, rot.y, rot.z, rot.w);
		}*/
}

void Statistica::OnBallNavInactive()
{
	//std::this_thread::yield();
}

void Statistica::OnLoadObject(CKSTRING filename, BOOL isMap, CKSTRING masterName,
	CK_CLASSID filterClass, BOOL addtoscene, BOOL reuseMeshes, BOOL reuseMaterials,
	BOOL dynamic, XObjectArray* objArray, CKObject* masterObj) {
	if (isMap) {
		
	}
	//m_bml->GetTimeManager()->SetTimeScaleFactor(.2);

}

void Statistica::OnStartLevel()
{
	hiperf_timer_.Stop();
	hiperf_timer_.Reset();
	on_start_level_ = true;
	PrintTime(&hiperf_timer_, m_bml);
}

void Statistica::OnPreEndLevel()
{
	hiperf_timer_.Stop();
	if (on_start_level_)
		hiperf_timer_.Reset();
	PrintTime(&hiperf_timer_, m_bml);
}

void Statistica::OnCounterActive()
{
	hiperf_timer_.Start();
	PrintTime(&hiperf_timer_, m_bml);
}

void Statistica::OnCounterInactive()
{
	hiperf_timer_.Stop();
	PrintTime(&hiperf_timer_, m_bml);
}

void Statistica::OnPauseLevel()
{
	hiperf_timer_.Stop();
	PrintTime(&hiperf_timer_, m_bml);
}

void Statistica::OnUnpauseLevel()
{
	PrintTime(&hiperf_timer_, m_bml);
	hiperf_timer_.Start();
}

void Statistica::OnUnload()
{

}

void Statistica::OnPreCheckpointReached()
{
	PrintTime(&hiperf_timer_, m_bml);
}

void Statistica::OnPreStartMenu()
{
	gui_ = new BGui::Gui();
	panel_ = gui_->AddPanel("panel", VxColor(0, 0, 0), 0.0f, 0.0f, 0.03f, 0.03f);
	panel_->SetZOrder(100);
	panel_->SetVisible(true);
}


