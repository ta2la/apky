//
// Copyright (C) 2019 Petr Talla. [petr.talla@gmail.com]
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
#include "T2lEasyViewCad.h"

#include "T2lHtmlTabsRegistry.h"

#include "TcCmdEngine.h"
#include "TcSysInfo.h"

#include "FlowLayout.h"

#include "T2lEasyViewTml.h"

#include <QGraphicsProxyWidget>

#include <QToolBar>
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QIcon>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextStream>
#include <QDesktopServices>
#include "T2lEasyViewHtml.h"
#include "T2lEasyViewButton.h"
#include <QStackedLayout>

#include "TcCmdTransl.h"

#include <iostream>

#include <QApplication>
#include <T2lEasyViewTab.h>

using namespace T2l;
using namespace std;

#define TAB_HEIGHT 40

//=============================================================================
EasyViewCad::EasyViewCad()
{
/*    setWindowFlags(Qt::WindowStaysOnTopHint);

    resize(700, 250);
    setWindowTitle("LabeL T2L");
    setWindowIconText("LabeL T2L");

    //=======================================================
    tabs_ = new QWidget(this);
    tabs_->move(0,0);
    tabs_->resize(10000, TAB_HEIGHT);

    main_ = new QWidget(this);
    main_->move(0,TAB_HEIGHT);

    //=======================================================
    stacked_ = new QStackedLayout();

    main_->setLayout(stacked_);

    //=======================================================
    tabs_->show();
    main_->show();*/

    createTab("dir");
    createTab("ofiles");
    createTab("cad", createCad());
    createTab("exed");
    createTab("about");
}

//=============================================================================
QWidget* EasyViewCad::createCad()
{
    QVBoxLayout *layout = new QVBoxLayout;

    std::string cmd("tab_set_"); cmd += "toolbar";
    EXECUTE(cmd.c_str());
    TcHtmlViewTab* tab = HtmlTabsRegistry::instance().tabGet_("toolbar");

    EasyViewTml* tabWidget = loadTml(tab->content(), "toolbar");
    tabWidget->resize(800, 300);
    layout->addWidget(tabWidget);

    QWidget *separator = new QWidget;
    separator->setFixedHeight(2);
    separator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    separator->setStyleSheet(QString("background-color: #c0c0c0;"));
    layout->addWidget(separator);

    tabWidget = loadTml("empty", "acmd");
    tabWidget->resize(800, 300);
    layout->addWidget(tabWidget);

    tabWidget = loadTml("empty", "icmd");
    tabWidget->resize(800, 300);
    layout->addWidget(tabWidget);

    layout->addStretch();

    QWidget* cadWidget = new QWidget();
    cadWidget->setLayout(layout);

    return cadWidget;
}

//=============================================================================
/*void EasyViewCad::createTab( const char* id, QWidget* widget )
{
    EasyViewTab* tab = new EasyViewTab(this, id, widget );
    tabItems_.append(tab);
    stacked_->addWidget(tab->widget_);
}*/

//=============================================================================
/*void EasyViewCad::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    tabs_->resize(width(), TAB_HEIGHT);
    main_->resize(width(), height()-TAB_HEIGHT);
}

//=============================================================================
void EasyViewCad::onEmptyQueue()
{
    for (int i = 0; i < tabItems_.count(); i++) {
        EasyViewTab* tab = tabItems_.at(i);

        if (active_ == tab->id_) {
            tab->button_->setText(QString(">> ") + tab->id_.c_str());
            stacked_->setCurrentWidget(tab->widget_);
        }
        else {
            tab->button_->setText(QString() + tab->id_.c_str());
        }
    }
}*/

//=============================================================================
/*void EasyViewCad::urlHandler_(const QUrl& url)
{
    QString urlScheme = url.scheme();
    QString urlFragment = url.fragment();
    QString urlHost = url.fragment();
    QString urlPath = url.path();
    QString urlQuery = url.query();

    if (url.scheme() != "tcview" ) return;

    QString cmd(QUrl::fromPercentEncoding(url.fragment().toLatin1()));
    TcCmdTransl::xcall( cmd.toUtf8().data(), true );
}

//=============================================================================
void EasyViewCad::urlHandlerHtml_(const QUrl& url)
{
    urlHandler_(url);
}*/

//=============================================================================
/*EasyViewTml* EasyViewCad::loadTml(QString content, const char* id)
{
    EasyViewTml* widget = new EasyViewTml(id);
    widget->load(content);
    widget->show();

    return widget;
}*/

//=============================================================================
