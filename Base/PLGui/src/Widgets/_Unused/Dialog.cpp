/*********************************************************\
 *  File: Dialog.cpp                                     *
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
#include "PLGui/Widgets/Windows/Dialog.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4355) // "'this' : used in base member initializer list"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLGui {


//[-------------------------------------------------------]
//[ Class implementation                                  ]
//[-------------------------------------------------------]
pl_implement_class(Dialog)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Dialog::Dialog(Widget *pParent) : Window(pParent),
	m_nResult(0)
{
	// Set title
	SetTitle("Dialog Box");

	// Dialogs are usually not resizable
	SetResizable(false);

	// Dialogs only have the 'Close' button
	SetSystemButtons(SystemButtonClose);
}

/**
*  @brief
*    Destructor
*/
Dialog::~Dialog()
{
}

/**
*  @brief
*    Show dialog
*/
void Dialog::ShowDialog()
{
	// Emit event
	EventShowDialog.Emit();

	// Make dialog visible
	SetVisible(true);
}

/**
*  @brief
*    Close dialog
*/
void Dialog::CloseDialog(int nResult)
{
	// Set result value
	m_nResult = nResult;

	// Call virtual function
	OnCloseDialog(m_nResult);
}

/**
*  @brief
*    Get result value
*/
int Dialog::GetResult() const
{
	// Return result value
	return m_nResult;
}


//[-------------------------------------------------------]
//[ Protected virtual Widget functions                    ]
//[-------------------------------------------------------]
void Dialog::OnClose()
{
	// Call base implementation
	ContainerWidget::OnClose();

	// Close dialog
	CloseDialog(-1);
}


//[-------------------------------------------------------]
//[ Public virtual Dialog functions                       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when dialog has been closed
*/
void Dialog::OnCloseDialog(int nResult)
{
	// Emit event
	EventCloseDialog.Emit(m_nResult);

	// Close dialog
	Destroy();
}


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
