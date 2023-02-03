NAME := ft_container

CC := c++
STDFLAGS := -std=c++98
CFLAGS := -Wall -Werror -Wextra
INCLUDE := -I include/
TESTFLAGS := -lgtest -lgtest_main -lgmock

SRCDIR := src/
OBJSDIR := objs/
TESTDIR := test/

SRC :=

TEST := redblacktree_test.cpp \
	map_test.cpp	

OBJS := $(SRC:%.cpp=$(OBJSDIR)%.o)
OBJSTEST := $(TEST:%.cpp=$(OBJSDIR)%.o)

ifeq ($(INT_ONLY), 1)
	CFLAGS += -DINT_ONLY
endif

all:
	make $(NAME)

$(NAME): $(OBJSDIR)main.o $(OBJS)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) $^ -o $@

tests: $(OBJS) $(OBJSTEST)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) $^ $(TESTFLAGS) -o $@

$(OBJSDIR)%.o: $(TESTDIR)%.cpp 
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) -c $< -o $@

$(OBJSDIR)%.o: $(SRCDIR)%.cpp 
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJSDIR) 

fclean: clean
	rm -rf $(NAME)
	rm -rf tests

re: fclean
	make $(NAME)

retest: fclean
	make tests

reint: fclean
	make tests INT_ONLY=1

.PHONY: all clean re fclean tests retest reint
