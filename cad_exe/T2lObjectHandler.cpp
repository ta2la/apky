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

#include "T2lObjectHandler.h"
#include "T2lHandlerMatrix.h"
//#include "T2lNaray2f.h"
#include <string>

using namespace T2l;
using namespace std;

//====================================================================
QList<ObjectHandler*> ObjectHandler::objects_;

//====================================================================
ObjectHandler::ObjectHandler(const char* id) :
    id_(id)
{
}

//====================================================================
ObjectHandler* ObjectHandler::objAt(int index)
{
    return objects_.at(index);
}

//====================================================================
ObjectHandler* ObjectHandler::objGet(const char* id)
{
    string idStr(id);

    for (auto item : objects_) {
        if ( idStr != item->id() ) continue;
        return item;
    }

    return NULL;
}

//====================================================================
int ObjectHandler::objCount()
{
    /*static bool initialized = false;

    if (initialized == false) {
        HandlerMatrix* m = new HandlerMatrix("a", 5, 4);
        for ( int x = 0; x < 5; x++ ) {
            for ( int y = 0; y < 4; y++ ) {
                m->naray().set(x*y, x, y);
            }
        }

        objAdd(m);

        initialized = true;
    }*/

    return objects_.size();
}

//====================================================================
