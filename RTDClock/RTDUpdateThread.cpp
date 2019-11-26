#include "stdafx.h"
#include "RTDUpdateThread.h"
#include <process.h>

static unsigned int __stdcall _rtd_thread(void* vp);

CRTDUpdateThread::CRTDUpdateThread():m_threadId(0), m_bStop(false), m_hThread(nullptr), m_pCallback(nullptr) {

}

CRTDUpdateThread::~CRTDUpdateThread() {

}

bool CRTDUpdateThread::Run(IRTDUpdateEvent* pCallBack) {
	if(!pCallBack)
		return false;

	m_pCallback = pCallBack;
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, _rtd_thread, (void*)this, 0, &m_threadId);
	m_bStop = m_hThread != 0 ? false:true;
	return m_hThread != 0;
}

bool  CRTDUpdateThread::IsRunning() {
	if(m_hThread) 
		return WaitForSingleObject(m_hThread, 0)==WAIT_TIMEOUT;
	return false;
}

void CRTDUpdateThread::Stop() {
	if(!m_hThread)
		return;

	m_bStop = true;

	DWORD ret = WaitForSingleObject(m_hThread, INFINITE);
	m_hThread = nullptr;
	m_threadId = 0;
}

unsigned int CRTDUpdateThread::_on_thread() {
	if(m_pCallback) {

		// 1초 간격으로 갱신 알림
		while(m_bStop==false) {
			m_pCallback->UpdateNotify();
			Sleep(1000);
		}
	}
	return 0;
}

unsigned int __stdcall _rtd_thread(void* vp) {
	if(CRTDUpdateThread* p = (CRTDUpdateThread*)vp)
		return p->_on_thread();
	return 0;
}