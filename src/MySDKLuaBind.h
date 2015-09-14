/**
 * Copyright 2015 leenjewel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __MYSDK_LUA_BIND_H__
#define __MYSDK_LUA_BIND_H__

typedef struct lua_State lua_State;
typedef int LUA_FUNCTION;

int register_mysdk_to_lua(lua_State* L);

#endif
