//
// Copyright (C) 2013 Petr Talla. [petr.talla@gmail.com]
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
//cmds
#include "TcCmds_cmdEx.h"
#include "TcCmds_cmdEngine.h"
#include "TcCmds_htmlView.h"
#include "T2lCmdsTab_cad.h"
#include "T2lCmds_cad.h"
#include "T2lCmds_signal.h"
#include "T2lCmds_new_functionality.h"
//#include "T2lCadObject_refFile.h"

//cad
#include "T2lTentativeImplementationCad.h"
#include "T2lCadExeSettings.h"

//infrastructure
#include <TcObjectRegistry.h>
#include <TcHtmlViewTabbed.h>
#include "T2lHtmlTabsRegistry.h"
#include <TcCmdTransl.h>
#include <TcLock.h>
#include <TcCmdExecuteLate.h>
#include <TcCmdEngine.h>
#include <T2lScript.h>
#include "T2lEasyViewCad.h"
#include "T2lCadObject_line3.h"

#include "T2lStoredFactory.h"
#include "T2lCadLine.h"
#include "T2lCadObject_image.h"
#include "T2lCadObject_symbol.h"
#include "T2lCadObject_text.h"
#include "T2lCadObject_dimm.h"
#include "T2lCmdAlias.h"
#include "T2lCmdAliasCol.h"
#include "T2lCmds_cad.h"
#include "T2lCmds_cad_exe.h"
#include "T2lCmds_scene3d.h"

#include "T2lCmdsTab_dir.h"
#include "T2lCmdsTab_about.h"
#include "TcCmds_dirBrowser.h"

// hg
#include "T2lCmdQueue.h"

// qt
#include <QApplication>

// std
#include <iostream>

using namespace std;
using namespace T2l;

//=============================================================================
int main(int argc, char *argv[]) {
    // output
    cout << "##################################" << endl;
    cout << "area analyzer started" << endl;

    // registration
    TcObjectRegistry::registry();
    TcCmds_cmdEx::registerCmds_();
    TcCmds_cmdEngine::registerCmds_();
    TcCmds_htmlView::registerCmds_();
    CmdsTab_dir::registerCmds_();
    CmdsTab_about::registerCmds_();
    CmdsTab_cad::registerCmds_();
    Cmds_cad::registerCmds_();
    Cmds_cad_exe::registerCmds_();
    Cmds_new_functionality::registerCmds_();
    TcCmds_dirBrowser::registerCmds_();
    Cmds_scene3d::registerCmds_();

    StoredFactory::instance().add(new CadLine( Point2Col<double>(), nullptr ));
    StoredFactory::instance().add(new CadObject_symbol( Point2F(), nullptr ));
    StoredFactory::instance().add(new CadObject_image( "ble.png", Point2<double>(0, 0), nullptr ));
    StoredFactory::instance().add(new CadObject_text( "null", Point2<double>(-100000, 0), nullptr ));
    StoredFactory::instance().add(new CadObject_dimm( Point2F(0, 0), nullptr ));
    StoredFactory::instance().add(new CadObject_line3( Point2F(0, 0), nullptr, 0, 0 ) );


    Queue::instance()->set(&CmdQueue::queue());
    CmdQueue::queue().setTentaiveImplementation(new TentativeImplementationCad());

    Script::run("configs", "main");
    Script::run("configs", "macros");

    QApplication a(argc, argv);

    CadExeSettings::instance().exeDir_ = QCoreApplication::applicationFilePath();

    TcHtmlViewTabbed::mainView().hide();

    EasyViewCad* test = new EasyViewCad();
    test->resize(900,450);
    test->show();

    TcCmdEngine::engine().queuedSetOn();
    TcCmdExecuteLate exeLate;
    return a.exec();
}

//=============================================================================


