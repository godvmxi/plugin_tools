#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libClient.la

#######################################
# Build information for each library

# Sources for libClient
libClient_la_SOURCES = libClient.c logger.c netutils.c  \
			buffer.c sysutils.c md5.c base64.c fifobuffer.c capisys.c \
			capi-app-mgr.c\
			capi-dbus-service.c \
			capi-handset-api.c \
			capi-sys-service.c  \
			capi-variable-type.c

# Linker options libTestProgram
libClient_la_LDFLAGS =  `pkg-config --libs jansson`  -L/usr/lib -llog4c

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libClient_la_CPPFLAGS = -I$(top_srcdir)/include   -I$(top_srcdir)/libClient -std=c99 `pkg-config --cflags glib-2.0`

