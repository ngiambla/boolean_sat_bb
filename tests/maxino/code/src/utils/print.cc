/*
 *  Copyright (C) 2017  Mario Alviano (mario@alviano.net)
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include "print.h"

namespace zuccherino {

std::ostream& operator<<(std::ostream& o, Glucose::lbool l) {
    if(l == l_True) return o << "T";
    if(l == l_False) return o << "F";
    if(l == l_Undef) return o << "U";
    assert(0);
    return o;
}
    
std::ostream& operator<<(std::ostream& o, const Glucose::Lit& l) {
    return o << (sign(l) ? "-" : "") << (var(l)+1);
}

std::ostream& operator<<(std::ostream& o, const Glucose::Clause& c) {
    o << "[ ";
    for(int i = 0; i < c.size(); i++)
        o << c[i] << " ";
    return o << "]";
}

}
