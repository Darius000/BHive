#pragma once

namespace BHive
{
	
	class UniformBlock
	{
	public:
		using BlockID = uint32;
		using BindingPoint = uint32;

		UniformBlock() = delete;
		UniformBlock(const UniformBlock&) = default;
		UniformBlock(const ANSICHAR* name, size_t blocksize, BindingPoint binding);

		void Bind(const Ref<class Shader>& shader);

		template<typename T>
		void SendData(size_t offset, const T* uniform);

		BlockID m_Id;
		const ANSICHAR* m_Name;
		BindingPoint m_Binding;
	};

	template<typename T>
	void UniformBlock::SendData(size_t offset, const T* uniform)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(T), (void*)uniform);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

}