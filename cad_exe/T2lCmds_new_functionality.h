//
// Copyright (C) 2017 Petr Talla. [petr.talla@gmail.com]
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

#include "TcCmdEngine.h"
#include "T2lTuple.h"
//#include "T2lNcount.h"
#include <string>

namespace T2l {

//=============================================================================
class Cmds_new_functionality {
//=============================================================================
//protected:
public:
//<CONSTRUCTION>
    Cmds_new_functionality() = delete;
//<METHODS>
//<CMDS>
    CMD_FCE ( cmd_test_new_drawing    );
    CMD_FCE ( cmd_test_text_drawing   );
    CMD_FCE ( cmd_display_objecst     );
    CMD_FCE ( cmd_objects_expand      );
    CMD_FCE ( cmd_objects_fence       );

//<REGISTRATOR>
    static bool registerCmds_()
    {
        REGISTER_CMD( "test_new_drawing",  cmd_test_new_drawing,  "test" );
        REGISTER_CMD( "test_text_drawing", cmd_test_text_drawing, "test" );
        REGISTER_CMD( "display_objecst",   cmd_display_objecst,   "test" );
        REGISTER_CMD( "objects_expand",    cmd_objects_expand,    "test" );
        REGISTER_CMD( "objects_fence",     cmd_objects_fence,     "test" );

        return true;
    }

//<INTERNALS>
};

} //namespace Hnw
