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
//self
#include "T2lCmds_cad_exe.h"

#include "T2lGFileCol.h"
#include "T2lGFile.h"
#include "T2lGFileObjects.h"
#include "T2lGFileImage.h"
#include "T2lGFileImgDescr.h"
#include "T2lCmd_active_file_move.h"
#include "T2lCmdQueue.h"
#include "T2lDisplayCol.h"
#include "T2lActiveFile.h"
#include "T2lFilterFile.h"
#include "T2lCmd_draw_dimm.h"
#include "T2lActiveFile.h"
#include "T2lWidgetInteractCol.h"

//geogebra
#include "T2lGFile.h"
#include "T2lCmd_draw_line.h"
#include "T2lCmd_draw_line3.h"
#include "T2lCmd_draw_dimm.h"
#include "T2lCmd_draw_area.h"
#include "T2lCmd_draw_image.h"
#include "T2lCmd_draw_text.h"
#include "T2lCmd_draw_imgLink.h"
#include "T2lCmd_view_fit.h"
#include "T2lCmd_measure.h"
#include "T2lCmd_draw_area.h"

#include "TcArg.h"
#include "TcArgVal.h"
#include "TcArgCol.h"

#include "T2lFilter.h"
#include "T2lScene.h"
#include "T2lGObjectPool.h"

//hg
#include "T2lCmdQueue.h"

//qt
#include <QFileInfo>
#include <QString>

//std
#include <sstream>

