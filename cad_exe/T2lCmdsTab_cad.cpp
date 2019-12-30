//
// Copyright (C) 2013 Kinalisoft. [kinalisoft.eu]
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
// author: petr.talla@kinalisoft.eu
//   date: 2012-06-17
//purpose:
//=============================================================================
//self
#include "T2lCmdsTab_cad.h"
#include "T2lHtmlTabsRegistry.h"

//cad
#include "T2lActiveFile.h"
#include "T2lCadExeSettings.h"
#include "T2lStoredFileNames.h"

// infrastructure
#include <TcHtmlViewTabbed.h>
#include "TcHtmlDir.h"
#include <TcArgCol.h>
#include <TcArgVal.h>
#include <TcCmdLog.h>
#include <TcCmds_htmlView.h>

// hg
#include "T2lGFile.h"
#include "T2lGFileCol.h"
#include "T2lWidgetInteract.h"
#include "T2lFilter.h"
#include "T2lCmdQueue.h"
#include "T2lCmd.h"

// qt
#include <QString>

using namespace T2l;

//=============================================================================
CmdsTab_cad::CmdsTab_cad()
{
}

//=============================================================================
QString CmdsTab_cad::symbolTag(const QString& symbol)
{
    QString result;
    result += "<img width='30' height='30' src='file://";
    result += StoredFileNames::getExeUpDir() + "/resource/";

    result += symbol;
    result += ".png";
    result += "'/>";

    return result;
}

//=============================================================================
int CmdsTab_cad::tab_set_ofiles(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    result.append("<div class='toolbar'>");
    result.append("opened files:<br> ");
    for ( int i = 0; i < GFileCol::instance().count(); i++ ) {
        GFile* file = GFileCol::instance().get(i);
        bool active = false;

        if (file == ActiveFile::active().file()) active = true;

        if (file->loaded()) {
            result.append("<a href='tcview:://#cmd_cad_file_load unload ");
            result.append(file->filePath());
            result.append("'>[loaded]</a>");
        }
        else {
            result.append("<a href='tcview:://#cmd_cad_file_load load ");
            result.append(file->filePath());
            result.append("'>[unloaded]</a>");
        }

        if (active == false) {
            result.append("<a href='tcview:://#cmd_cad_file_activate ");
            result.append(file->filePath());
            result.append("'>[a]</a>");
        }

        if (active==false || GFileCol::instance().count()==1) {
            result.append("<a href='tcview:://#cmd_cad_file_close ");
            result.append(file->filePath());
            result.append("'>[close]</a>");
        }

        if (active) result.append(" <b>");
        result.append(file->fileName());
        if (active) result.append("</b>");
        result.append("<br>");
    }
    result.append("</div>");

    TcHtmlViewTabbed::mainView().tabSet("ofiles", result.toLatin1().data());
    return 0;
}

//=============================================================================
int CmdsTab_cad::tab_set_executed(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    /*result.append("<div class='toolbar'>");
    result.append("opened files:<br> ");
    for ( int i = 0; i < GFileCol::instance().count(); i++ ) {
        GFile* file = GFileCol::instance().get(i);
        bool active = false;

        if (file == ActiveFile::active().file()) active = true;

        if (file->loaded()) {
            result.append("<a href='tcview:://#cmd_cad_file_load unload ");
            result.append(file->filePath());
            result.append("'>[loaded]</a>");
        }
        else {
            result.append("<a href='tcview:://#cmd_cad_file_load load ");
            result.append(file->filePath());
            result.append("'>[unloaded]</a>");
        }

        if (active == false) {
            result.append("<a href='tcview:://#cmd_cad_file_activate ");
            result.append(file->filePath());
            result.append("'>[a]</a>");
        }

        if (active) result.append(" <b>");
        result.append(file->fileName());
        if (active) result.append("</b>");
        result.append("<br>");
    }
    result.append("</div>");*/


    result.append("<div class='toolbar'>");
    result.append(TcCmds_htmlView::displayCmdLine(!Queue::instance()->consumeText()));
    result.append("</div>");

    TcHtmlViewTabbed::mainView().tabSet("exed", result.toLatin1().data());
    return 0;
}


//=============================================================================
QString button(const QString& symbol, const QString& cmd = "")
{
    QString acmd = cmd;
    if (acmd.isEmpty()) acmd = symbol;

    QString result = "TC;CB;cmd: ";
    result += acmd + ";icon: ";
    result += StoredFileNames::getExeUpDir() + "/resource/";
    result += symbol;
    result += ".png;;";

    return result;
}

