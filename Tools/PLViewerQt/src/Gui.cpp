/*********************************************************\
 *  File: Gui.cpp                                        *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
	PL_WARNING_DISABLE(4127)	// "warning C4127: conditional expression is constant"
	#include <QtCore/qurl.h>
	#include <QtCore/qfilesystemwatcher.h>
	#include <QtGui/qevent.h>
	#include <QtGui/qlabel.h>
	#include <QtGui/qmenubar.h>
	#include <QtGui/qstatusbar.h>
	#include <QtGui/qfiledialog.h>
	#include <QtGui/qinputdialog.h>
	#include <QtGui/qdesktopservices.h>
PL_WARNING_POP
#include <PLCore/Log/Log.h>
#include <PLCore/File/Url.h>
#include <PLCore/Base/Class.h>
#include <PLCore/System/System.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneQueries/SQByClassName.h>
#include <PLEngine/SceneCreator/SceneCreatorLoadableType.h>
#include <PLFrontendQt/Frontend.h>
#include <PLFrontendQt/QtStringAdapter.h>
#include <PLFrontendQt/FrontendMainWindow.h>
#include <PLFrontendQt/ConstructFileFilter.h>
#include <PLFrontendQt/DockWidget/DockWidget.h>
#include <PLFrontendQt/DockWidget/DockWidgetManager.h>
#include "ApplicationQt.h"
#include "GuiPicking.h"
#include "Gui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
using namespace PLEngine;
using namespace PLFrontendQt;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Gui::Gui(ApplicationQt &cApplication) :
	EventHandlerCameraFound(&Gui::OnCameraFound, this),
	m_pApplication(&cApplication),
	m_pGuiPicking(nullptr),
	m_pQFileSystemWatcher(new QFileSystemWatcher()),
	// Menu bar
	m_pQActionReload(nullptr),
	m_pQActionAutomaticReload(nullptr),
	m_pQMenuCamera(nullptr),
	m_pQActionGroupCamera(nullptr),
	m_pQMenuWindow(nullptr),
	m_pQActionGroupWindow(nullptr),
	// Status bar
	m_pQLabelStatusBar(nullptr)
{
	connect(m_pQFileSystemWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(QtSlotFileChanged(const QString&)));

	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();
	if (pFrontendMainWindow) {
		// Initialize the main window
		InitMainWindow(*pFrontendMainWindow);
	}
}

/**
*  @brief
*    Destructor
*/
Gui::~Gui()
{
	// Destroy the GUI picking instance
	if (m_pGuiPicking)
		delete m_pGuiPicking;

	// Destroy the Qt file system watcher instance
	delete m_pQFileSystemWatcher;
}

/**
*  @brief
*    Returns the owner application
*/
ApplicationQt &Gui::GetApplication() const
{
	return *m_pApplication;
}

