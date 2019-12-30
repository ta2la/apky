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
#include "T2lCmdsTab_dir.h"
#include "T2lFilesystem.h"
//#include "T2lCmd_refed_file_list.h"

// infrastructure
#include "TcHtmlDir.h"
#include "TcHtmlViewTabbed.h"
#include "TcArgCol.h"
#include "TcArgVal.h"
#include "T2lGFileCol.h"

// qt
#include <QDir>
#include <QDirIterator>

// opencv
//#include <opencv2/opencv.hpp>

using namespace std;
using namespace T2l;

//=============================================================================
QString CmdsTab_dir::currentDir_ = "C:/HOME/KADLUB/cvz/samples/cad/TEST";

bool CmdsTab_dir::alreadyUsed_(const QString& filePath)
{
    QFileInfo fi(filePath);
    QDir dir = fi.dir();

    GFileCol& files = GFileCol::instance();
    for ( int i = 0; i < files.count(); i++ ) {
        QFileInfo fii = files.get(i)->filePath();
        if ( fii.dir() != dir) continue;
        if ( fii.baseName() != fi.baseName() ) continue;
        return true;
    }

    return false;
}

//=============================================================================
QString CmdsTab_dir::getT2ls_(const QString& dirStr)
{
    QString wrapper( "<a href='tcview:://#cmd_cad_file_open $FILELINK show'>$FILENAME</a>&nbsp;&nbsp; " );

    QDir dir(dirStr);
    if ( dir.exists() == false ) return "No files found";

    QStringList nameFilter;
    nameFilter << "*.t2l";
    QStringList list = dir.entryList(nameFilter, QDir::Files);

    QString result;

    for (int i = 0; i < list.size(); i++) {
        QFileInfo file(dirStr, list.at(i));

        /*bool skip = false;
        GFileCol& files = GFileCol::instance();
        for ( int i = 0; i < files.count(); i++ ) {
            if ( QFileInfo(files.get(i)->filePath()) != file ) continue;
            skip = true;
            break;
        }

        if (skip) continue;*/

        if ( alreadyUsed_(file.absoluteFilePath()) ) continue;

        QString resulti = wrapper;
        resulti.replace("$FILELINK", file.absoluteFilePath());
        QString fileName = file.fileName();
        resulti.replace("$FILENAME", fileName);
        result += resulti;
    }

    return result;
}

//=============================================================================
QString CmdsTab_dir::getImages_(const QString& dirStr)
{
    QString wrapper( "<a href='tcview:://#cmd_cad_file_open $FILENAME show'>"
                     "<img width='50' height='45' src='file://$FILENAME'/>"
                     "</a>&nbsp;&nbsp; " );

    QDir dir(dirStr);
    if ( dir.exists() == false ) return "No files found";

    QStringList nameFilter;
    nameFilter << "*.jpg" << "*.jpeg" << "*.png" << ".bmp";
    QStringList list = dir.entryList(nameFilter, QDir::Files);

    QString result;

    for (int i = 0; i < list.size(); i++) {
        QFileInfo file(dirStr, list.at(i));

        if ( alreadyUsed_(file.absoluteFilePath()) ) continue;

        bool selected =  Filesystem::instance().isSelected(file.absoluteFilePath());

        QString resulti = wrapper;
        resulti.replace("$FILENAME", file.absoluteFilePath());

        if ( selected ) result += "<font size='230'>[</font>";
        result += resulti;
        if ( selected ) result += "<font size='230'>]</font>";
    }

    return result;
}

//=============================================================================
int CmdsTab_dir::tab_set_dir_browser(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    //QDir dir(Cmd_refed_file_list::currentDir());
    QDir dir(currentDir_);

    result.append("<div class='dir_part1'>");
    result.append("<p>Current directory: <b>");
    result.append(currentDir_.toStdString().c_str());
    result.append("</b></p>");

    /*result.append("<p>Favourites: ");
    result.append("<a href='tcview:://#cad_set_actual_dir /home/petrtalla/Development/P4/pia/test/regression/test_cornertestengine/image'>");
    result.append("regression/test_cornertestengine</a>&nbsp;&nbsp;");
    result.append("<a href='tcview:://#cad_set_actual_dir /home/petrtalla/Development/P4/imagecol_corners'>");
    result.append("imagecol_corners</a><br>");
    result.append("</p>");*/

    result.append("<p>Subdirectories: ");
    QDirIterator dirIt(dir.absolutePath(), QDir::AllDirs | QDir::Dirs);
    while( dirIt.hasNext() ) {
        dirIt.next();

        if ( dirIt.fileInfo().fileName() == "." ) continue;

        result.append("<a href='tcview:://#cad_set_actual_dir ");
        result.append(dirIt.fileInfo().canonicalFilePath());
        result.append("'>");
        result.append(dirIt.fileInfo().fileName());
        result.append("</a>");
        result.append("&nbsp; &nbsp;");
    }
    result.append("</p></div>");

    result.append("<div>");
    result.append(getT2ls_(currentDir_));
    result.append("<br></div><div>");
    result.append(getImages_(currentDir_));
    result.append("</div>");

    TcHtmlViewTabbed::mainView().tabSet("dir", result.toLatin1().data());

    return 0;
}

//=============================================================================
int CmdsTab_dir::cad_set_actual_dir(TcCmdContext* /*context*/, TcArgCol& args)
{
    if (args.count() < 2) return args.appendError("dir name must be entered");
    TcArgVal* val = args.at(1)->getAsVal();
    if (val == NULL) return args.appendError("dirname name must be entered");
    //Cmd_refed_file_list::currentDirSet(val->value());
    currentDir_ = QString(val->value());
    //Cmd_refed_file_list::currentDirSet(val->value());

    return 0;
}

//=============================================================================
