/*
@brief		세계주요 도시 실시간 시간정보 RTD예제 클래스

			엑셀에서 사용 방법
			=RTD("RtdExam.RTDClock",,"도시이름")
			* 도시이름 목록
			"seoul","paris","la","london","newyork","bangkok"

@date		2019/11/25 kim,jk (d0nzs00n@gmail.com)
*/
#pragma once
#include "../resource.h"       // main symbols
#include "../rtdexam_i.h"
#include <map>
#include "RTDUpdateThread.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

typedef struct TimeZone {
	std::string name;		// 지역(도시명)
	const int time_offset;
}TimeZone;

typedef std::map<long, TimeZone> TopicMap;

// CRTDClock

class ATL_NO_VTABLE CRTDClock :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRTDClock, &CLSID_RTDClock>,
	public IDispatchImpl<IRtdServer, &__uuidof(IRtdServer), &LIBID_rtdexamLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRTDClock()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RTDCLOCK)


BEGIN_COM_MAP(CRTDClock)
	COM_INTERFACE_ENTRY(IRtdServer)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_pCallback = nullptr;
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	// IRtdServer Methods
	STDMETHOD(ServerStart)(IRTDUpdateEvent *CallbackObject, long *pfRes);
	STDMETHOD(ConnectData)(long TopicID, SAFEARRAY * *Strings, VARIANT_BOOL *GetNewValues, VARIANT *pvarOut);
	STDMETHOD(RefreshData)(long *TopicCount, SAFEARRAY * *parrayOut);
	STDMETHOD(DisconnectData)(long TopicID);
	STDMETHOD(Heartbeat)(long *pfRes);
	STDMETHOD(ServerTerminate)();

private:
	TopicMap m_topicMap;
	IRTDUpdateEvent* m_pCallback;
	CRTDUpdateThread m_updateThread;
};

OBJECT_ENTRY_AUTO(__uuidof(RTDClock), CRTDClock)
