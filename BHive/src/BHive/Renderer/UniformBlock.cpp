#include "BHivePCH.h"
#include "UniformBlock.h"

namespace BHive
{
	UniformBlock::UniformBlock(const ANSICHAR* name, size_t blocksize, BindingPoint binding)
	{		
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
		glBufferData(GL_UNIFORM_BUFFER, blocksize, nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferRange(GL_UNIFORM_BUFFER, binding, m_Id, 0, blocksize);
		m_Name = name;
		m_Binding = binding;
	}

	void UniformBlock::Bind(const Ref<Shader>& shader)
	{
		uint32 blockIndex = glGetUniformBlockIndex(shader->GetID(), m_Name);
		if(blockIndex != -1)
		{
			glUniformBlockBinding(shader->GetID(), blockIndex, m_Binding);
		}
	}

}