#ifndef __MYSDK_LUA_BIND_H__
#define __MYSDK_LUA_BIND_H__

extern "C"
{
#include "lua.h"
}

int register_mysdk_to_lua(lua_State* L);

#endif