using namespace std;
using namespace T2l;

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_line(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_line(), false );

    string result ( "<br><a href='tcview:://#cad_set_ortho'>[ortho]</a>" );
    args.appendVal(result.c_str(), "result");

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_line3(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_line3(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_area(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_area(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_dimm(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_dimm(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_view_fit(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    CmdQueue::queue().add( new Cmd_view_fit(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_image(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    CmdQueue::queue().add( new Cmd_draw_image(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_text(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_text(), false );

    string result ( "<br>text: "
                    " <a href='tcview:://#text ahoj'> [ahoj]</a>"
                    " <a href='tcview:://#text sbohem'> [sbohem]</a>"
                  );

    args.appendVal(result.c_str(), "result");

    return 1;
}

//=============================================================================
int Cmds_cad_exe::alias(TcCmdContext* /*context*/, TcArgCol& args)
{
    /*TODOM if ( args.count() < 2 ) return args.appendError("you must enter alias name");
    TcArg* arg1 = args.getAsCol()->at(1);

    CmdQueue::queue().add( new Cmd_alias(arg1->getAsVal()->value()), false );*/
    return 0;
}

//=============================================================================
int Cmds_cad_exe::alias_print(TcCmdContext* /*context*/, TcArgCol& args)
{
    /*TODOS stringstream ss;

    if ( args.count() < 2 ) {
        for (int i = 0; i < CmdAliasCol::instance().count(); i++ ) {
            if (i != 0) ss << endl;
            string id = CmdAliasCol::instance().get(i)->id();
            ss << "<a href='tcview:://#alias_print " << id << "'>";
            ss << id;
            ss << "</a> ";
        }
    }
    else {
        TcArg* arg1 = args.getAsCol()->at(1);
        string alias = arg1->getAsVal()->value();

        ss << alias << ":" << "<br>";

        CmdAlias* cmdAlias = CmdAliasCol::instance().get(alias.c_str());
        if (cmdAlias == NULL) {
            ss << "NOT FOUND";
        }
        else {
            QString content = cmdAlias->content();
            QStringList list = content.split("\n");
            for (int i = 0; i < list.size(); i++) {
                ss << list.at(i).toStdString().c_str() << "<br>";
            }
        }
    }

    args.appendVal(ss.str().c_str(), "result");*/
    return 1;
}


//=============================================================================
int Cmds_cad_exe::cmd_cad_active_file_move(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    CmdQueue::queue().add( new Cmd_active_file_move(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_file_load(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 2 ) return args.appendError("you must enter the text");
    TcArg* arg1 = args.getAsCol()->at(1);

    TcArg* arg2 = args.getAsCol()->at(2);
    QString fullFileName = arg2->getAsVal()->value();

    GFile* file = GFileCol::instance().getByFileName(fullFileName);
    if (file == NULL) return args.appendError("wrong file name");

    if ( string("load") == arg1->getAsVal()->value() ) {
        if (file->loaded()) return args.appendError("file is already loaded");
        file->load();
    }
    else {
        if (file->loaded() == false) return args.appendError("file is already unloaded");
        file->unload();
    }

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_file_activate(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 1 ) return args.appendError("you must enter file name");

    TcArg* arg = args.getAsCol()->at(1);
    QString fullFileName = arg->getAsVal()->value();

    GFile* file = GFileCol::instance().getByFileName(fullFileName);
    if (file == NULL) return args.appendError("wrong file name");

    ActiveFile::changeActiveFile(file, false, false);

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_file_close(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 1 ) return args.appendError("you must enter file name");

    TcArg* arg = args.getAsCol()->at(1);
    QString fullFileName = arg->getAsVal()->value();

    GFile* file = GFileCol::instance().getByFileName(fullFileName);
    if (file == nullptr) return args.appendError("wrong file name");

    WidgetInteractCol& widgets = WidgetInteractCol::instance();
    for (int i = 0; i < widgets.count(); i++) {
        delete widgets.get(i);
    }
    widgets.clean();

    file->close();

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_save(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    for (int i = 0; i < GFileCol::instance().count(); i++) {
        GFile* file = GFileCol::instance().get(i);
        if (file->loaded() == false) continue;
        file->save();
    }

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_file_open(TcCmdContext* context, TcArgCol& args)
{
    if (args.count() < 2) return args.appendError("dir name must be entered");
    TcArgVal* val = args.at(1)->getAsVal();
    if (val == NULL) return args.appendError("dir name must be entered");

    QFileInfo fileInfo(val->value());
    if ( fileInfo.exists() == false ) {
        return args.appendError("file does not exist");
    }

    GFile* file = NULL;

    QString suffix = fileInfo.suffix();

    bool show = false;

    if ( suffix == "t2l") {
        file = new GFileObjects(val->value());
    }
    else if ( ( suffix == "png" ) ||
              ( suffix == "jpg" ) ||
              ( suffix == "jpeg" ) ) {
        file = new GFileImage(val->value());
    }
    else if ( suffix == "t2limgd") {
        file = new GFileImgDescr(val->value());
    }


    if (file == NULL) {
        return args.appendError("file is not of type t2l or png");
    }

    GFileCol::instance().add(file);

    if (args.count() >= 3 ) {

        TcArgVal* val2 = args.at(2)->getAsVal();

        bool fifile = true;

        if (args.count() >= 3 ) {
            fifile = false;
        }

        if ( val2->getString() == "show" ) {
            WidgetInteractCol& widgets = WidgetInteractCol::instance();
            /*for (int i = 0; i < widgets.count(); i++) {
                delete widgets.get(i);
            }
            widgets.clean();*/

            ActiveFile::changeActiveFile(file, false, true);

            WidgetInteract* view = new WidgetInteract( Point2F(0, 0), 1.0/1000.0 );
            widgets.add(view);

            Filter* filter = nullptr;
            if (fifile) {
                filter = new FilterFile(file);
            }
            else {
                filter = new Filter();
            }

            Scene* scene = new Scene(filter);
            GObjectPool::instance().addRefCol(scene);

            view->colorBackgroundSet(Color::WHITE);
            scene->entities().addDisplay(view);

            Box2F newDisplay;
            newDisplay.inflateBy(file->bound());
            newDisplay.inflateBy( (newDisplay.x().getLength() + newDisplay.y().getLength()) / 10.0);
            if ( newDisplay.isEmpty() == false ) {
                Point2F originNew (
                    ( view->scale(Scale2::X) > 0 ) ? newDisplay.x().beg() : newDisplay.x().end(),
                    ( view->scale(Scale2::Y) > 0 ) ? newDisplay.y().beg() : newDisplay.y().end() );

                view->originSet(originNew);

                double scaleX = view->getRefCanvas().scaleX()*view->size().w()/newDisplay.x().getLength();
                double scaleY = view->getRefCanvas().scaleY()*view->size().h()/newDisplay.y().getLength();

                double scale = scaleX;
                if (scaleY > scale) scale = scaleY;

                view->scaleSet( scale, Scale2::XY );
            }

            view->resize(600, 400);

            view->refresh();
            view->show();

            show = true;
        }
    }

    if (show == false) {
        ActiveFile::changeActiveFile(file, false, true);
    }

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_list_files(TcCmdContext* /*context*/, TcArgCol& args)
{
    stringstream ss;

    ss << "<br>";

    GFileCol& files = GFileCol::instance();
    for (int f = 0; f < files.count(); f++) {
        GFile* file = files.get(f);

        ss << "</br>";
        ss << "#### " << file->fileName().toStdString();

        if (file->loaded()) {
            ss << " [loaded]";
        }
        else {
            ss << " [not loaded]";
        }

        if (file == ActiveFile::active().file()) {
            ss << " [active]";
        }

        for (int i = 0; i < file->objects().count(); i++) {
            ss << "<br>" << file->objects().get(i)->print();
        }
    }

    args.appendVal(ss.str().c_str(), "result");

    return 1;
}

//=============================================================================
