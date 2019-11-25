#pragma once

namespace BHive
{
	struct ProfilerResult
	{
		BString m_Name;
		long long m_Start, m_End;
		uint32 m_ThreadID;
	};

	struct InstrumentionSession
	{
		BString m_Name;
	};

	class Instrumentor
	{
	public:
		Instrumentor()
			:m_CurrentSession(nullptr), m_ProfileCount(0)
		{

		}

		void BeginSession(const BString& name, const WinPath& filepath = "results.json")
		{
			m_OutputStream.open(*filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentionSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void WriteProfile(const ProfilerResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",";

			BString name = result.m_Name;
			Replace(name.begin(), name.end(),'"', '\'');

			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.m_End - result.m_Start) << ",";
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << result.m_ThreadID << ",";
			m_OutputStream << "\"ts\":" << result.m_Start;
			m_OutputStream << "}";

			m_OutputStream.flush();
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\":{},\"traceEvents\":[";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor* instance = new Instrumentor();
			return *instance;
		}

	private:
		InstrumentionSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int32 m_ProfileCount;
	};

	//template<typename Fn>
	struct InstrumentionTimer
	{
		InstrumentionTimer(const ANSICHAR* name/*, Fn&& func*/)
			:m_Name(name), m_Stopped(false)//, m_Func(func)
		{
			m_StartPoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentionTimer()
		{
			if(!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimePoint = std::chrono::high_resolution_clock::now();
			
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
			float duration = (end - start) * .001f;

			m_Stopped = true;

			 uint32 threadID = (uint32)std::hash<std::thread::id>{}(std::this_thread::get_id());
			//m_Func({ m_Name, duration });
			//ProfilerResults.push_back({m_Name, start, end});
			Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID});
			//BH_CORE_WARN("Timer: {0} took {1} milliseconds, {2} microseconds to complete!", m_Name, ms, duration);
		}

		//static std::vector<ProfilerResult> GetProfilerResults() { return ProfilerResults; }
		//static std::vector<ProfilerResult> ProfilerResults;
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
		const ANSICHAR* m_Name;
		bool m_Stopped;
		//Fn m_Func;
		
	};
}

#define BH_PROFILING 1
#if BH_PROFILING 
#define BH_PROFILE_BEGIN_SESSION(name, filepath) BHive::Instrumentor::Get().BeginSession(name, filepath)
#define BH_PROFILE_END_SESSION() BHive::Instrumentor::Get().EndSession()
#define BH_PROFILE_SCOPE(name) BHive::InstrumentionTimer timer##__LINE__(name)
#define BH_PROFILE_FUNCTION() BH_PROFILE_SCOPE(__FUNCSIG__)
#else
#define BH_PROFILE_BEGIN_SESSION(name, filepath) 
#define BH_PROFILE_END_SESSION()
#define BH_PROFILE_SCOPE(name) 
#define BH_PROFILE_FUNCTION() 
#endif // BH_PROFILING
