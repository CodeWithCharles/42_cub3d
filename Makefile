# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 16:33:26 by cpoulain          #+#    #+#              #
#    Updated: 2025/02/25 15:39:11 by cpoulain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Includes

include			Files.mk
include			Makefile.colors
include			Makefile.msg
include			Makefile.vars

# Objs formatter

OBJS			=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

# Phony rules

all: $(NAME)

clean:
	@$(RM) -r $(OBJ_DIR)
	@printf $(MSG_RM_DIR) $(OBJ_DIR)

fclean: clean
	@$(RM) -r $(BIN_DIR)
	@printf $(MSG_RM_DIR) $(BIN_DIR)
	@$(RM) $(THDPTY_LIBFT_H)
	@printf $(MSG_RM) $(THDPTY_LIBFT_H)
	@$(RM) $(LIBFT_TARGET)
	@printf $(MSG_RM) $(LIBFT_TARGET)
	@$(RM) $(THDPTY_LIBX_H)
	@printf $(MSG_RM) $(THDPTY_LIBX_H)
	@$(RM) $(LIBX_TARGET)
	@printf $(MSG_RM) $(LIBX_TARGET)

fclean_all: fclean dellibs

dellibs:
	@$(RM) -r $(LIBFT_PATH)
	@printf $(MSG_RM_DEP) $(LIBFT_PATH)
	@$(RM) -r $(LIBX_PATH)
	@printf $(MSG_RM_DEP) $(LIBX_PATH)
	@$(RM) $(THDPTY_LIBFT_H)
	@printf $(MSG_RM) $(THDPTY_LIBFT_H)
	@$(RM) $(LIBFT_TARGET)
	@printf $(MSG_RM) $(LIBFT_TARGET)
	@$(RM) $(THDPTY_LIBX_H)
	@printf $(MSG_RM) $(THDPTY_LIBX_H)
	@$(RM) $(LIBX_TARGET)
	@printf $(MSG_RM) $(LIBX_TARGET)

cleanlibs:
	@$(MAKE) clean -C $(LIBFT_PATH)
	@$(MAKE) clean -C $(LIBX_PATH)

fcleanlibs:
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@$(MAKE) fclean -C $(LIBX_PATH)
	@$(RM) $(THDPTY_LIBFT_H)
	@printf $(MSG_RM) $(THDPTY_LIBFT_H)
	@$(RM) $(LIBFT_TARGET)
	@printf $(MSG_RM) $(LIBFT_TARGET)
	@$(RM) $(THDPTY_LIBX_H)
	@printf $(MSG_RM) $(THDPTY_LIBX_H)
	@$(RM) $(LIBX_TARGET)
	@printf $(MSG_RM) $(LIBX_TARGET)

re: fclean all

relibs: dellibs re

norminette:
	@norminette $(SRC_DIR) $(INC_DIR) | grep -Ev '^Notice|OK!$$'	\
	&& $(ECHO) -e '\033[1;31mNorminette KO!'						\
	|| $(ECHO) -e '\033[1;32mNorminette OK!'

# THDPTY CLONING

libft:
	@if [ ! -d "$(LIBFT_PATH)/.git" ]; then  \
		printf $(MSG_CLONING)  $@;\
		git clone $(LIBFT_GIT) $(LIBFT_PATH) > /dev/null 2>&1;\
		printf $(MSG_DONE_CLONING) $@;\
	else\
		printf $(MSG_DEP_FOUND) $@;\
	fi
	@printf $(MSG_MAKING) $@
	@$(MAKE) --no-print-directory -C $(LIBFT_PATH) > /dev/null 2>&1
	@printf $(MSG_DONE_MAKE) $@
	@sleep 0.2

minilibx:
	@if [ ! -d "$(LIBX_PATH)/.git" ]; then  \
		printf $(MSG_CLONING)  $@;\
		git clone $(LIBX_GIT) $(LIBX_PATH) > /dev/null 2>&1;\
		printf $(MSG_DONE_CLONING) $@;\
	else\
		printf $(MSG_DEP_FOUND) $@;\
	fi
	@printf $(MSG_MAKING) $@
	@$(MAKE) --no-print-directory -C $(LIBX_PATH) > /dev/null 2>&1
	@printf $(MSG_DONE_MAKE) $@
	@sleep 0.2

# Binary / Lib generation

$(NAME): $(THDPTY_DEPS) $(OBJS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -I$(INC_DIR) $(THDPTY_TARGETS) -o $@
	@printf "$(TERM_CLEAR_LINE)\n  ✅  $(TERM_GREEN)Done building executable $(TERM_BLUE)\"%s\"$(TERM_GREEN) !$(TERM_RESET)\n" $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@printf "$(TERM_CLEAR_LINE)🔨 $(TERM_CYAN)Compiling $(TERM_MAGENTA)\"%s\"$(TERM_CYAN)...$(TERM_RESET)" $<
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

# Third party compilation

$(THDPTY_LIBFT_H): libft
	@cp -u $(LIBFT_PATH)/$(LIBFT_INC_H) $@

$(LIBFT_TARGET): libft
	@cp $(LIBFT_PATH)/$@ ./

$(THDPTY_LIBX_H): minilibx
	@cp -u $(LIBX_PATH)/$(LIBX_INC_H) $@

$(LIBX_TARGET): minilibx
	@cp $(LIBX_PATH)/$@ ./

.PHONY: all clean fclean re norminette cleanlibs fcleanlibs fclean_all dellibs libft minilibx
