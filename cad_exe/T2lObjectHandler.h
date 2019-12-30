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

#include <QString>
#include <QList>

#include <string>
#include <list>

namespace T2l {

//=============================================================================
class ObjectHandler {
//=============================================================================
public:

//<CONSTRUCTION>
    ObjectHandler(const char* id);
    virtual ~ObjectHandler() {}

//<METHODS>
    virtual const char* id() { return id_.c_str(); }
    virtual QString toHtml() { return "void object"; }

    static void objAdd(ObjectHandler* object) { objects_.push_back(object); }
    static ObjectHandler* objGet(const char* id);

    static int objCount();
    static ObjectHandler* objAt(int index);
//=============================================================================
//<OVERRIDES>
protected:
//<DATA>
public:
    std::string id_;
    static QList<ObjectHandler*> objects_;
//<HIDDING>
//<INTERNALS>
//<FRIENDS>
    //friend int main(int argc, char *argv[]);
};

} // manespace T2l


