#pragma once
#include <BML/BMLAll.h>

class Command: public ICommand
{
private:
	CKStats _stats;
public:
	virtual std::string GetName() override { return "stats"; };
	virtual std::string GetAlias() override { return "statistics"; };
	virtual std::string GetDescription() override { return "Profiling."; };
	virtual bool IsCheat() override { return false; };
	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override {
		if (args.size() == 1)
		{
			bml->GetCKContext()->GetProfileStats(&_stats);
			char buffer[50];
			bml->SendIngameMessage("----------");
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
		}
	}
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override {
		return args.size() == 2 ? std::vector<std::string>{ "enable", "disable" } : std::vector<std::string>{};
	};
};

