// dllmain.h : Declaration of module class.

class CPLFrontendActiveXModule : public CAtlDllModuleT< CPLFrontendActiveXModule >
{
public :
	DECLARE_LIBID(LIBID_PLFrontendActiveXLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PLFRONTENDACTIVEX, "{88DAA3D7-0C15-47CF-AA81-5BEB67FC68A6}")
};

extern class CPLFrontendActiveXModule _AtlModule;
