// PixelLightCtrl.h : Declaration of the PixelLightCtrl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "PLFrontendActiveX_i.h"
#include <PLCore/Frontend/FrontendImpl.h>
#include <PLCore/Frontend/FrontendContext.h>
#include <PLCore/Frontend/FrontendPixelLight.h>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif


// PixelLightCtrl
class ATL_NO_VTABLE PixelLightCtrl :
	public PLCore::FrontendImpl,
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IPixelLightCtrl, &IID_IPixelLightCtrl, &LIBID_PLFrontendActiveXLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<PixelLightCtrl>,
	public IOleControlImpl<PixelLightCtrl>,
	public IOleObjectImpl<PixelLightCtrl>,
	public IOleInPlaceActiveObjectImpl<PixelLightCtrl>,
	public IViewObjectExImpl<PixelLightCtrl>,
	public IOleInPlaceObjectWindowlessImpl<PixelLightCtrl>,
#ifdef _WIN32_WCE // IObjectSafety is required on Windows CE for the control to be loaded correctly
	public IObjectSafetyImpl<PixelLightCtrl, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
#endif
	public CComCoClass<PixelLightCtrl, &CLSID_PixelLightCtrl>,
	public CComControl<PixelLightCtrl>
{
public:
	PixelLightCtrl();

	virtual ~PixelLightCtrl();

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_PIXELLIGHTCTRL)


BEGIN_COM_MAP(PixelLightCtrl)
	COM_INTERFACE_ENTRY(IPixelLightCtrl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
#ifdef _WIN32_WCE // IObjectSafety is required on Windows CE for the control to be loaded correctly
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
#endif
END_COM_MAP()

BEGIN_PROP_MAP(PixelLightCtrl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY_TYPE("Property Name", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()


BEGIN_MSG_MAP(PixelLightCtrl)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	CHAIN_MSG_MAP(CComControl<PixelLightCtrl>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	// No RTTI interface, this frontend is not allowed to be instanced by using the RTTI


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::FrontendImpl functions        ]
	//[-------------------------------------------------------]
	private:
		virtual int Run(const PLCore::String &sExecutableFilename, const PLCore::Array<PLCore::String> &lstArguments) override;
		virtual PLCore::handle GetNativeWindowHandle() const override;
		virtual void Redraw() override;
		virtual void Ping() override;
		virtual int GetX() const override;
		virtual int GetY() const override;
		virtual PLCore::uint32 GetWidth() const override;
		virtual PLCore::uint32 GetHeight() const override;
		virtual void SetPositionSize(int nX, int nY, PLCore::uint32 nWidth, PLCore::uint32 nHeight) override;
		virtual bool GetToggleFullscreenMode() const override;
		virtual void SetToggleFullscreenMode(bool bToggleFullscreenMode) override;
		virtual bool GetFullscreenAltTab() const override;
		virtual void SetFullscreenAltTab(bool bAllowed) override;
		virtual bool IsFullscreen() const override;
		virtual void SetFullscreen(bool bFullscreen) override;
		virtual void RefreshFullscreen() override;
		virtual bool IsMouseOver() const override;
		virtual int GetMousePositionX() const override;
		virtual int GetMousePositionY() const override;
		virtual bool IsMouseVisible() const override;
		virtual void SetMouseVisible(bool bVisible) override;
		virtual void SetTrapMouse(bool bTrap) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Update trap mouse if required
		*
		*  @note
		*    - Should be called after window position or size was changed
		*/
		void UpdateTrapMouse();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		HWND						m_hFrontendWnd;						/**< Window handle of the plugin container */
		bool						m_bFrontendApplicationInitialized;	/**< Frontend application successfully initialized? */
		bool						m_bMouseVisible;					/**< Is the mouse cursor visible? */
		bool						m_bTrapMouse;						/**< Trap mouse? */
		PLCore::FrontendContext		m_cFrontendContext;
		PLCore::FrontendPixelLight	m_cFrontend;

// IPixelLightCtrl
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	HRESULT OnDrawAdvanced(ATL_DRAWINFO &di);
	LRESULT OnCreate(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnEraseBkgnd(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnSize(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
};

OBJECT_ENTRY_AUTO(__uuidof(PixelLightCtrl), PixelLightCtrl)
