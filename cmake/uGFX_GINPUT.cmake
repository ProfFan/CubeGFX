SET(uGFX_ginput_SEARCH_PATH ${uGFX_DIR}/src/ginput)

set(uGFX_ginput_HEADERS ginput.h
        ginput_dial.h
        ginput_driver_dial.h
        ginput_driver_keyboard.h
        ginput_driver_mouse.h
        ginput_driver_toggle.h
        ginput_keyboard.h
        ginput_keyboard_microcode.h
        ginput_mouse.h
        ginput_options.h
        ginput_rules.h
        ginput_toggle.h)
set(uGFX_ginput_SOURCES ginput.c
        ginput_dial.c
        ginput_keyboard.c
        ginput_keyboard_microcode.c
        ginput_mouse.c
        ginput_toggle.c)

SET(uGFX_GINPUT_TOUCH_DRIVERS ADS7843 EXC7200 FT5x06 FT6x06 FT5336 Linux-Event MAX11802 MCU STMPE610 STMPE811)

set(uGFX_GINPUT_MODULES ginput)

FOREACH(driver ${uGFX_GINPUT_TOUCH_DRIVERS})
    SET(uGFX_driver_${driver}_SEARCH_PATH ${uGFX_DIR}/drivers/ginput/touch/${driver})
    SET(uGFX_driver_${driver}_SOURCES gmouse_lld_${driver}.c)
    #SET(uGFX_driver_${driver}_HEADERS gdisp_lld_${driver.h)
    LIST(APPEND uGFX_GINPUT_MODULES driver_${driver})
ENDFOREACH()


#MESSAGE(STATUS "ginput: ${uGFX_ginput_SOURCES}")