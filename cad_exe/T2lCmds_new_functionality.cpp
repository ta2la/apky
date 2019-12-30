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
#include "T2lCmds_new_functionality.h"
#include "T2lComponentLine.h"
#include "T2lComponentArea.h"
#include "T2lComponentText.h"
#include "T2lPapper.h"
#include "TcArgVal.h"
#include "TcArgCol.h"
#include "Protocol.h"
#include "T2lPainterUtility.h"
#include "T2lObjectHandler.h"
#include "T2lCmdQueue.h"

#include <string>
#include <sstream>

using namespace std;
using namespace T2l;

//=============================================================================
int Cmds_new_functionality::cmd_test_text_drawing( TcCmdContext* /*context*/, TcArgCol& args )
{
    Papper p(210.0, 150);
    QPainter& qp = p.painter();
    Color cg(120, 120, 120);

    PainterUtility::drawText( qp, "L_T", Point2F( 75,  75),  20, 20, cg, POSITION_H_RIGHT,  POSITION_V_TOP, true );
    PainterUtility::drawText( qp, "C_T", Point2F(150,  75),   0, 20, cg, POSITION_H_CENTER, POSITION_V_TOP, true );
    PainterUtility::drawText( qp, "R_T", Point2F(225,  75), -20, 20, cg, POSITION_H_LEFT,   POSITION_V_TOP, true );

    PainterUtility::drawText( qp, "L_C", Point2F( 75, 150),   0, 20, cg, POSITION_H_RIGHT,  POSITION_V_CENTER, true );
    PainterUtility::drawText( qp, "C_C", Point2F(150, 150),   0, 20, cg, POSITION_H_CENTER, POSITION_V_CENTER, true );
    PainterUtility::drawText( qp, "R_C", Point2F(225, 150),   0, 20, cg, POSITION_H_LEFT,   POSITION_V_CENTER, true );

    PainterUtility::drawText( qp, "L_B", Point2F( 75, 225), -20, 20, cg, POSITION_H_RIGHT,  POSITION_V_BOTTOM, true );
    PainterUtility::drawText( qp, "C_B", Point2F(150, 225),   0, 20, cg, POSITION_H_CENTER, POSITION_V_BOTTOM, true );
    PainterUtility::drawText( qp, "R_B", Point2F(225, 225),  20, 20, cg, POSITION_H_LEFT,   POSITION_V_BOTTOM, true );

    PainterUtility::drawText( qp, "red 10",     Point2F(100, 350), AngleXcc(0), 10, Color::RED,     POSITION_H_LEFT, POSITION_V_BOTTOM, true );
    PainterUtility::drawText( qp, "blue 20",    Point2F(100, 400), AngleXcc(0), 20, Color::BLUE,    POSITION_H_LEFT, POSITION_V_BOTTOM, true );
    PainterUtility::drawText( qp, "magenta 30", Point2F(100, 450), AngleXcc(0), 30, Color::MAGENTA, POSITION_H_LEFT, POSITION_V_BOTTOM, true );

#ifdef WINDOWS
    p.save("C:\\TEMP\\test.png");
    Protocol::protocolCmdGet().append("<img src='file://C:\\TEMP\\test.png'><br>");
#else
    p.save("/home/t2l/TEMP/test.png");
    Protocol::protocolCmdGet().append("<img src='file:///home/t2l/TEMP/test.png'><br>");
#endif

    return 0;
}

//=============================================================================
int Cmds_new_functionality::cmd_test_new_drawing( TcCmdContext* /*context*/, TcArgCol& args )
{
    Protocol::protocolCmdGet().append("HALLO PRINT IMAGE:<br>");

    Papper p(150.0, 120.0);

    ComponentLine line(Color::BLUE, 5, 30);
    line.points().points().add(Point2F(20,20));
    line.points().points().add(Point2F(60,20));
    line.points().points().add(Point2F(60,50));
    line.points().points().add(Point2F(20,50));
    line.points().points().add(Point2F(20,20));
    p.draw(line);

    ComponentLine line2(Color::RED, 0.18);
    line2.points().points().add(Point2F(0,0));
    line2.points().points().add(Point2F(50,50));
    p.draw(line2);

    ComponentArea area(Color::RED, 60);
    area.area().points().points().add(Point2F(50,50));
    area.area().points().points().add(Point2F(100,50));
    area.area().points().points().add(Point2F(50,100));
    p.draw(area);

    ComponentText ct( "test abcdefgh/Q{", Point2F(50, 75), 40, Color::BLUE,
                               POSITION_H_LEFT, POSITION_V_BOTTOM );

    p.draw( ComponentText( "test abcdefgh/Q{", Point2F(50, 75), 40, Color::BLUE,
                           POSITION_H_LEFT, POSITION_V_BOTTOM ) );
    p.draw( ComponentText( "iiisfWsji1", Point2F(150, 200), 30, Color::GRAY,
                           POSITION_H_CENTER, POSITION_V_CENTER, false, AngleXcc(20)) );
    p.draw( ComponentText( "PINkla", Point2F(150, 300), 20, Color::MAGENTA,
                           POSITION_H_RIGHT, POSITION_V_TOP, false, AngleXcc(45)) );

#ifdef WINDOWS
    p.save("C:\\TEMP\\test.png");
    Protocol::protocolCmdGet().append("<img src='file://C:\\TEMP\\test.png'><br>");
#else
    p.save("/home/t2l/TEMP/test.png");
    Protocol::protocolCmdGet().append("<img src='file:///home/t2l/TEMP/test.png'><br>");
#endif

    return 0;
}

//=============================================================================
int Cmds_new_functionality::cmd_display_objecst( TcCmdContext* /*context*/, TcArgCol& args )
{
    for ( int i = 0; i < ObjectHandler::objCount(); i++ ) {
        ObjectHandler* oh = ObjectHandler::objAt(i);
        Protocol::protocolCmdGet().append("<b>");
        Protocol::protocolCmdGet().append(oh->id());
        Protocol::protocolCmdGet().append(":</b><br>");
        Protocol::protocolCmdGet().append(oh->toHtml().toLatin1().data());
        Protocol::protocolCmdGet().append("<hr>");
    }

    return 0;
}

//=============================================================================
int Cmds_new_functionality::cmd_objects_expand(TcCmdContext* /*context*/, TcArgCol& args)
{
    /*CmdQueue::queue().add( new Cmd_objects_expand(Cmd_objects_expand::EXPAND), false);
    args.appendVal( "comparing value", "result");*/

    return 0;
}

//=============================================================================
int Cmds_new_functionality::cmd_objects_fence(TcCmdContext* /*context*/, TcArgCol& args)
{
    /*CmdQueue::queue().add( new Cmd_objects_expand(Cmd_objects_expand::FILL), false);
    args.appendVal( "comparing value", "result");*/

    return 0;
}

//=============================================================================

