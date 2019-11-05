#pragma once

namespace BHive
{
	typedef uint64 index;
	typedef uint64 size;

	class WinPath
	{
	
	public:
		WinPath();
		WinPath(const ANSICHAR* path);
		WinPath(const WinPath& other);
		~WinPath();

		const ANSICHAR* GetName() const { return m_Name.get(); }
		const ANSICHAR* GetPath() const { return m_Path.get(); }
		const ANSICHAR* GetExtension() const { return m_Ext.get(); }

		bool IsDirectory() { return m_Directory; }

		const ANSICHAR* operator*() const { return m_Path.get(); }

	private:
		void copy(ANSICHAR* to, const ANSICHAR* from);
		Scope<ANSICHAR[]> substring(index start, index end);
		index find_first_of(ANSICHAR x);
		index find_last_of(ANSICHAR x);
		
	private:
		Scope<ANSICHAR[]> m_Path;
		Scope<ANSICHAR[]> m_Name;
		Scope<ANSICHAR[]> m_Ext;
		bool m_Directory;
		size m_Length;
	};
}