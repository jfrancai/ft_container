# Ouput
NAME := ft_container
TESTS := tests

# Flags
CC := c++
STDFLAGS := -std=c++98
CFLAGS :=  -Wall -Werror -Wextra -MD
INCLUDE := -I include/ -I lib/googletest/include
TESTFLAGS := -L lib/googletest/lib -lgtest -lgtest_main -lgmock

# Source dirs
SRCDIR := src/
OBJSDIR := objs/
TESTDIR := test/
DEPSDIR := include/

# Source files
SRC := main.cpp

TEST := map_test.cpp \
	vector_test.cpp \
	stack_test.cpp \
	type_traits_test.cpp

# Objs files
OBJS := $(SRC:%.cpp=$(OBJSDIR)%.o)
OBJSTEST := $(TEST:%.cpp=$(OBJSDIR)%.o)

# Rules
all:
	make $(NAME)

$(TESTS): $(OBJSTEST)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) $^ $(TESTFLAGS) -o $@

$(NAME): $(OBJSDIR)main.o $(OBJS)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) $^ -o $@

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

# Dependencies
-include $(OBJS:.o=.d)
-include $(OBJSTEST:.o=.d)

.PHONY: all clean re fclean retest
