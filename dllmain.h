// dllmain.h : Declaration of module class.

class CrtdexamModule : public ATL::CAtlDllModuleT< CrtdexamModule >
{
public :
	DECLARE_LIBID(LIBID_rtdexamLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_RTDEXAM, "{AD71AD19-4B47-4F8B-A94B-4D1092B4C277}")
};

extern class CrtdexamModule _AtlModule;
