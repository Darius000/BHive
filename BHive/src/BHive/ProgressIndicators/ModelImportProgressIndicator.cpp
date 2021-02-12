#include "BHivePCH.h"
#include "ModelImportProgressIndicator.h"

namespace BHive
{

	MeshImportProgressIndicator::MeshImportProgressIndicator()
	{
		
	}

	void MeshImportProgressIndicator::UpdateFileRead(int currentStep, int numberOfSteps)
	{
		
	}

	bool MeshImportProgressIndicator::Update(float percentage)
	{
		return true;
	}

	void MeshImportProgressIndicator::UpdatePostProcess(int currentStep, int numberOfSteps)
	{
		float percentage = ((float)currentStep / (float)numberOfSteps) * 100.0f;
		if(percentage == 100.0f)
		{
			BH_CORE_INFO("Complete!");
		}
		else
		{
			BH_CORE_INFO("Progress {0}%", percentage);
		}
	}

	void MeshImportProgressIndicator::UpdateFileWrite(int currentStep, int numberOfSteps)
	{

	}

}