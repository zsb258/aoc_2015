day = $(shell basename `pwd`)
file = $(day).c

out = $(day)
memcheck-out = $(day)-memcheck

FLAGS = -Wall -Wextra -std=c2x -pedantic
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

run: build
	@echo "Running $(day)..."
	@./$(day)

build: $(file)
	@echo "Compiling $(day)..."
	@gcc $(FLAGS) -o $(out) $(day).c

memcheck: $(file)
	@echo "Compiling $(day)..."
	@gcc $(FLAGS) $(ASANFLAGS) -o $(memcheck-out) $(day).c
	@echo "Running $(day) with memcheck..."
	@./$(day)-memcheck
	@echo "memcheck ok."
	
clean:
	@echo "Cleaning $(day)..."
	@rm -f $(out)
	@rm -f $(memcheck-out)
	@echo "Clean ok."
