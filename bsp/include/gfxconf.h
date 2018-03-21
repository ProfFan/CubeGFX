/**
 * This file has a different license to the rest of the GFX system.
 * You can copy, modify and distribute this file as you see fit.
 * You do not need to publish your source modifications to this file.
 * The only thing you are not permitted to do is to relicense it
 * under a different license.
 */

#ifndef _GFXCONF_H
#define _GFXCONF_H

/* The operating system to use. One of these must be defined - preferably in your Makefile */
//#define GFX_USE_OS_CHIBIOS                           TRUE
#define GFX_USE_OS_FREERTOS                            TRUE
//    #define GFX_FREERTOS_USE_TRACE                   FALSE
//#define GFX_USE_OS_WIN32                             FALSE
//#define GFX_USE_OS_LINUX                             FALSE
//#define GFX_USE_OS_OSX                               FALSE
//#define GFX_USE_OS_ECOS                              FALSE
//#define GFX_USE_OS_RAWRTOS                           FALSE
//#define GFX_USE_OS_ARDUINO                           FALSE
//#define GFX_USE_OS_KEIL                              FALSE
//#define GFX_USE_OS_CMSIS                             FALSE
//#define GFX_USE_OS_RAW32                             TRUE
//#define GFX_USE_OS_NIOS                              FALSE
//    #define INTERRUPTS_OFF()                         optional_code
//    #define INTERRUPTS_ON()                          optional_code

// Options that (should where relevant) apply to all operating systems
//    #define GFX_NO_INLINE                            FALSE
//    #define GFX_COMPILER                             GFX_COMPILER_UNKNOWN
    #define GFX_CPU                                  GFX_CPU_CORTEX_M4
//    #define GFX_CPU_NO_ALIGNMENT_FAULTS              FALSE
//    #define GFX_CPU_ENDIAN                           GFX_CPU_ENDIAN_UNKNOWN
//    #define GFX_OS_HEAP_SIZE                         40960
    #define GFX_OS_NO_INIT                           TRUE
//    #define GFX_OS_INIT_NO_WARNING                   TRUE
//    #define GFX_OS_PRE_INIT_FUNCTION                 Raw32OSInit
//    #define GFX_OS_EXTRA_INIT_FUNCTION               myOSInitRoutine
//    #define GFX_OS_EXTRA_DEINIT_FUNCTION             myOSDeInitRoutine
//    #define GFX_EMULATE_MALLOC                       FALSE
//#define GFX_USE_DIRECTIO TRUE

///////////////////////////////////////////////////////////////////////////
// GDISP                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GDISP                                TRUE

#define GDISP_NEED_VALIDATION                        TRUE
#define GDISP_NEED_CLIP                              TRUE
#define GDISP_NEED_CIRCLE                            TRUE
#define GDISP_NEED_CONVEX_POLYGON                    TRUE
//#define GDISP_NEED_SCROLL                            TRUE
#define GDISP_NEED_CONTROL                           TRUE
#define GDISP_NEED_TEXT                              TRUE
    #define GDISP_INCLUDE_FONT_UI2                   TRUE
#define GDISP_NEED_STREAMING    TRUE

#define GDISP_NEED_IMAGE                             TRUE
    #define GDISP_NEED_IMAGE_BMP                     TRUE
    #define GDISP_NEED_IMAGE_GIF                     TRUE

#define GDISP_DEFAULT_ORIENTATION                    GDISP_ROTATE_LANDSCAPE
#define GDISP_NEED_MULTITHREAD                       TRUE
#define GDISP_NEED_STARTUP_LOGO                      FALSE

//#define GDISP_HARDWARE_PIXELREAD                     TRUE
/********************************************************/
/* Font stuff                                           */
/********************************************************/
#define GDISP_NEED_TEXT TRUE
#define GDISP_NEED_ANTIALIAS FALSE
#define GDISP_NEED_TEXT_KERNING FALSE
#define GDISP_NEED_UTF8 FALSE
#define GDISP_INCLUDE_USER_FONTS TRUE

///////////////////////////////////////////////////////////////////////////
// GWIN                                                                  //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GWIN                                 TRUE

#define GWIN_NEED_WINDOWMANAGER                      TRUE
    #define GWIN_NEED_FLASHING                       TRUE

#define GWIN_NEED_CONSOLE                            TRUE
    #define GWIN_CONSOLE_USE_HISTORY                 TRUE
        #define GWIN_CONSOLE_HISTORY_AVERAGING       TRUE
        #define GWIN_CONSOLE_HISTORY_ATCREATE        TRUE
#define GWIN_NEED_GRAPH                              TRUE

#define GWIN_NEED_WIDGET                             TRUE
    #define GWIN_NEED_LABEL                          TRUE
        #define GWIN_LABEL_ATTRIBUTE                 TRUE
    #define GWIN_NEED_BUTTON                         TRUE
//        #define GWIN_BUTTON_LAZY_RELEASE             TRUE
    #define GWIN_NEED_SLIDER                         TRUE
    #define GWIN_NEED_CHECKBOX                       TRUE
    #define GWIN_NEED_IMAGE                          TRUE
    #define GWIN_NEED_RADIO                          TRUE
    #define GWIN_NEED_LIST                           TRUE
        #define GWIN_NEED_LIST_IMAGES                TRUE
    #define GWIN_NEED_PROGRESSBAR                    TRUE
        #define GWIN_PROGRESSBAR_AUTO                TRUE
    #define GWIN_NEED_KEYBOARD TRUE
    #define GWIN_NEED_TEXTEDIT TRUE
#define GWIN_NEED_CONTAINERS                         TRUE
    #define GWIN_NEED_CONTAINER                      TRUE

#define GWIN_NEED_TABSET                             TRUE

///////////////////////////////////////////////////////////////////////////
// GEVENT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GEVENT                               TRUE

///////////////////////////////////////////////////////////////////////////
// GTIMER                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GTIMER                               TRUE

///////////////////////////////////////////////////////////////////////////
// GQUEUE                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GQUEUE                               TRUE

#define GQUEUE_NEED_ASYNC                            TRUE

///////////////////////////////////////////////////////////////////////////
// GINPUT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GINPUT                               TRUE

#define GINPUT_NEED_MOUSE                            TRUE
//#define GINPUT_NEED_TOGGLE                           TRUE
//#define GINPUT_NEED_DIAL                             TRUE

///////////////////////////////////////////////////////////////////////////
// GFILE                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GFILE                                TRUE

#define GFILE_NEED_PRINTG                            TRUE
#define GFILE_NEED_STRINGS                           TRUE

#define GFILE_NEED_ROMFS                             TRUE
//#define GFILE_NEED_NATIVEFS                          TRUE

///////////////////////////////////////////////////////////////////////////
// GMISC                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GMISC               FALSE
#define GMISC_NEED_INVSQRT          TRUE
#define GMISC_NEED_MATRIXFLOAT2D    TRUE
#define GMISC_NEED_MATRIXFIXED2D    TRUE
#endif /* _GFXCONF_H */