/**
*  @brief
*    Get frontend main window
*/
FrontendMainWindow *Gui::GetFrontendMainWindow() const
{
	// Get Qt frontend implementation
	PLFrontendQt::Frontend *pFrontendQt = static_cast<PLFrontendQt::Frontend*>(m_pApplication->GetFrontend().GetImpl());
	if (pFrontendQt) {
		// Return the frontend main window
		return pFrontendQt->GetMainWindow();
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Sets whether or not the GUI is currently enabled
*/
void Gui::SetEnabled(bool bEnabled)
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();
	if (pFrontendMainWindow) {
		// State change?
		if (pFrontendMainWindow->isEnabled() != bEnabled) {
			// Set new enabled state of the Qt main window
			pFrontendMainWindow->setEnabled(bEnabled);

			// Perform a dock widget manager broadcast
			pFrontendMainWindow->GetDockWidgetManager().CallDockWidgetsMethod("SetSceneContainer", Params<void, SceneContainer*>(bEnabled ? m_pApplication->GetScene() : nullptr));

			// Remove all files from the Qt file system watcher instance
			m_pQFileSystemWatcher->removePaths(m_pQFileSystemWatcher->files());
		}

		// Is the GUI enabled?
		if (bEnabled) {
			// Create the GUI picking
			if (!m_pGuiPicking)
				m_pGuiPicking = new GuiPicking(*this);

			// Setup the update interval of the Qt main window (in milliseconds)
			pFrontendMainWindow->SetUpdateInterval(10);

			// Update reload Qt action
			const String sResourceFilename = m_pApplication->GetResourceFilename();
			m_pQActionReload->setEnabled(sResourceFilename.GetLength() != 0);

			// Add files to the Qt file system watcher instance
			if (sResourceFilename.GetLength() && m_pQActionAutomaticReload && m_pQActionAutomaticReload->isChecked())
				m_pQFileSystemWatcher->addPath(QtStringAdapter::PLToQt(Url(sResourceFilename).GetNativePath()));
		} else {
			// Disable the timed update of the Qt main window
			pFrontendMainWindow->SetUpdateInterval(0);

			// Destroy the GUI picking
			if (m_pGuiPicking) {
				delete m_pGuiPicking;
				m_pGuiPicking = nullptr;
			}
		}
	}
}

/**
*  @brief
*    Sets the state text
*/
void Gui::SetStateText(const String &sText)
{
	// Update the Qt label shown in the status bar of the Qt main window
	if (m_pQLabelStatusBar)
		m_pQLabelStatusBar->setText(QtStringAdapter::PLToQt(sText));
}

/**
*  @brief
*    Opens a dialog in order to give the user a choice between multiple options
*/
String Gui::InputDialog(const String &sTitle, const String &sText, const Array<String> &lstOptions) const
{
	// Construct Qt string list
	QStringList cQStringList;
	for (uint32 i=0; i<lstOptions.GetNumOfElements(); i++)
		cQStringList << QtStringAdapter::PLToQt(lstOptions[i]);

	// Create Qt input dialog
	QInputDialog cQInputDialog(GetFrontendMainWindow(), Qt::Tool);
	cQInputDialog.setWindowTitle(tr(sTitle));
	cQInputDialog.setLabelText(tr(sText));
	cQInputDialog.setComboBoxItems(cQStringList);

	{ // Usability: Set dialog width so we can see the complete title at once and disable dialog resize
		const int nWidth = cQInputDialog.fontMetrics().boundingRect(cQInputDialog.windowTitle()).width() + 80;
		QSize cQSize = cQInputDialog.size();
		if (cQSize.width() < nWidth)
			cQSize.setWidth(nWidth);
		cQInputDialog.setFixedSize(cQSize);
	}

	// Open Qt input dialog
	return (cQInputDialog.exec() == QDialog::Accepted) ? QtStringAdapter::QtToPL(cQInputDialog.textValue()) : "";
}

/**
*  @brief
*    Updates the GUI
*/
void Gui::Update()
{
	// Perform the informativ picking
	if (m_pGuiPicking)
		m_pGuiPicking->PerformInformativPicking();
}


//[-------------------------------------------------------]
//[ Public virtual QObject methods                        ]
//[-------------------------------------------------------]
bool Gui::eventFilter(QObject *pQObject, QEvent *pQEvent)
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();

	// Handle Qt main window events
	if (pQObject == GetFrontendMainWindow()) {
		// Mouse button double click (QMouseEvent)
		if (pQEvent->type() == QEvent::MouseButtonDblClick) {
			// Cast the received event to QMouseEvent
			QMouseEvent *pQMouseEvent = static_cast<QMouseEvent*>(pQEvent);

			// Left mouse button?
			if (pQMouseEvent->button() == Qt::LeftButton) {
				// Perform picking
				if (m_pGuiPicking) {
					SceneNode *pSceneNode = m_pGuiPicking->PerformPicking();

					// Perform a dock widget manager broadcast
					pFrontendMainWindow->GetDockWidgetManager().CallDockWidgetsMethod("SelectObject", Params<void, Object*>(pSceneNode));

					// Done - filter the event out, i.e. stop it being handled further
					return true;
				}
			}
		}
	}

	// Pass the event on to the parent class
	return QObject::eventFilter(pQObject, pQEvent);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initializes the main window
*/
void Gui::InitMainWindow(QMainWindow &cQMainWindow)
{
	// This Qt object should receive events from the Qt main window
	cQMainWindow.installEventFilter(this);

	{ // Menu bar
		{ // Setup the file menu
			QMenu *pQMenu = cQMainWindow.menuBar()->addMenu(tr("&File"));

			{ // Setup the load action
				QAction *pQAction = new QAction(tr("L&oad"), &cQMainWindow);
				connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredLoad()));
				pQAction->setShortcut(tr("Ctrl+L"));
				pQMenu->addAction(pQAction);
			}

			{ // Setup the reload action
				m_pQActionReload = new QAction(tr("R&eload"), &cQMainWindow);
				connect(m_pQActionReload, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredReload()));
				m_pQActionReload->setShortcut(tr("F5"));
				pQMenu->addAction(m_pQActionReload);
			}

			{ // Setup the automatic reload action
				m_pQActionAutomaticReload = new QAction(tr("A&utomatic reload"), &cQMainWindow);
				m_pQActionAutomaticReload->setCheckable(true);
				m_pQActionAutomaticReload->setChecked(true);
				connect(m_pQActionAutomaticReload, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredAutomaticReload()));
				pQMenu->addAction(m_pQActionAutomaticReload);
			}

			// Add a separator
			pQMenu->addSeparator();

			{ // Setup the exit action
				QAction *pQAction = new QAction(tr("E&xit"), &cQMainWindow);
				pQAction->setShortcuts(QKeySequence::Quit);
				connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredExit()));
				pQAction->setShortcut(tr("Ctrl+Q"));
				pQMenu->addAction(pQAction);
			}
		}

		{ // Setup the camera menu
			m_pQMenuCamera = cQMainWindow.menuBar()->addMenu(tr("&Camera"));
			connect(m_pQMenuCamera, SIGNAL(aboutToShow()), this, SLOT(QtSlotAboutToShowMenuCamera()));

			// Menu is filled when it's about to show
		}

		{ // Setup the window menu
			m_pQMenuWindow = cQMainWindow.menuBar()->addMenu(tr("&Window"));
			connect(m_pQMenuWindow, SIGNAL(aboutToShow()), this, SLOT(QtSlotAboutToShowMenuWindow()));

			// Menu is filled when it's about to show
		}

		{ // Setup the tools menu
			QMenu *pQMenu = cQMainWindow.menuBar()->addMenu(tr("&Tools"));

			{ // Setup the log action
				QAction *pQAction = new QAction(tr("Open log file"), &cQMainWindow);
				connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredOpenLogFile()));
				pQMenu->addAction(pQAction);
			}
		}

		{ // Setup the help menu
			QMenu *pQMenu = cQMainWindow.menuBar()->addMenu(tr("&Help"));

			{ // Setup the open PixelLight website action
				QAction *pQAction = new QAction(tr("Open PixelLight Website"), &cQMainWindow);
				connect(pQAction, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredOpenPixelLightWebsite()));
				pQMenu->addAction(pQAction);
			}
		}
	}

	{ // Status bar
		// Create the Qt label shown in the status bar of the Qt main window and add it to Qt main window status bar
		m_pQLabelStatusBar = new QLabel();
		cQMainWindow.statusBar()->addWidget(m_pQLabelStatusBar);
	}
}

