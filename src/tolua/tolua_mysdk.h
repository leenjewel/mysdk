
#ifndef __TOLUA_MYSDK_H_
#define __TOLUA_MYSDK_H_

#include "tolua++.h"
    
#define TOLUA_REFID_FUNCTION_MAPPING "toluamysdk_refid_function_mapping"

/**
 * @addtogroup lua
 * @{
 */
/// @cond
TOLUA_API void toluamysdk_open(lua_State* L);
/// @endcond

/**
 * Get the refrence id of the Lua function at the given accepteable index lo of stack.
 * Meanwhile add refrence about the Lua function through the toluamysdk_refid_function_mapping table in the Lua registry.
 *
 * @param L the current lua_State.
 * @param lo the given accepteable index lo of stack.
 * @param def useless.
 * @return 0 if the type of value at the given accepteable index lo of stack is not LUA_TFUNCTION; otherwise return the refrence id.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluamysdk_ref_function(lua_State* L, int lo, int def);

/**
 * Push the Lua function found by the refid in the toluamysdk_refid_function_mapping table in the Lua registry on the top index of the current stack.
 *
 * @param L the current lua_State.
 * @param refid referenc id corresponding to the Lua function.
 * @lua NA
 * @js NA
 */
TOLUA_API void toluamysdk_get_function_by_refid(lua_State* L, int refid);

/**
 * Remove the reference of the Lua function corresponding to the refid in the toluamysdk_refid_function_mapping table in the Lua registry.
 *
 * @param L the current lua_State.
 * @param refid referenc id corresponding to the Lua function.
 * @lua NA
 * @js NA
 */
TOLUA_API void toluamysdk_remove_function_by_refid(lua_State* L, int refid);

/**
 * Verify the value at the given acceptable index is a function or not.
 * 
 * @param L the current lua_State.
 * @param lo the given accepteable index lo of stack.
 * @param type useless.
 * @param def useless.
 * @param err if triggger the error, record the error message to err.
 * @return 1 if the value at the given acceptable index is a function, otherwise return 0.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluamysdk_isfunction(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

/// @cond
TOLUA_API int toluamysdk_totable(lua_State* L, int lo, int def);
/// @endcond

/**
 * Verify the value at the given acceptable index is a table or not.
 * 
 * @param L the current lua_State.
 * @param lo the given accepteable index lo of stack.
 * @param type useless.
 * @param def whether has the default value.
 * @param err if triggger the error, record the error message to err.
 * @return 1 if the value at the given acceptable index is a table or have def value is not 0, otherwise return 0.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluamysdk_istable(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

/**
 * Print all information of the stack from the top index.
 * If the type corresponding to the index of the stack is LUA_TSTRING, LUA_TBOOLEAN or LUA_TNUMBER, it would output the value of the index,otherwise output the type name of the index.
 *
 * @param L the current lua_State.
 * @param label the string pointer to define the label of the dump information.
 * @lua NA
 * @js NA
 */
TOLUA_API void toluamysdk_stack_dump(lua_State* L, const char* label);

// end group
/// @}

#endif // __TOLUA_MYSDK_H_