//=============================================================================
int CmdsTab_cad::tab_set_acmd(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;
    result += "TC;CT;text: <b>";
    result.append(CmdQueue::queue().activeCommand()->name());
    result.append("</b>: ");
    result.append(CmdQueue::queue().activeCommand()->hint());
    result += ";;";

    //===================================================
    result = result.replace("TC", "type: control");
    result = result.replace("CT", "control: text");
    result = result.replace("CB", "control: button");
    result = result.replace(";", "\n");

    TcHtmlViewTab* tab = HtmlTabsRegistry::instance().tabGet_("acmd");
    tab->contentSet(result.toStdString().c_str());

    return 0;
}

//=============================================================================
int CmdsTab_cad::tab_set_icmd(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result = CmdQueue::queue().activeCommand()->dialogTml();

    TcHtmlViewTab* tab = HtmlTabsRegistry::instance().tabGet_("icmd");
    tab->contentSet(result.toStdString().c_str());

    return 0;
}

//=============================================================================
int CmdsTab_cad::tab_set_toolbar(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    static int i = 0;

    result += "TC;CT;text: create:;;";
    result += button("create_line",   "cmd_cad_draw_line" );
    result += button("create_area",   "cmd_cad_draw_area" );
    result += button("create_symbol", "cmd_object_enter");
    result += button("create_image",  "cmd_cad_draw_image");
    result += button("create_text",   "cmd_cad_draw_text");
    result += button("create_dimm",   "cmd_cad_draw_dimm");
    result += button("create_line3",  "cmd_cad_draw_line3" );

    result += "TC;CT;text: <space>;;";
    result += "TC;CT;text: select:;;";
    result += button( "edit_select",      "cmd_object_select" );

    result += "TC;CT;text: <space>;;";
    result += "TC;CT;text: copy:;;";
    result += button("copy",              "cmd_object_copy");
    result += button("copy_parallel",     "cmd_object_mocopy_parallel");

    result += "TC;CT;text: <space>;;";
    result += "TC;CT;text: edit:;;";
    result += button( "edit_move",        "cmd_object_move"          );
    result += button( "edit_move_points", "cmd_object_movepoints"    );
    result += button( "edit_trim",        "cmd_object_trim"          );
    result += button( "edit_trimto",      "cmd_object_trimtoother"   );
    result += button( "edit_symbology",   "cmd_object_set_symbology" );
    result += button( "change_text",      "change_text" );
    result += button( "delete",           "cmd_object_delete"        );

    result += "TC;CT;text: <space>;;";
    result += "TC;CT;text: info:;;";
    result += button("info_measure", "cmd_cad_measure");

    result += "TC;CT;text: <hup>;;";
    result += "TC;CT;text: file:;;";
    result += button("cmd_cad_save", "cmd_cad_save");

    result += "TC;CT;text: view:;;";
    result += button("view_new");
    result += button("view_pan",        "cmd_view_pan");
    result += button("view_zoomrect",   "cmd_view_zoomrect");
    result += button("view_fit", "cmd_cad_view_fit");

    bool all = false;
    if (all) {
        result +=
        "TC;CT;text: <hup>;;"
        "TC;CT;text: test: <a href='tcview:://#test_new_drawing'>[new drawing]</a>;;"
        "TC;CT;text: <a href='tcview:://#test_text_drawing'>[text drawing]</a>;;"
        "TC;CT;text: <a href='tcview:://#display_objecst'>[display objects]</a>;;"
        "TC;CT;text: <a href='tcview:://#objects_expand'>[expand]</a>;;"
        "TC;CT;text: <a href='tcview:://#objects_fence'>[fence]</a>;;"
        "TC;CT;text: <a href='tcview:://#view_new red'>[view red]</a>;;"
        "TC;CT;text: <a href='tcview:://#view_new green'>[green]</a>;;"
        "TC;CT;text: <a href='tcview:://#view_new blue'>[blue]</a>;;"

        "TC;CT;text: photomap: <a href='tcview:://#viewinfo'>[viewinfo]</a>;;"
        "TC;CT;text: <a href='tcview:://#cmd_real_measure_enter'>[real MEASURE]</a>;;"
        "TC;CT;text: <a href='tcview:://#cmd_ref_file_enter'>[enter file ref]</a>;;"
        "TC;CT;text: <a href='tcview:://#cmd_ref_file_navigate e'> [navigate ref]</a>;;"
        "TC;CT;text: <a href='tcview:://#cmd_over_file_manipulate'> [over file EXPAND]</a>;;"
        "TC;CT;text: <a href='tcview:://#cmd_refed_file_navigate'> [REFED list]</a>;;";
    }

    result +=
    "TC;CT;text: <hup>;;"
    "TC;CT;text: command:;;"
    "TC;control: edit;"
    ";;";

    //===================================================
    result = result.replace("TC", "type: control");
    result = result.replace("CT", "control: text");
    result = result.replace("CB", "control: button");
    result = result.replace(";", "\n");

    TcHtmlViewTab* tab = HtmlTabsRegistry::instance().tabGet_("toolbar");
    tab->contentSet(result.toStdString().c_str());

    return 0;
}

//=============================================================================
