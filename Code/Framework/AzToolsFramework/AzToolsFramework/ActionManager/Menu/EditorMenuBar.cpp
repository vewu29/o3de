/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzToolsFramework/ActionManager/Menu/EditorMenuBar.h>
#include <AzToolsFramework/ActionManager/Menu/MenuManagerInterface.h>

#include <QMenuBar>

namespace AzToolsFramework
{
    EditorMenuBar::EditorMenuBar()
        : m_menuBar(new QMenuBar())
    {
    }
    
    void EditorMenuBar::AddMenu(int sortKey, AZStd::string menuIdentifier)
    {
        m_menus.insert({ sortKey, AZStd::move(menuIdentifier) });
        RefreshMenuBar();
    }

    QMenuBar* EditorMenuBar::GetMenuBar()
    {
        return m_menuBar;
    }

    const QMenuBar* EditorMenuBar::GetMenuBar() const
    {
        return m_menuBar;
    }

    void EditorMenuBar::RefreshMenuBar()
    {
        m_menuBar->clear();

        for (const auto& elem : m_menus)
        {
            if(QMenu* menu = m_menuManagerInterface->GetMenu(elem.second))
            {
                m_menuBar->addMenu(menu);
            }
        }
    }

    void EditorMenuBar::Initialize()
    {
        m_menuManagerInterface = AZ::Interface<MenuManagerInterface>::Get();
        AZ_Assert(m_menuManagerInterface, "EditorMenuBar - Could not retrieve instance of MenuManagerInterface");
    }

} // namespace AzToolsFramework
