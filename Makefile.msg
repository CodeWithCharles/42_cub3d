# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile.msg                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 12:53:06 by cpoulain          #+#    #+#              #
#    Updated: 2025/02/20 13:40:14 by cpoulain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Messages

#	RM_MSG

MSG_RM_DIR			:=	"\t❌  $(TERM_RED) Removed $(TERM_YELLOW)\"%s\"$(TERM_RED) directory.$(TERM_RESET)\n"
MSG_RM				:=	"\t❌  $(TERM_RED) Removed $(TERM_YELLOW)\"%s\"$(TERM_RED).$(TERM_RESET)\n"
MSG_RM_DEP			:=	"\t❌  $(TERM_RED) Removed $(TERM_YELLOW)\"%s\"$(TERM_RED) dependency.$(TERM_RESET)\n"

#	THDPTY_MSG

MSG_MAKING			:=	"\n\t\t🔨  $(TERM_YELLOW)Making $(TERM_BLUE)\"%s\"$(TERM_YELLOW)...$(TERM_RESET)"
MSG_DONE_MAKE		:=	"\n\t✅  $(TERM_YELLOW)Done making $(TERM_GREEN) \"%s\" $(TERM_YELLOW)!$(TERM_RESET)\n\n"
MSG_CLONING			:=	"\n\t\t🔨  $(TERM_YELLOW)Dependency $(TERM_BLUE)\"%s\"$(TERM_YELLOW) not found ! Cloning dependency... $(TERM_RESET)"
MSG_DONE_CLONING	:=	"\n\t✅  $(TERM_YELLOW)Done cloning $(TERM_GREEN) \"%s\" $(TERM_YELLOW)!$(TERM_RESET)\n"
MSG_DEP_FOUND		:=	"\n\t✅  $(TERM_GREEN)\"%s\" $(TERM_YELLOW)dependency found !$(TERM_RESET)"
