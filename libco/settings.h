#if defined(LIBCO_C)

/*[amd64, arm, ppc, x86]:
   by default, co_swap_function is marked as a text (code) section
   if not supported, uncomment the below line to use mprotect instead */
/* #define LIBCO_MPROTECT */

/*[amd64]:
   Win64 only: provides a substantial speed-up, but will thrash XMM regs
   do not use this unless you are certain your application won't use SSE */
/* #define LIBCO_NO_SSE */

#if defined(LIBCO_C)
  #if defined(LIBCO_MP)
    #define thread_local __thread
  #else
    #define thread_local
  #endif
#endif

#if __STDC_VERSION__ >= 201112L
  #if !defined(_MSC_VER)
    #include <stdalign.h>
  #endif
#else
  #define alignas(bytes)
#endif

#if defined(_MSC_VER)
  #define section(name) __declspec(allocate("." #name))
#elif defined(__APPLE__)
  #define section(name) __attribute__((section("__TEXT,__" #name)))
#elif defined(__SWITCH__)
  /*
    This is basically the same as the last case, however the "#" suffix will create a secondary .text section.
    Because of that, the toolchain will treat the section as non-executable. This might be related to the linker scripts
    used for libnx homebrew. The reason that this is a seperate ifdef, is purely to silence a cosmetic warn
    about ignoring the +w attribute on .text which would happen on other platforms under some conditions (said warning is by design 
    when data is being merged like this into .text).
  */
  #define section(name) __attribute__((section("." #name)))
#else
  #define section(name) __attribute__((section("." #name "#")))
#endif

/* if defined(LIBCO_C) */
#endif
