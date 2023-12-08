day = $(shell basename `pwd`)
file = $(day).c

run: $(file)
	@echo "Compiling $(day)..."
	@gcc -Wall -Wextra -std=c2x -pedantic -o $(day) $(day).c -lssl -lcrypto
	@echo "Running $(day)..."
	@./$(day)
