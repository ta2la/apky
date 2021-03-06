//
// Copyright (C) 2015 Petr Talla. [petr.talla@gmail.com]
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

#include <TcCmdEngine.h>
#include <QString>

//=============================================================================
class  CmdsTab_dir {
//=============================================================================
public:
//<CMDS>
//=============================================================================
    //<REGISTRATOR>
    static bool registerCmds_()
    {   TcCmd* cmd;
        cmd = TcCmdEngine::engine().registerCmd("tab_set_dir", tab_set_dir_browser, "tab_set");
        cmd->frontControllExclude();

        TcCmdEngine::engine().registerCmd("cad_set_actual_dir", cad_set_actual_dir, "cad");

        return true;
    }


//<INTERNALS>
    CmdsTab_dir();

    static int tab_set_dir_browser(TcCmdContext* context, TcArgCol& args);
    static int cad_set_actual_dir(TcCmdContext* context, TcArgCol& args);

    static QString getT2ls_(const QString& dirStr);
    static QString getImages_(const QString& dirStr);
    static bool    alreadyUsed_(const QString& dirStr);
//<DATA>
private:
    static QString currentDirGet();
    static QString currentDir_;
};
