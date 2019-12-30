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

// self
#include "T2lCmdsTab_about.h"

// infrastructure
#include "TcHtmlViewTabbed.h"
#include "TcArgCol.h"
#include "TcArgVal.h"

using namespace std;
using namespace T2l;

//=============================================================================
int CmdsTab_about::tab_set_about(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    result.append(
        "<div class='dir_part1'>"
        );
    result.append("<p><big><b>Cad2l 0.1.0</big></b></p>");
    result.append("<p>Copyright 2015-2019 Petr Talla. All right reserved.</p>");
    result.append("<p>The program is provided AS IS with NO WARRANY OF ANY KIND, "
                  "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY "
                  "AND FITNESS FOR A PARTICULAR PURPOSE.");

    TcHtmlViewTabbed::mainView().tabSet("about", result.toLatin1().data());

    return 0;
}

//=============================================================================
