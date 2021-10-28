//
// Copyright 2018 Sepehr Taghdisian (septag@github). All rights reserved.
// License: https://github.com/septag/sx#license-bsd-2-clause
//
// parts of this code is copied from bx library: https://github.com/bkaradzic/bx
// Copyright 2011-2019 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bx#license-bsd-2-clause
//
// macros.h - v1.0 - Common portable helper macros
// Many of these are stolen from: https://github.com/bkaradzic/bx/blob/master/include/bx/macros.h
//      General rule is that function like macros are in camel_case
//      and simple preprocessor/code annotations are in UPPER_CASE
#pragma once

#include "config.h"
#include "platform.h"

///
#define sx_makefourcc(_a, _b, _c, _d) \
    (((uint32_t)(_a) | ((uint32_t)(_b) << 8) | ((uint32_t)(_c) << 16) | ((uint32_t)(_d) << 24)))

///
#define _sx_stringize(_x) #_x
#define sx_stringize(_x) _sx_stringize(_x)
#define _sx_concat(_a, _b) _a##_b
#define sx_concat(_a, _b) _sx_concat(_a, _b)

///
// Function decleration code helpers

// Default parameter value, only for C++ and kind of a self documenting for C
#ifdef __cplusplus
#    define sx_default(_e) = (_e)
#else
#    define sx_default(_e)
#endif

///
#define sx_align_mask(_value, _mask) (((_value) + (_mask)) & ((~0) & (~(_mask))))
#define sx_align_16(_value) sx_align_mask(_value, 0xf)
#define sx_align_256(_value) sx_align_mask(_value, 0xff)
#define sx_align_4096(_value) sx_align_mask(_value, 0xfff)

#if defined(__has_feature)
#    define sx_clang_has_feature(_x) __has_feature(_x)
#else
#    define sx_clang_has_feature(_x) 0
#endif    // defined(__has_feature)

#if defined(__has_extension)
#    define sx_clang_has_extension(_x) __has_extension(_x)
#else
#    define sx_clang_has_extension(_x) 0
#endif    // defined(__has_extension)

#if SX_COMPILER_GCC || SX_COMPILER_CLANG
#    define SX_ALLOW_UNUSED __attribute__((unused))
#    define SX_FORCE_INLINE SX_INLINE __attribute__((__always_inline__))
#    define SX_FUNCTION __PRETTY_FUNCTION__
#    define SX_NO_INLINE __attribute__((noinline))
#    define SX_NO_RETURN __attribute__((noreturn))
#    define SX_CONSTFN __attribute__((const))
#    define SX_RESTRICT __restrict__
// https://awesomekling.github.io/Smarter-C++-inlining-with-attribute-flatten/
#    define SX_FLATTEN __attribute__((flatten))     // inline everything in the function body
#    if SX_CRT_MSVC
#        define __stdcall
#    endif    // SX_CRT_MSVC
#    if SX_CONFIG_FORCE_INLINE_DEBUG
#       define SX_INLINE static 
#    else
#       define SX_INLINE static inline  
#    define SX_NO_VTABLE 
#    endif
#elif SX_COMPILER_MSVC
#    define SX_ALLOW_UNUSED
#    define SX_FORCE_INLINE __forceinline
#    define SX_FUNCTION __FUNCTION__
#    define SX_NO_INLINE __declspec(noinline)
#    define SX_NO_RETURN
#    define SX_CONSTFN __declspec(noalias)
#    define SX_RESTRICT __restrict
#    define SX_FLATTEN 
#    if SX_CONFIG_FORCE_INLINE_DEBUG
#       define SX_INLINE static 
#    else
#       define SX_INLINE static inline  
#    endif
#    define SX_NO_VTABLE __declspec(novtable)
#    ifndef __cplusplus
#       define _Thread_local __declspec(thread)
#    endif // __cplusplus
#else
#    error "Unknown SX_COMPILER_?"
#endif

#if SX_COMPILER_GCC || SX_COMPILER_CLANG
#    define sx_align_decl(_align, _decl) _decl __attribute__((aligned(_align)))
#else
#    define sx_align_decl(_align, _decl) __declspec(align(_align)) _decl
#endif

#if SX_COMPILER_CLANG
#    define SX_PRAGMA_DIAGNOSTIC_PUSH_CLANG_() _Pragma("clang diagnostic push")
#    define SX_PRAGMA_DIAGNOSTIC_POP_CLANG_() _Pragma("clang diagnostic pop")
#    define SX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG(_x) _Pragma(sx_stringize(clang diagnostic ignored _x))
#else
#    define SX_PRAGMA_DIAGNOSTIC_PUSH_CLANG_()
#    define SX_PRAGMA_DIAGNOSTIC_POP_CLANG_()
#    define SX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG(_x)
#endif    // SX_COMPILER_CLANG

