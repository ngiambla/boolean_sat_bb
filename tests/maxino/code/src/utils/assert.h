/*
 *  Copyright (C) 2014  Mario Alviano (mario@alviano.net)
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

#ifndef zuccherino_assert_h
#define zuccherino_assert_h

#include <cassert>
#include <iostream>

#define assert_action( condition, action ) \
    assert( ( condition ) || ( ( action ) && false ) )

#define assert_msg( condition, msg ) \
    assert_action( condition, std::cerr << "[assert_msg] " << msg << std::endl )

#endif