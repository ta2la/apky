//
// Copyright (C) 2014 Petr Talla. [petr.talla@gmail.com]
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

//=============================================================================
class Cmds_cad_exe {
//=============================================================================
public:
//<CMDS>
//=============================================================================
//<REGISTRATOR>
    static bool registerCmds_()
    {
        TcCmdEngine::engine().registerCmd("cmd_cad_file_open",        cmd_cad_file_open,        "cad");
        TcCmdEngine::engine().registerCmd("cmd_cad_save",             cmd_cad_save,             "cad");
        TcCmdEngine::engine().registerCmd("cmd_cad_file_load",        cmd_cad_file_load,        "cad");
        TcCmdEngine::engine().registerCmd("cmd_cad_active_file_move", cmd_cad_active_file_move, "cad");
        TcCmdEngine::engine().registerCmd("cmd_cad_list_files",       cmd_cad_list_files,       "cad");
        TcCmdEngine::engine().registerCmd("cmd_cad_file_activate",    cmd_cad_file_activate,    "cad");
        REGISTER_CMD("cmd_cad_draw_line", cmd_cad_draw_line, "cad");
        REGISTER_CMD("cmd_cad_draw_area", cmd_cad_draw_area, "cad");
        REGISTER_CMD("cmd_cad_draw_dimm", cmd_cad_draw_dimm, "cad");
        REGISTER_CMD("cmd_cad_draw_line3", cmd_cad_draw_line3, "cad");
        TcCmdEngine::engine().registerCmd("cmd_cad_draw_image",       cmd_cad_draw_image,       "cad");
        TcCmdEngine::engine().registerCmd("cmd_cad_draw_text",        cmd_cad_draw_text,        "cad");
        TcCmdEngine::engine().registerCmd("alias",                    alias,                    "cad");
        TcCmdEngine::engine().registerCmd("alias_print",              alias_print,              "cad");
        TcCmdEngine::engine().registerCmd("cmd_cad_view_fit",         cmd_cad_view_fit,         "cad");
        TcCmdEngine::engine().registerCmd("cmd_cad_file_close",       cmd_cad_file_close,       "cad");

        return true;
    }
private:
//<INTERNALS>
    Cmds_cad_exe();

    static int cmd_cad_file_open        ( TcCmdContext* context, TcArgCol& args );
    static int cmd_cad_save             ( TcCmdContext* context, TcArgCol& args );
    static int cmd_cad_file_load        ( TcCmdContext* context, TcArgCol& args );
    static int cmd_cad_active_file_move ( TcCmdContext* context, TcArgCol& args );
    static int cmd_cad_list_files       ( TcCmdContext* context, TcArgCol& args );
    static int cmd_cad_file_activate    ( TcCmdContext* context, TcArgCol& args );
    CMD_FCE(cmd_cad_draw_line);
    CMD_FCE(cmd_cad_draw_area);
    CMD_FCE(cmd_cad_draw_dimm);
    CMD_FCE(cmd_cad_draw_line3);
    static int cmd_cad_draw_image       ( TcCmdContext* context, TcArgCol& args );
    static int cmd_cad_draw_text        ( TcCmdContext* context, TcArgCol& args );
    static int cmd_cad_view_fit         ( TcCmdContext* context, TcArgCol& args );
    static int alias                    ( TcCmdContext* context, TcArgCol& args );
    static int alias_print              ( TcCmdContext* context, TcArgCol& args );
    static int cmd_cad_file_close       ( TcCmdContext* context, TcArgCol& args );
};
