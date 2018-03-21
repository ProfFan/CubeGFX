SET(uGFX_gfile_SEARCH_PATH ${uGFX_DIR}/src/gfile)

set(uGFX_gfile_HEADERS gfile.h
        gfile_fatfs_wrapper.h
        gfile_fs.h
        gfile_options.h
        gfile_petitfs_wrapper.h
        gfile_rules.h)
set(uGFX_gfile_SOURCES gfile.c
        gfile_fatfs_diskio_chibios.c
        gfile_fatfs_wrapper.c
        gfile_fs_chibios.c
        gfile_fs_fatfs.c
        gfile_fs_mem.c
        gfile_fs_native.c
        gfile_fs_petitfs.c
        gfile_fs_ram.c
        gfile_fs_rom.c
        gfile_fs_strings.c
        gfile_petitfs_diskio_chibios.c
        gfile_petitfs_wrapper.c
        gfile_printg.c
        gfile_scang.c
        gfile_stdio.c)

set(uGFX_GFILE_MODULES gfile)