// dllmain.h : Declaration of module class.

class CPLPluginActiveXModule : public CAtlDllModuleT< CPLPluginActiveXModule >
{
public :
	DECLARE_LIBID(LIBID_PLPluginActiveXLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PLPLUGINACTIVEX, "{88DAA3D7-0C15-47CF-AA81-5BEB67FC68A6}")
};

extern class CPLPluginActiveXModule _AtlModule;
