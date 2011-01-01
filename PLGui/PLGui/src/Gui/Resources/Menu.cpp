/*********************************************************\
 *  File: Menu.cpp                                       *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLGui/Gui/Resources/Menu.h"
#include "PLGui/Gui/Resources/MenuSeparator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGui {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Menu::Menu(Gui &cGui) : MenuItem(cGui, TypeMenu)
{
}

/**
*  @brief
*    Destructor
*/
Menu::~Menu()
{
	// Delete all items
	Clear();
}

/**
*  @brief
*    Clear menu
*/
void Menu::Clear()
{
	// Delete menu items
	for (uint32 i=0; i<m_lstItems.GetNumOfElements(); i++) {
		// May the item be destroyed?
		if (!m_lstNoDeletion.IsElement(m_lstItems[i])) {
			// Delete item
			delete m_lstItems[i];
		}
	}

	// Clear lists
	m_lstItems.Clear();
	m_lstNoDeletion.Clear();
}

/**
*  @brief
*    Get items
*/
const Container<MenuItem*> &Menu::GetItems() const
{
	// Return item list
	return m_lstItems;
}

/**
*  @brief
*    Get item that belongs to a certain shortcut
*/
int32 Menu::GetShortcutItem(char nShortcut) const
{
	// Check all items
	for (uint32 i=0; i<m_lstItems.GetNumOfElements(); i++) {
		// Get item
		MenuItem *pItem = m_lstItems[i];

		// Is this the shortcut we search for?
		char nItemShortcut = pItem->GetShortcut();
		if (nItemShortcut != '\0' && nItemShortcut == nShortcut) {
			// Yes!
			return i;
		}
	}

	// No item with that shortcut found
	return -1;
}

/**
*  @brief
*    Adds a new item to the menu
*/
void Menu::AddItem(MenuItem *pItem, bool bDelete)
{
	// Add item
	m_lstItems.Add(pItem);

	// Shall the item not be destroyed?
	if (!bDelete) {
		m_lstNoDeletion.Add(pItem);
	}
}

/**
*  @brief
*    Adds a new item to the menu at a specific index
*/
void Menu::AddItemAtIndex(uint32 nIndex, MenuItem *pItem, bool bDelete)
{
	// Check index
	if (nIndex < m_lstItems.GetNumOfElements()) {
		// Add item at given index
		m_lstItems.AddAtIndex(pItem, nIndex);
	} else {
		// Add item at end of list
		m_lstItems.Add(pItem);
	}

	// Shall the item not be destroyed?
	if (!bDelete) {
		m_lstNoDeletion.Add(pItem);
	}
}

/**
*  @brief
*    Removes an item from the menu
*/
void Menu::RemoveItem(MenuItem *pItem)
{
	// Remove item
	m_lstItems.Remove(pItem);

	// May the item be destroyed?
	if (!m_lstNoDeletion.IsElement(pItem)) {
		// Delete item
		delete pItem;
	} else {
		// Remove from list
		m_lstNoDeletion.Remove(pItem);
	}
}

/**
*  @brief
*    Adds a standard item with a text
*/
MenuItem *Menu::AddItem(const PLGeneral::String &sText)
{
	// Create item
	MenuItem *pItem = new MenuItem(*m_pGui);
	pItem->SetText(sText);

	// Add item
	AddItem(pItem);

	// Return item
	return pItem;
}

/**
*  @brief
*    Adds a standard item with a text and an icon
*/
MenuItem *Menu::AddItem(const PLGeneral::String &sText, const Image &cIcon)
{
	// Create item
	MenuItem *pItem = new MenuItem(*m_pGui);
	pItem->SetText(sText);
	pItem->SetIcon(cIcon);

	// Add item
	AddItem(pItem);

	// Return item
	return pItem;
}

/**
*  @brief
*    Adds a separator item to the menu
*/
MenuItem *Menu::AddSeparator()
{
	// Create separator
	MenuItem *pItem = new MenuSeparator(*m_pGui);

	// Add item
	AddItem(pItem);

	// Return item
	return pItem;
}

/**
*  @brief
*    Adds a sub menu to the menu
*/
MenuItem *Menu::AddSubMenu(Menu *pMenu, bool bDelete)
{
	// Add item
	AddItem(pMenu, bDelete);

	// Return item
	return pMenu;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
