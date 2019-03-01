#ifndef CORE_H
#define CORE_H

#ifdef MX_PLATFORM_WINDOWS_X64
    #ifdef MX_BUILD_DLL
        #define MX_API __declspec(dllexport)
    #else   
        #define MX_API __declspec(dllimport)
    #endif
#else
    #error Matrix only supports Windows x64
#endif

#endif // CORE_H