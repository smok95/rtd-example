#include "stdafx.h"
#include "RTDClock.h"
#include "../util/util.h"
#include <time.h>

static int g_cnt = 0;

static TimeZone TimeZones[] = {
	{"Seoul"	,9	},
	{"LA"		,-8	},
	{"Paris"	,1	},
	{"London"	,0	},
	{"NewYork"	,-5	},
	{"Bangkok"	,7	}
};

// CRTDClock

STDMETHODIMP CRTDClock::ServerStart(IRTDUpdateEvent *CallbackObject, long *pfRes) {
	if(!CallbackObject || !pfRes)
		return E_POINTER;

	HRESULT hr = S_OK;
	m_pCallback = CallbackObject;

	m_pCallback->AddRef();

	if(!m_updateThread.IsRunning())
		m_updateThread.Run(m_pCallback);

	*pfRes = 1;

	return hr;
}

STDMETHODIMP CRTDClock::ConnectData(long TopicID, SAFEARRAY * *Strings, VARIANT_BOOL *GetNewValues, VARIANT *pvarOut) {
	if(!Strings || !GetNewValues || !pvarOut)
		return E_POINTER;
	HRESULT hr = S_OK;
	
	// 인자 개수 확인
	ULONG argc = (*Strings)->rgsabound[0].cElements;

	std::string input;

	*GetNewValues = (VARIANT_BOOL)TRUE;

	if(argc==1) 
		util::safearray::get_string(*Strings, 0, OUT input);
	
	time_t t = time(nullptr);

	const int HOUR = 3600;	// 3600 sec

	TimeZone* pCurZone = nullptr;

	for(size_t i=0; i<_countof(TimeZones); i++) {
		TimeZone& zone = TimeZones[i];

		if(_stricmp(zone.name.c_str(), input.c_str())==0) {
			t += zone.time_offset * HOUR;

			pCurZone = &zone;
			break;
		}
	}

	char buf[260]={0,};

	if(!pCurZone) {
		sprintf(buf, "invalid arguments.");
	}
	else {
		struct tm now = *gmtime(&t);
		sprintf(buf, "%2d:%02d:%02d (%s)", now.tm_hour, now.tm_min, now.tm_sec, pCurZone->name.c_str());
		m_topicMap.insert(std::make_pair(TopicID, *pCurZone));
	}

	_variant_t vout;
	vout.SetString(buf);
	*pvarOut = vout;

	if(m_pCallback)
		m_pCallback->UpdateNotify();


	return hr;
}

STDMETHODIMP CRTDClock::RefreshData(long *TopicCount, SAFEARRAY * *parrayOut) {
	if(!TopicCount || !parrayOut)
		return E_POINTER;

	HRESULT hr = S_OK;

	*TopicCount = (long)m_topicMap.size();

	// SafeArray 생성
	SAFEARRAYBOUND bounds[2] = {0,};
	bounds[0].cElements = 2;
	bounds[1].cElements = (ULONG)*TopicCount;

	long index[2] = {0,};

	*parrayOut = SafeArrayCreate(VT_VARIANT, 2, bounds);

	_variant_t val;

	for(auto it=m_topicMap.begin(); it!=m_topicMap.end(); ++it) {
		val = it->first;

		// 1번째값 TopicID 설정
		index[0] = 0;
		SafeArrayPutElement(*parrayOut, index, &val.GetVARIANT());

		// 2번째값 Value 설정
		{
			time_t t = time(nullptr);

			const int HOUR = 3600;	// 3600 sec
			TimeZone& zone = it->second;
			t += zone.time_offset * HOUR;

			char buf[260]={0,};

			struct tm now = *gmtime(&t);
			sprintf(buf, "%2d:%02d:%02d (%s)", now.tm_hour, now.tm_min, now.tm_sec, zone.name.c_str());

			val.SetString(buf);
		}
		index[0] = 1;
		SafeArrayPutElement(*parrayOut, index, &val.GetVARIANT());

		index[1]++;
	}
	return hr;
}

STDMETHODIMP CRTDClock::DisconnectData(long TopicID) {
	HRESULT hr = S_OK;

	// 맵에 저장된 토픽정보 삭제
	auto it = m_topicMap.find(TopicID);
	if(it==m_topicMap.end())
		return hr;

	m_topicMap.erase(it);

	if(m_topicMap.size()==0)
		m_updateThread.Stop();

	return hr;
}

STDMETHODIMP CRTDClock::Heartbeat(long *pfRes) {
	if(!pfRes)
		return E_POINTER;

	HRESULT hr = S_OK;
	*pfRes = 1;
	return hr;
}

STDMETHODIMP CRTDClock::ServerTerminate() {
	HRESULT hr = S_OK;

	if(m_pCallback) {
		m_pCallback->Release();
		m_pCallback = nullptr;
	}

	return hr;
}