/**
*  @brief
*    Called when a camera scene node was found
*/
void Gui::OnCameraFound(SceneQuery &cQuery, SceneNode &cSceneNode)
{
	// Camera Qt menu there?
	if (m_pQMenuCamera) {
		// Add camera to the menu
		QAction *pQAction = m_pQMenuCamera->addAction(QtStringAdapter::PLToQt(cSceneNode.GetAbsoluteName()));
		pQAction->setCheckable(true);
		if (reinterpret_cast<SceneNode*>(m_pApplication->GetCamera()) == &cSceneNode)
			pQAction->setChecked(true);
		m_pQActionGroupCamera->addAction(pQAction);
	}
}

/**
*  @brief
*    Fills the window menu recursivity
*/
uint32 Gui::FillMenuWindowRec(QMenu &cQMenu, const String &sBaseClass)
{
	// Number of checked items
	uint32 nCheckedItems = 0;

	// Get a list of RTTI classes derived from the current base class
	List<const Class*> lstClasses;
	ClassManager::GetInstance()->GetClasses(lstClasses, sBaseClass, NonRecursive, NoBase, IncludeAbstract);
	ConstIterator<const Class*> cIterator = lstClasses.GetConstIterator();
	while (cIterator.HasNext()) {
		// Get the current RTTI class
		const Class *pClass = cIterator.Next();

		// Abstract class?
		if (pClass->HasConstructor()) {
			// Class can be instanced

			// Add action
			QAction *pQAction = cQMenu.addAction(tr(pClass->GetProperties().Get("Title")));
			pQAction->setCheckable(true);
			pQAction->setData(QtStringAdapter::PLToQt(pClass->GetClassName()));
			m_pQActionGroupWindow->addAction(pQAction);

			// One can also derive from classes which can be instanced, but by convention this should not be done for RTTI dock widgets

			// Get the Qt main window
			FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();

			// Is there currently an instance of this dock widget already visible?
			DockWidget *pDockWidget = pFrontendMainWindow ? pFrontendMainWindow->GetDockWidgetManager().GetFirstDockWidget(pClass->GetClassName()) : nullptr;
			if (pDockWidget && pDockWidget->IsQDockWidgetVisible()) {
				pQAction->setChecked(true);
				nCheckedItems++;
			} else {
				pQAction->setChecked(false);
			}
		} else {
			// Abstract class will result in a sub-menu, but only if at least one none abstract class is derived from it
			List<const Class*> lstDerivedClasses;
			ClassManager::GetInstance()->GetClasses(lstDerivedClasses, pClass->GetClassName(), Recursive, NoBase, NoAbstract);
			if (lstDerivedClasses.GetNumOfElements()) {
				// Add sub-menu
				QMenu *pQMenuSub = cQMenu.addMenu(tr(pClass->GetProperties().Get("Title")));

				// Automatically fill the Qt window menu by using RTTI information
				nCheckedItems += FillMenuWindowRec(*pQMenuSub, pClass->GetClassName());
			}
		}
	}

	// Return the number of checked items
	return nCheckedItems;
}


