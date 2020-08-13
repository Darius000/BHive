#pragma once

namespace BHive
{
	class WinPath
	{

	public:
		WinPath();
		WinPath(const ANSICHAR* path);
		WinPath(const WinPath& other);
		WinPath(WinPath&& other) noexcept;
		~WinPath();

		const ANSICHAR* GetName() const { return m_Name; }
		const ANSICHAR* GetPath() const { return m_Path; }
		const ANSICHAR* GetExtension() const { return m_Ext; }
		const ANSICHAR* GetFullPath() const { return m_FullPath; }
		uint64 GetLength() const { return m_Length; }

		bool IsDirectory() { return m_Directory; }

		const ANSICHAR* operator*() const { return m_FullPath; }
		ANSICHAR& operator[](uint64 index){ return m_Path[index]; }
		const ANSICHAR& operator[](uint64 index) const { return m_Path[index]; }
		WinPath& operator= (const WinPath& Other);
		friend WinPath operator+(const WinPath& a, const ANSICHAR* b);
		friend bool operator==(const WinPath& a, const WinPath& b);
		friend std::iostream& operator >> (std::iostream& io, const WinPath& path);
		friend std::ifstream& operator << (std::ifstream& io, WinPath& path);

	private:
		void ConstructPath();

	private:
		ANSICHAR* m_Path = nullptr;
		ANSICHAR* m_FullPath = nullptr;
		ANSICHAR* m_Name = nullptr;
		ANSICHAR* m_Ext = nullptr;

		bool m_Directory = false;
		uint64 m_Length = 0;
	};

	inline WinPath operator+(const ANSICHAR* a, const WinPath& b)
	{
		return (std::string(a) + std::string(b.GetFullPath())).c_str();
	}

	inline WinPath operator+(const WinPath& a, const ANSICHAR* b)
	{
		return (std::string(a.GetPath()) + std::string(b)).c_str();
	}

	inline std::iostream& operator >> (std::iostream& io, const WinPath& path)
	{
		return io >> path.GetFullPath();
	}

	inline std::ifstream& operator << (std::ifstream& io, WinPath& path)
	{
		return io << path;
	}

	inline bool operator==(const WinPath& a, const WinPath& b)
	{
		if (a.GetLength() != b.GetLength())
			return false;

		for (uint64 i = 0; i < a.GetLength(); i++)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}

		return true;
	}

	namespace StringLibrary
	{
		inline void copy(ANSICHAR*& to, const ANSICHAR* from);
		inline ANSICHAR* substring(ANSICHAR* from, uint64 start, uint64 end);
		inline int64 find_first_of(ANSICHAR* from, std::vector<ANSICHAR> x);
		inline int64 find_last_of(ANSICHAR* from, std::vector<ANSICHAR> x);
		inline int64 GetLength(const ANSICHAR* from);
		
	}
}