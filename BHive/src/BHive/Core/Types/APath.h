#pragma once

namespace BHive
{
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
		WinPath operator= (const WinPath& Other);

	private:
		void copy(ANSICHAR* to, const ANSICHAR* from);
		Scope<ANSICHAR[]> substring(uint64 start, uint64 end);
		int64 find_first_of(std::vector<ANSICHAR> x);
		int64 find_last_of(std::vector<ANSICHAR> x);

	private:
		Scope<ANSICHAR[]> m_Path;
		Scope<ANSICHAR[]> m_Name;
		Scope<ANSICHAR[]> m_Ext;
		bool m_Directory;
		uint64 m_Length;
	};
}