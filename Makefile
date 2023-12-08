day = $(shell basename `pwd`)
file = $(day).c

run: $(file)
	@echo "Compiling $(day)..."
	@gcc -o $(day) $(day).c
	@echo "Running $(day)..."
	@./$(day)
