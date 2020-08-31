// Parent Header
#include "MasterExecution.hpp"


#include "Cycler.hpp"
#include "Concurrency/CyclerPool.hpp"

// When you have a proper UI module setup, setup it to bind to imgui instead.
#include "ImGui_SAL.hpp"



namespace Core::Execution
{
	using namespace Concurrency;

	PrimitiveExecuter<void()> MasterExecuter;

	Cycler MasterCycler;


	void MainCycle();


	void Initialize_MasterCycler()
	{
		MasterExecuter.Bind(MainCycle);

		MasterCycler.BindExecuter(MasterExecuter);

		//MasterCycler.AssignInterval(Duration64(1.0 / 1036.0));

		std::chrono::seconds sec(1);

		Dev::CLog(String("Interval: ") + ToString(std::chrono::duration<float64, std::ratio<1>>(1.0 / 144.0).count()));

		MasterCycler.Initiate();
	}

	void MainCycle()
	{
		using namespace SAL;

		OSAL::PollEvents();

		static Duration64 consoleUpdateDelta(0), consoleUpdateInterval(1.0 / 30.0);

		static Duration64 renderPresentDelta(0), renderPresentInterval(1.0 / 60.0);

		if (consoleUpdateDelta >= consoleUpdateInterval)
		{

			Dev::CLog_Status("Master    Delta: " + ToString(MasterCycler.GetDeltaTime().count()), 0, 0);
			Dev::CLog_Status("Render    Delta: " + ToString(renderPresentDelta.count()), 1, 0);

			if (Concurrency::CyclerPool::GetNumUnits() > 0)
			{
				for (uInt16 row = 1, col = 0, cycleIndex = 0; cycleIndex < CyclerPool::GetNumUnits(); cycleIndex++)
				{
					Dev::CLog_Status("Thread 1  Delta: " + ToString(CyclerPool::GetCycler(cycleIndex).GetDeltaTime().count()), row++, col);

					if (row == 4)
					{
						row = 0; col++;
					}

					if (col == 4) break;
				}
			}

			Dev::Console_UpdateBuffer();

			Dev::CLog_Status("Console   Delta: " + ToString(consoleUpdateDelta.count()), 2, 0);

			consoleUpdateDelta = Duration64(0);
		}
		else
		{
			consoleUpdateDelta += MasterCycler.GetDeltaTime();
		}

		if (renderPresentDelta >= renderPresentInterval)
		{
			Imgui::MakeFrame();

			Imgui::Render();

			HAL::GPU::Default_DrawFrame(EngineWindow);

			HAL::GPU::Vulkan::Render();

			HAL::GPU::Vulkan::Present();

			Imgui::Dirty_DoSurfaceStuff(EngineWindow);	

			renderPresentDelta = Duration64(0);
		}
		else
		{
			renderPresentDelta += MasterCycler.GetDeltaTime();
		}

		if (OSAL::CanClose(EngineWindow))
		{
			HAL::GPU::WaitFor_GPUIdle();

			if (Meta::UseConcurrency)
			{
				Concurrency::CyclerPool::RequestShutdown();
			}
			else
			{
				MasterCycler.Lapse();
			}
		}

		if (Meta::UseConcurrency)
		{
			// Query module states to see if its safe for the master cycler to shutdown.
			if (Concurrency::CyclerPool::IsShutdown())
			{
				MasterCycler.Lapse();
			}
		}
	}
}