//[-------------------------------------------------------]
//[ Private Qt slots (MOC)                                ]
//[-------------------------------------------------------]
void Gui::QtSlotFileChanged(const QString &path)
{
	m_pApplication->LoadResource(QtStringAdapter::QtToPL(path));
}

void Gui::QtSlotTriggeredLoad()
{
	// Fill the file filter (filter example: "All Files (*);;Scene (*.scene *.SCENE);;Script (*.lua *.LUA)")
	const String sAllFiles = QtStringAdapter::QtToPL(tr("All Files"));
	String sFileFilter = sAllFiles + " (*)";
	sFileFilter += ";;";
	sFileFilter += ConstructFileFilter::ByLoadableType(QtStringAdapter::QtToPL(tr("Scene")), "Scene");
	sFileFilter += ";;";
	sFileFilter += ConstructFileFilter::ByScriptLanguages(QtStringAdapter::QtToPL(tr("Script")));

	{ // Fill the file filter - the highly dynamic part
		// Get a list of loadable types were it's possible to use a scene creator in order to
		// configure a scene, everything else is not interesting in this viewer
		Array<String> lstLoadableTypes;
		SceneCreatorLoadableType::GetLoadableTypes(lstLoadableTypes);

		// Fill the file filter
		if (lstLoadableTypes.GetNumOfElements()) {
			sFileFilter += ";;";
			for (uint32 i=0; i<lstLoadableTypes.GetNumOfElements(); i++) {
				// Get the current loadable type...
				const String &sType = lstLoadableTypes[i];

				// ... and add it to the file filter
				sFileFilter += ConstructFileFilter::ByLoadableType(QtStringAdapter::QtToPL(tr(sType)), sType);

				// Will another file filter follow?
				if (i < lstLoadableTypes.GetNumOfElements()-1)
					sFileFilter += ";;";
			}
		}
	}

	// Open a file dialog were the user can choose a filename
	QString sQSelectedFilter;
	const QString sQFilename = QFileDialog::getOpenFileName(GetFrontendMainWindow(), "", "", QtStringAdapter::PLToQt(sFileFilter), &sQSelectedFilter);

	// Filename chosen?
	if (sQFilename.length()) {
		// Get the loadable type
		String sType;
		String sSelectedFilter = QtStringAdapter::QtToPL(sQSelectedFilter);
		const int nIndex = sSelectedFilter.IndexOf(" (");
		if (nIndex > -1)
			sType = sSelectedFilter.GetSubstring(0, nIndex);

		// Load the resource
		m_pApplication->LoadResource(QtStringAdapter::QtToPL(sQFilename), (sType != sAllFiles) ? sType : "");
	}
}

