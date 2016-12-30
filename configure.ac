AC_INIT([Vacation Cruft], 0.0.0, [ikey@solus-project.com], [vacation-cruft], [https://github.com/ikeydoherty/vacation-cruft])
AM_INIT_AUTOMAKE([-Wno-portability no-dist-gzip dist-xz foreign subdir-objects 1.9 tar-ustar])
AC_PROG_CC
AC_PROG_CC_STDC
AC_PREFIX_DEFAULT(/usr/local)
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])
LT_PREREQ(2.2)
LT_INIT([disable-static])

# Build requirements
m4_define([sdl_required_version], [2.0.0])

PKG_CHECK_MODULES(SDL,
                 [
                   sdl2 >= sdl_required_version
                   SDL2_image >= sdl_required_version
                 ]
)

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

AC_MSG_RESULT([
        vacation-cruft $VERSION
        =====================

        prefix:                 ${prefix}
        libdir:                 ${libdir}
        sysconfdir:             ${sysconfdir}
        exec_prefix:            ${exec_prefix}
        bindir:                 ${bindir}
        datarootdir:            ${datarootdir}

        compiler:               ${CC}
        cflags:                 ${CFLAGS}
        ldflags:                ${LDFLAGS}
])
