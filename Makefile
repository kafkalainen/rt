NAME = rt

SRCS = \
	main.cpp \
	Application.class.cpp \

HEADERS = \
	headers/rt.hpp \
#	libkaf/libkaf.h \

CC = g++

ABS_DIR = $(shell pwd)

LIBS = -Llibkaf/

#SFML build
SFML_SRCS = $(ABS_DIR)/sfml
SFML_BUILD = $(SFML_SRCS)/build
SFML_LIBS = $(SFML_SRCS)/libs

CFLAGS_SFML = $(shell export PKG_CONFIG_PATH=$(SFML_LIBS)/pkgconfig && pkg-config --cflags sfml-all)
LIBS_SFML = $(shell export PKG_CONFIG_PATH=$(ABS_DIR)/glfw/lib/pkgconfig && pkg-config --static --libs sfml-all)

INCLUDES = -I$(SFML_LIBS)/include
#INCLUDES = -Ilibkaf -I$(SFML_LIBS)/include
CFLAGS = -Wall -Wextra -g -std=c++17 -O2 $(CFLAGS_GLFW)
LDFLAGS = -lkaf $(LIBS_GLFW) "-Wl,-rpath,$(GLFW_LIBS)/lib" -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

MKDIR := mkdir -p
RM = /bin/rm -rf
RESET = "\033[0m"
RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[0;33m"
BLUE = "\033[0;34m"
MAGENTA = "\033[0;35m"
CYAN = "\033[0;36m"
WHITE = "\033[0;37m"
OPENGL = $(shell pkg-config --libs gl)

S = srcs
O = objs

LIBKAF = libkaf/libkaf.a
SRC = $(addprefix $S/, $(SRCS))
OBJ = $(SRC:$S%=$O%.o)

.PHONY: all dependencies clean fclean re

all: $(NAME)

dependencies:
	sudo apt install libc-dev libstdc++6 libgcc-s1 libudev1 libfreetype6 libx11-dev libxrandr-dev xorg x11-xserver-utils libgl-dev libflac-dev libogg-dev libopenal1 libopenal-dev libstdc++6 libvorbis-dev cmake-curses-gui doxygen

$(SFML_LIBS):
	@if [ ! -d $(SFML_SRCS) ]; then \
		git clone https://github.com/SFML/SFML.git sfml; \
	fi
	@if [ ! -d $(SFML_LIBS) ]; then \
  		cd $(SFML_SRCS) && \
        mkdir build && cd build && \
        cmake -DCMAKE_INSTALL_PREFIX:PATH=$(SFML_LIBS) -DSFML_BUILD_DOC:BOOL=ON -DSFML_BUILD_EXAMPLES:BOOL=ON .. && \
        make && \
        make install; \
    fi


$(GLAD):
	@if [ ! -d $(GLAD) ]; then \
		mkdir -p glad && \
		unzip glad.zip -d glad && \
		mv glad/src/glad.c srcs/glad.c; \
	fi

$O:
	$(MKDIR) $@

$(OBJ): | $O

$(OBJ): $O%.o: $S% $(HEADERS)
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDES) $<

#$(LIBKAF):
#	make -C libkaf

#$(NAME): $(GLFW_LIBS) $(GLAD) $(SPV) $(OBJ)

$(NAME): $(SFML_LIBS) $(OBJ)
	$(CC) -o $@ $(INCLUDES) $(LIBS) $(CFLAGS) $(OBJ) $(LDFLAGS)
	@echo $(GREEN)Compiled executable $(NAME).

cleanobj:
ifneq ($(wildcard $(OBJ)),)
	@$(RM) $(wildcard $(OBJ))
endif
ifneq ($(wildcard $(SPV)),)
	@$(RM) $(wildcard $(SPV))
endif

cleanobjdir: cleanobj
	@$(RM) $O
	@$(RM) $P

clean: cleanobjdir
	@if [ -d "$(GLFW_LIBS)" ] ; then \
	make -C $(GLFW_LIBS) clean ; \
	fi;
	@make -C libkaf clean
	@echo $(GREEN)Cleaned projects from object files.$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(GLFW_SRCS)
	@$(RM) $(GLFW_LIBS)
	@$(RM) $(GLAD)
	@make -C libkaf fclean
	@echo $(GREEN)Removed binaries and libraries.$(RESET)

re: fclean all