void Gui::QtSlotTriggeredReload()
{
	const String sResourceFilename = m_pApplication->GetResourceFilename();
	if (sResourceFilename.GetLength())
		m_pApplication->LoadResource(sResourceFilename);
}

void Gui::QtSlotTriggeredAutomaticReload()
{
	// Remove all files from the Qt file system watcher instance
	m_pQFileSystemWatcher->removePaths(m_pQFileSystemWatcher->files());

	// Update the Qt file system watcher instance
	if (m_pQActionAutomaticReload && m_pQActionAutomaticReload->isChecked()) {
		// Add files to the Qt file system watcher instance
		const String sResourceFilename = m_pApplication->GetResourceFilename();
		if (sResourceFilename.GetLength())
			m_pQFileSystemWatcher->addPath(QtStringAdapter::PLToQt(Url(sResourceFilename).GetNativePath()));
	}
}

void Gui::QtSlotTriggeredExit()
{
	// Shut down the application
	m_pApplication->Exit(0);
}

void Gui::QtSlotAboutToShowMenuCamera()
{
	// Camera Qt menu there?
	if (m_pQMenuCamera) {
		// Clear the previous content - this is not performance critical so there's no reason to implement a
		// more complex solution like e.g. updating the menu entries as soon as there's a change within the scene
		m_pQMenuCamera->clear();
		if (m_pQActionGroupCamera)
			delete m_pQActionGroupCamera;
		m_pQActionGroupCamera = new QActionGroup(GetFrontendMainWindow());
		connect(m_pQActionGroupCamera, SIGNAL(selected(QAction*)), this, SLOT(QtSlotSelectedCamera(QAction*)));

		// Automatically fill the Qt camera menu by using the cameras which are within the scene

		// Get the scene container with our 'concrete scene'
		SceneContainer *pSceneContainer = m_pApplication->GetScene();
		if (pSceneContainer) {
			// Create a scene query instance
			SQByClassName *pSceneQuery = static_cast<SQByClassName*>(pSceneContainer->CreateQuery("PLScene::SQByClassName"));
			if (pSceneQuery) {
				// Setup the regular expression of the scene query
				pSceneQuery->SetRegEx(RegEx("PLScene::SNCamera"));

				// Connect event handler
				pSceneQuery->SignalSceneNode.Connect(EventHandlerCameraFound);

				// Perform the scene query
				pSceneQuery->PerformQuery();

				// Destroy scene query instance
				pSceneContainer->DestroyQuery(*pSceneQuery);
			}
		}
	}
}

