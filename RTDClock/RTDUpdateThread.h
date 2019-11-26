/*
@brief		데이터 갱신 스레드
@date		2019/11/26 kim,jk, d0nzs00n@gmail.com
*/
#ifndef __RTD_UPDATE_THREAD_H__
#define __RTD_UPDATE_THREAD_H__

#include "../rtdexam_i.h"

class CRTDUpdateThread {
public:
	CRTDUpdateThread();
	virtual ~CRTDUpdateThread();

	bool Run(IRTDUpdateEvent* pCallBack);
	void Stop();
	bool IsRunning();

	unsigned int _on_thread();
private:
	unsigned int m_threadId;
	bool m_bStop;
	IRTDUpdateEvent* m_pCallback;
	HANDLE m_hThread;
};

#endif // __RTD_UPDATE_THREAD_H__