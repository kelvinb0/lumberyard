/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#ifndef __EMSTUDIO_ANIMGRAPHNODEGROUPWINDOW_H
#define __EMSTUDIO_ANIMGRAPHNODEGROUPWINDOW_H

#include <MCore/Source/StandardHeaders.h>
#include <MCore/Source/Array.h>
#include <MCore/Source/UnicodeString.h>

#include <EMotionFX/Source/NodeGroup.h>

#include "../StandardPluginsConfig.h"
#include "AttributesWindow.h"
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>

#include <EMotionFX/CommandSystem/Source/AnimGraphConnectionCommands.h>
#include <EMotionFX/CommandSystem/Source/AnimGraphCommands.h>
#include <EMotionFX/CommandSystem/Source/AnimGraphParameterCommands.h>
#include <EMotionFX/CommandSystem/Source/AnimGraphNodeCommands.h>

#include <MysticQt/Source/SearchButton.h>


namespace EMStudio
{
    // forward declarations
    class AnimGraphPlugin;

    class NodeGroupRenameWindow
        : public QDialog
    {
        Q_OBJECT
                 MCORE_MEMORYOBJECTCATEGORY(NodeGroupRenameWindow, MCore::MCORE_DEFAULT_ALIGNMENT, MEMCATEGORY_STANDARDPLUGINS);

    public:
        NodeGroupRenameWindow(QWidget* parent, EMotionFX::AnimGraph* animGraph, const MCore::String& nodeGroup);

    private slots:
        void TextEdited(const QString& text);
        void Accepted();

    private:
        EMotionFX::AnimGraph*  mAnimGraph;
        MCore::String           mNodeGroup;
        QLineEdit*              mLineEdit;
        QPushButton*            mOKButton;
        //QLabel*               mErrorMsg;
    };

    class NodeGroupWindow
        : public QWidget
    {
        Q_OBJECT
                 MCORE_MEMORYOBJECTCATEGORY(NodeGroupWindow, EMFX_DEFAULT_ALIGNMENT, MEMCATEGORY_STANDARDPLUGINS_ANIMGRAPH);

    public:
        NodeGroupWindow(AnimGraphPlugin* plugin);
        ~NodeGroupWindow();

        void Init();

    private slots:
        void OnAddNodeGroup();
        void OnRemoveSelectedGroups();
        void OnRenameSelectedNodeGroup();
        void OnClearNodeGroups();
        void OnIsVisible(int state);
        //void OnNameEdited(QTableWidgetItem* item);
        void OnColorChanged(const QColor& color);
        //void OnCellChanged(int row, int column);
        void SearchStringChanged(const QString& text);
        void UpdateInterface();

    private:
        virtual void keyPressEvent(QKeyEvent* event) override;
        virtual void keyReleaseEvent(QKeyEvent* event) override;

        virtual void contextMenuEvent(QContextMenuEvent* event) override;

        uint32 FindGroupIndexByWidget(QObject* widget) const;
        //bool ValidateName(EMotionFX::AnimGraphNodeGroup* nodeGroup, const char* newName) const;

        MCORE_DEFINECOMMANDCALLBACK(CommandAnimGraphAddNodeGroupCallback);
        MCORE_DEFINECOMMANDCALLBACK(CommandAnimGraphAdjustNodeGroupCallback);
        MCORE_DEFINECOMMANDCALLBACK(CommandAnimGraphRemoveNodeGroupCallback);

        CommandAnimGraphAddNodeGroupCallback*      mCreateCallback;
        CommandAnimGraphAdjustNodeGroupCallback*   mAdjustCallback;
        CommandAnimGraphRemoveNodeGroupCallback*   mRemoveCallback;

        struct WidgetLookup
        {
            MCORE_MEMORYOBJECTCATEGORY(NodeGroupWindow::WidgetLookup, EMFX_DEFAULT_ALIGNMENT, MEMCATEGORY_STANDARDPLUGINS_ANIMGRAPH);
            QObject*    mWidget;
            uint32      mGroupIndex;

            WidgetLookup(QObject* widget, uint32 index)
            {
                mWidget     = widget;
                mGroupIndex = index;
            }
        };

        AnimGraphPlugin*               mPlugin;
        QTableWidget*                   mTableWidget;
        QVBoxLayout*                    mVerticalLayout;
        QPushButton*                    mAddButton;
        QPushButton*                    mRemoveButton;
        QPushButton*                    mClearButton;
        MysticQt::SearchButton*         mFindWidget;
        MCore::Array<WidgetLookup>      mWidgetTable;
    };
} // namespace EMStudio


#endif
