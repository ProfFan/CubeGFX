SET(uGFX_gwin_SEARCH_PATH ${uGFX_DIR}/src/gwin)

set(uGFX_gwin_HEADERS gwin.h
        gwin_button.h
        gwin_checkbox.h
        gwin_class.h
        gwin_console.h
        gwin_container.h
        gwin_frame.h
        gwin_gl3d.h
        gwin_graph.h
        gwin_image.h
        gwin_keyboard.h
        gwin_keyboard_layout.h
        gwin_label.h
        gwin_list.h
        gwin_options.h
        gwin_progressbar.h
        gwin_radio.h
        gwin_rules.h
        gwin_slider.h
        gwin_tabset.h
        gwin_textedit.h
        gwin_widget.h)
set(uGFX_gwin_SOURCES gwin.c
        gwin_button.c
        gwin_checkbox.c
        gwin_console.c
        gwin_container.c
        gwin_frame.c
        gwin_gl3d.c
        gwin_graph.c
        gwin_image.c
        gwin_keyboard.c
        gwin_keyboard_layout.c
        gwin_label.c
        gwin_list.c
        gwin_progressbar.c
        gwin_radio.c
        gwin_slider.c
        gwin_tabset.c
        gwin_textedit.c
        gwin_widget.c
        gwin_wm.c)

set(uGFX_GWIN_MODULES gwin)