#if SX_COMPILER_GCC && SX_COMPILER_GCC >= 40600
#    define SX_PRAGMA_DIAGNOSTIC_PUSH_GCC_() _Pragma("GCC diagnostic push")
#    define SX_PRAGMA_DIAGNOSTIC_POP_GCC_() _Pragma("GCC diagnostic pop")
#    define SX_PRAGMA_DIAGNOSTIC_IGNORED_GCC(_x) _Pragma(sx_stringize(GCC diagnostic ignored _x))
#else
#    define SX_PRAGMA_DIAGNOSTIC_PUSH_GCC_()
#    define SX_PRAGMA_DIAGNOSTIC_POP_GCC_()
#    define SX_PRAGMA_DIAGNOSTIC_IGNORED_GCC(_x)
#endif    // SX_COMPILER_GCC

#if SX_COMPILER_MSVC
#    define SX_PRAGMA_DIAGNOSTIC_PUSH_MSVC_() __pragma(warning(push))
#    define SX_PRAGMA_DIAGNOSTIC_POP_MSVC_() __pragma(warning(pop))
#    define SX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(_x) __pragma(warning(disable : _x))
#else
#    define SX_PRAGMA_DIAGNOSTIC_PUSH_MSVC_()
#    define SX_PRAGMA_DIAGNOSTIC_POP_MSVC_()
#    define SX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(_x)
#endif    // SX_COMPILER_MSVC

#if SX_COMPILER_CLANG
#    define SX_PRAGMA_DIAGNOSTIC_PUSH SX_PRAGMA_DIAGNOSTIC_PUSH_CLANG_
#    define SX_PRAGMA_DIAGNOSTIC_POP SX_PRAGMA_DIAGNOSTIC_POP_CLANG_
#    define SX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC SX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG
#elif SX_COMPILER_GCC
#    define SX_PRAGMA_DIAGNOSTIC_PUSH SX_PRAGMA_DIAGNOSTIC_PUSH_GCC_
#    define SX_PRAGMA_DIAGNOSTIC_POP SX_PRAGMA_DIAGNOSTIC_POP_GCC_
#    define SX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC SX_PRAGMA_DIAGNOSTIC_IGNORED_GCC
#elif SX_COMPILER_MSVC
#    define SX_PRAGMA_DIAGNOSTIC_PUSH SX_PRAGMA_DIAGNOSTIC_PUSH_MSVC_
#    define SX_PRAGMA_DIAGNOSTIC_POP SX_PRAGMA_DIAGNOSTIC_POP_MSVC_
#    define SX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC(_x)
#endif    // SX_COMPILER_

#ifdef __cplusplus
#    define _SX_EXTERN extern "C"
#else
#    define _SX_EXTERN extern
#endif

#if SX_CONFIG_SHARED_LIB
#    if SX_COMPILER_MSVC
#        ifdef sx_EXPORTS
#            define _SX_API_DECL __declspec(dllexport)
#        else
#            define _SX_API_DECL __declspec(dllimport)
#        endif
#    else
#        define _SX_API_DECL __attribute__((visibility("default")))
#    endif
#else
#    define _SX_API_DECL
#endif

#define SX_API _SX_EXTERN _SX_API_DECL

#define sx_enabled(_f) ((_f) != 0)
#define sx_unused(_a) (void)(_a)

#ifdef __cplusplus
#    define sx_cppbool(_b) (_b) ? true : false;
#    define SX_CONSTEXPR constexpr
#else
#    define sx_cppbool(_b) _b
#    define SX_CONSTEXPR 
#endif

// see array.h
#ifndef SX_ARRAY
#   define SX_ARRAY
#endif 

// Idea: https://www.youtube.com/watch?v=QpAhX-gsHMs&t=967s
// sx_defer and scope can be used to mimick the behavior of go and zig's defer 
// "start" is the statement that you would like to run at the begining of the scope
// "end" is the statement that you would like to run at the end of the scope
#define _sx_var(_name) sx_concat(_name, __LINE__)
#define sx_defer(_start, _end) for (int _sx_var(_i_) = (_start, 0); !_sx_var(_i_); (_sx_var(_i_) += 1), _end)
#define sx_scope(_end) for (int _sx_var(_i_) = 0; !_sx_var(_i_); (_sx_var(_i_) += 1), _end)

// somewhat like python's `with` statement
#define sx_with(_init, _release) _init; for (int _sx_var(_i_) = 0; !_sx_var(_i_); (_sx_var(_i_) += 1), _release)

