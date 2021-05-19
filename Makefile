##
# ft_irc
#
# @make
# @version 0.1.1
#
default: all
#==============================================================================#
#--------------------------------- SHELL --------------------------------------#
#==============================================================================#
SHELL			:= /bin/sh
#==============================================================================#
#------------------------------ DIRECTORIES -----------------------------------#
#==============================================================================#
SRCS_DIR		 = src/
OBJS_DIR		 = obj/
#==============================================================================#
#--------------------------------- FILES --------------------------------------#
#==============================================================================#
SRCS_NAME		  = parse_message
SRCS_NAME		  += rec_data
SRCS_NAME		  += tcp_main
SRCS_NAME		  += Utils
SRCS_NAME		  += Server
SRCS_NAME		  += replies
SRCS_NAME		  += reg_cmds
SRCS_NAME		  += parse_channels
#------------------------------------------------------------------------------#
CLIENTSRC		 = client/tcp_chat_client
#------------------------------------------------------------------------------#
SRCS			 = $(addprefix ${SRCS_DIR}, $(addsuffix .cpp, ${SRCS_NAME}))
#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#
OBJS			 = $(patsubst ${SRCS_DIR}%.cpp,${OBJS_DIR}%.o,${SRCS})
#------------------------------------------------------------------------------#
NAME			 = ircserv
#------------------------------------------------------------------------------#
#==============================================================================#
#-------------------------------- COMPILER ------------------------------------#
#==============================================================================#
CC				 = clang++
CFLAGS			+= -Wall
CFLAGS			+= -Wextra
CFLAGS			+= -Werror
CFLAGS			+= -pedantic
CFLAGS			+= -std=c++98
#--------------------------------- UNIX ---------------------------------------#
#==============================================================================#
RM				= rm -rf
MKDIR			= mkdir -p
#==============================================================================#
#--------------------------------- RULES --------------------------------------#
#==============================================================================#
${OBJS_DIR}%.o:	${SRCS_DIR}%.cpp
	${CC} -c ${CFLAGS} ${CDEFS} -o $@ $< ${LDFLAGS}
#------------------------------------------------------------------------------#
${OBJS_DIR}:
	${MKDIR} ${OBJS_DIR}
#------------------------------------------------------------------------------#
$(NAME): ${OBJS}
	${CC} ${CFLAGS} ${CDEFS} -o ${NAME} ${OBJS} ${LDFLAGS}
#------------------------------------------------------------------------------#
all: ${OBJS_DIR} ${NAME} ctest
#------------------------------------------------------------------------------#
asan: CFLAGS += -g3
asan: CFLAGS += -fsanitize=address
asan: LFTRULE = asan
asan: all
#------------------------------------------------------------------------------#
msan: CFLAGS += -g3
msan: CFLAGS += -fsanitize=memory
msan: CFLAGS += -fsanitize-memory-track-origins
msan: CFLAGS += -fno-common
msan: CFLAGS += -fno-omit-frame-pointer
msan: LFTRULE = msan
msan: all
#------------------------------------------------------------------------------#

tags:
	ctags -e -R .
#------------------------------------------------------------------------------#
clean:
	${RM} ${OBJS_DIR} vgcore*
#------------------------------------------------------------------------------#
fclean: clean
	${RM} ${NAME} ${NAME}.core ${NAME}.dSYM/ valgrind.log ctest
#------------------------------------------------------------------------------#
re: fclean all
#------------------------------------------------------------------------------#
ctest: ${CLIENTSRC}.c
	clang client/tcp_chat_client.c -o ctest
#------------------------------------------------------------------------------#
.PHONY:	all clean clean fclean re debug asan

# end
