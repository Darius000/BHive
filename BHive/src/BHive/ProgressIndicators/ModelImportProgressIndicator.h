#pragma once

#include <assimp/ProgressHandler.hpp>

namespace BHive
{
	/* Progress bar handler for models being imported*/
	class MeshImportProgressIndicator : public Assimp::ProgressHandler
	{

	public:

		MeshImportProgressIndicator();

		void UpdateFileRead(int currentStep, int numberOfSteps) override;


		bool Update(float percentage = -1.f) override;

		void UpdatePostProcess(int currentStep, int numberOfSteps) override;

		void UpdateFileWrite(int currentStep, int numberOfSteps) override;
	};
}