void Gui::QtSlotSelectedCamera(QAction *pQAction)
{
	// Get the scene container with our 'concrete scene'
	SceneContainer *pSceneContainer = m_pApplication->GetScene();
	if (pSceneContainer) {
		// Get the chosen camera scene node
		SceneNode *pSceneNode = pSceneContainer->GetByName(QtStringAdapter::QtToPL(pQAction->text()));
		if (pSceneNode && pSceneNode->IsCamera()) {
			// Set the new application camera
			m_pApplication->SetCamera(reinterpret_cast<SNCamera*>(pSceneNode));
		}
	}
}

void Gui::QtSlotAboutToShowMenuWindow()
{
	// Window Qt menu there?
	if (m_pQMenuWindow) {
		// Get the Qt main window
		FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();

		// Clear the previous content - this is not performance critical so there's no reason to implement a
		// more complex solution like e.g. updating the menu entries as soon as there's a change within the scene
		m_pQMenuWindow->clear();
		if (m_pQActionGroupWindow)
			delete m_pQActionGroupWindow;
		m_pQActionGroupWindow = new QActionGroup(pFrontendMainWindow);
		m_pQActionGroupWindow->setExclusive(false);
		connect(m_pQActionGroupWindow, SIGNAL(selected(QAction*)), this, SLOT(QtSlotSelectedWindow(QAction*)));

		// Setup the hide all action
		QAction *pQActionHideAll = new QAction(tr("Hide all"), pFrontendMainWindow);
		connect(pQActionHideAll, SIGNAL(triggered()), this, SLOT(QtSlotTriggeredWindowHideAll()));
		pQActionHideAll->setShortcut(tr("Ctrl+H"));
		m_pQMenuWindow->addAction(pQActionHideAll);

		// Add a separator
		m_pQMenuWindow->addSeparator();

		// Automatically fill the Qt window menu by using RTTI information
		if (!FillMenuWindowRec(*m_pQMenuWindow, "PLFrontendQt::DockWidget"))
			pQActionHideAll->setEnabled(false);	// Disable "Hide all" menu entry if there's currently nothing to hide
	}
}

void Gui::QtSlotTriggeredWindowHideAll()
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();
	if (pFrontendMainWindow) {
		// All registered dock widgets
		pFrontendMainWindow->GetDockWidgetManager().HideDockWidgets();

		// Usability: When hiding all windows at once, do also unselect the current object (if one is selected)
		// -> A kind of "Disable edit mode and switch back to business as usual"
		// -> Perform a dock widget manager broadcast
		pFrontendMainWindow->GetDockWidgetManager().CallDockWidgetsMethod("SelectObject", Params<void, Object*>(nullptr));
	}
}

void Gui::QtSlotSelectedWindow(QAction *pQAction)
{
	// Get the Qt main window
	FrontendMainWindow *pFrontendMainWindow = GetFrontendMainWindow();
	if (pFrontendMainWindow) {
		// Get the RTTI dock widget class name
		const String sClassName = QtStringAdapter::QtToPL(pQAction->data().toString());

		// Show the requested dock widget
		pFrontendMainWindow->GetDockWidgetManager().ShowDockWidget(sClassName);
	}
}

void Gui::QtSlotTriggeredOpenLogFile()
{
	// Use "PLCore::System::Execute()" to open the log file which is usually a simple text file
	// -> "QDesktopServices::openUrl(QtStringAdapter::PLToQt(Log::GetInstance()->GetFilename()));" didn't work for me
	System::GetInstance()->Execute(Log::GetInstance()->GetFilename(), "");
}

void Gui::QtSlotTriggeredOpenPixelLightWebsite()
{
	QDesktopServices::openUrl(QUrl("http://www.pixellight.org"));
}
