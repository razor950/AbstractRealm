/*
GPU Hardware Abstraction Layer


*/



#pragma once




// Engine

#include "GPU_HAL_CoreDefs.hpp"
#include "HAL/Vulkan/GPU_Vulkan.hpp"

#include "LAL/LAL.hpp"

#include "Meta/AppInfo.hpp"
#include "Meta/Config/HAL_Config.hpp"

#include "OSAL/OSAL.hpp"



namespace HAL
{
	namespace GPU
	{
		// Usings

		using namespace LAL;

		using Meta::AppVersion;


		// Functionality

		// Submodule Related

		/*
		Loads the GPU HAL submodule.

		Note: This prepares the submodule for use of its related functionality supported.
		*/
		void Load();

		/*
		Unloads the GPU HAL submodule.

		Note: Unloading the submodule is not possible unless the GPU is not being used.
		Please make sure the GPU is properly deinitialized with the application first.
		*/
		void Unload();



		// GPU Related


		/*
		Initializes the essential object instances to provide interfacing to the GPU.

		_appName: Name to represent this application to the GPU.
		_version: Version of the application.
		*/
		void Initialize_GPUComms(RoCStr _appName, AppVersion _version);

		void Cease_GPUComms();

		void WaitFor_GPUIdle();

		/*
		Provides the render context for the provided window.

		Note: Render contexts are different depending on GPU API. You must check the GPU_API in use and cast the render context reference to its associated type.
		*/
		ptr<ARenderContext> GetRenderContext(ptr<OSAL::Window> _window);

		// Quick and dirty functionality. Due to lack of better implementation or time to make it.
		namespace Dirty
		{
			/*
			Does a quick and dirty GPU initialization for rendering.

			Note: Only works for one window.
			*/
			void GetRenderReady(ptr<OSAL::Window> _window);

			void DrawFrame(ptr<OSAL::Window> _window);

			/*
			Deinitialize of the Dirty_GetRenderReady setup.
			*/
			void DeinitializeRenderReady(ptr<OSAL::Window> _window);

			void ReinitializeRenderer(ptr<OSAL::Window> _window);
		}
	}
}
