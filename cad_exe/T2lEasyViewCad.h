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
#pragma once

#include "T2lEasyView.h"

namespace T2l
{

class EasyViewTml;
class EasyViewButton;

//===================================================================
class EasyViewCad : public EasyView {
//===================================================================
public:
//<CONSTRUCTION>
    EasyViewCad();
    virtual ~EasyViewCad() {}

    //void createTab(const char* id, QWidget* widget = nullptr);
//<METHODS>
    //QTextBrowser* loadHtml(QString content);
    //EasyViewTml*  loadTml(QString content, const char* id = "");

    //static void activeSet(const char* value) { active_ = value; }

    QWidget* createCad();
//===================================================================
//<INTERNALS>
//<OVERRIDES>
    //virtual void onEmptyQueue();
    //virtual void resizeEvent(QResizeEvent *event);
protected:
//<DATA>
    //static std::string active_;

    //QList<EasyViewTab*> tabItems_;

    //QWidget*        tabs_;
    //QWidget*        main_;
    //QStackedLayout* stacked_;

    //QWidget*        cadWidget_;
//<QT>
    Q_OBJECT
private slots:
    //void onLinkActivated(const QString& link);
    //void urlHandler_(const QUrl& url);
    //void urlHandlerHtml_(const QUrl& url);
//<FRIENDS>
    friend class EasyViewTab;
};

} // namespace T2l
