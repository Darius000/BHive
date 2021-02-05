#include "BHivePCH.h"
#include "UniformBlock.h"

namespace BHive
{
	UniformBlock::UniformBlock(const ANSICHAR* name, size_t blocksize)
	{		
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
		glBufferData(GL_UNIFORM_BUFFER, blocksize, nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_Id, 0, blocksize);
		m_Name = name;
	}

	void UniformBlock::Bind(const Ref<Shader>& shader, uint32 slot)
	{
		uint32 blockIndex = glGetUniformBlockIndex(shader->GetID(), m_Name);
		glUniformBlockBinding(shader->GetID(), blockIndex, slot);
	}

}