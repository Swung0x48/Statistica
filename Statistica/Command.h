#pragma once
#include <BML/BMLAll.h>

class Command: public ICommand
{
private:
	CKStats _stats;
	int _displayModeCount;
	int _pageSize = 10;
public:
	virtual std::string GetName() override { return "stats"; };
	virtual std::string GetAlias() override { return "statistics"; };
	virtual std::string GetDescription() override { return "Profiling."; };
	virtual bool IsCheat() override { return false; };
	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override {
		if (args.size() == 4)
		{
			if (args[1] == "resize") {
				int width = atoi(args[2].c_str());
				int length = atoi(args[3].c_str());
				bml->GetRenderContext()->Resize(0, 0, width, length);
				return;
			}
		}

		if (args.size() == 1)
		{
			bml->GetCKContext()->GetProfileStats(&_stats);
			char buffer[50];
			bml->SendIngameMessage("----------");
			sprintf(buffer, "ActiveObjectsExecuted: %d", _stats.ActiveObjectsExecuted);
			bml->SendIngameMessage(buffer);
			sprintf(buffer, "TotalFrameTime: %.3fms", _stats.TotalFrameTime);
			bml->SendIngameMessage(buffer);
			sprintf(buffer, "Est.InterfaceTime: %.3fms", _stats.EstimatedInterfaceTime);
			bml->SendIngameMessage(buffer);
			sprintf(buffer, "ProcessTime: %.3fms", _stats.ProcessTime);
			bml->SendIngameMessage(buffer);
			sprintf(buffer, "RenderTime: %.3fms", _stats.RenderTime);
			bml->SendIngameMessage(buffer);
			sprintf(buffer, "ParametricOperations: %.3fms", _stats.ParametricOperations);
			bml->SendIngameMessage(buffer);
			sprintf(buffer, "TotalBeh.Exec.: %.3fms", _stats.TotalBehaviorExecution);
			bml->SendIngameMessage(buffer);
			sprintf(buffer, "AnimationMgnt.: %.3fms", _stats.AnimationManagement);
			bml->SendIngameMessage(buffer);
			sprintf(buffer, "IKMgnt.: %.3fms", _stats.IKManagement);
			bml->SendIngameMessage(buffer);
			sprintf(buffer, "Beh.CodeExec.: %.3fms", _stats.BehaviorCodeExecution);
			bml->SendIngameMessage(buffer);
			bml->SendIngameMessage("----------");
			return;
		}
		if (args.size() > 1) {
			if (args[1] == "enable") {
				bml->GetCKContext()->EnableProfiling(true);
			}
			else if (args[1] == "disable") {
				bml->GetCKContext()->EnableProfiling(false);
			}
			else if (args[1] == "gpuinfo") {
				_displayModeCount = bml->GetRenderManager()->GetRenderDriverDescription(0)->DisplayModeCount;
				if (args.size() == 2) {
					bml->SendIngameMessage(std::to_string(bml->GetRenderManager()->GetRenderDriverCount()).c_str());
					bml->SendIngameMessage(bml->GetRenderManager()->GetRenderDriverDescription(0)->DriverDesc);
					bml->SendIngameMessage(std::to_string(bml->GetRenderManager()->GetRenderDriverDescription(0)->DisplayModeCount).c_str());
					bml->SendIngameMessage("See detailed display modes, use /stats gpuinfo [PageNumber].");
					return;
				}
				int selectedPage = atoi(args[2].c_str());
				if (selectedPage <= 0 || selectedPage * _pageSize > _displayModeCount)
				{
					bml->SendIngameMessage("ERR: Out of range.");
					return;
				}
				VxDisplayMode* displaymodes = bml->GetRenderManager()->GetRenderDriverDescription(0)->DisplayModes;
				char buffer[100];
				for (int i = (selectedPage - 1) * _pageSize; i < ((selectedPage * _pageSize > _displayModeCount) ? (_displayModeCount) : (selectedPage * _pageSize)); i++) {
					sprintf(buffer, "%dx%d, %dbit, %dHz", displaymodes[i].Width, displaymodes[i].Height, displaymodes[i].Bpp, displaymodes[i].RefreshRate);
					bml->SendIngameMessage(buffer);
				}
			}
			else if (args[1] == "info")
			{
				char buffer[50];
				float framerateLimit = bml->GetTimeManager()->GetFrameRateLimit();
				sprintf(buffer, "Framerate limit: %f fps", framerateLimit);
				bml->SendIngameMessage(buffer);

				float behLimit = bml->GetTimeManager()->GetBehavioralRateLimit();
				sprintf(buffer, "Behrate limit: %f lps", behLimit);
				bml->SendIngameMessage(buffer);
				
				CKDWORD options = bml->GetTimeManager()->GetLimitOptions();
				sprintf(buffer, "Limit options: 0x%08hx", options);
				bml->SendIngameMessage(buffer);

				VxDirectXData* dxInfo = bml->GetRenderContext()->GetDirectXInfo();
				sprintf(buffer, "DirectXVer: %hx", dxInfo->DxVersion);
				bml->SendIngameMessage(buffer);
			}
			else if (args[1] == "setlimit")
			{
				if (args.size() < 3)
				{
					bml->SendIngameMessage("ERR: No number specified.");
					return;
				}

				bml->GetTimeManager()->SetFrameRateLimit(atof(args[2].c_str()));
			}
			else if (args[1] == "fullscreen") {
				auto ctx = bml->GetRenderContext();
				auto error = ctx->GoFullScreen(ctx->GetHeight(), ctx->GetWidth(), -1, ctx->GetDriverIndex(), 120);
				char buffer[50]; sprintf(buffer, "%d", error);
				bml->SendIngameMessage(buffer);
			}
			else {
				bml->SendIngameMessage("ERR: Unknown command.");
				return;
			}
		}
	}
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override {
		return args.size() == 2 ? std::vector<std::string>{ "enable", "disable" } : std::vector<std::string>{};
	};
};

