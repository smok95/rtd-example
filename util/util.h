#ifndef __rtd_exam_util_h__
#define __rtd_exam_util_h__

#include <string>
#include <OAIdl.h>
#include <comutil.h>

namespace util {

	struct safearray {
		// SAFEARRAY���� ���ڿ��� ����
		static bool get_string(SAFEARRAY* pArr, LONG index, OUT std::string& rValue);
	};

} // namespace util

#endif // __rtd_exam_util_h__