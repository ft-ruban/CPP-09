override SRCSDIR	:= srcs/
override MAINDIR    :=

override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

SRC += $(addprefix $(MAINDIR), $(addsuffix .cpp, $(MAIN)))

override MAIN := 	main \
