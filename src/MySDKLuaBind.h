#ifndef __MYSDK_LUA_BIND_H__
#define __MYSDK_LUA_BIND_H__

typedef struct lua_State lua_State;
typedef int LUA_FUNCTION;

int register_mysdk_to_lua(lua_State* L);

#endif
