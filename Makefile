#Compile the src files
all:
	$(info =================================)
	$(info Compilation)
	+$(MAKE) -C src

#Clear the directory
clean:
	+$(MAKE) clean -C src

# ./main
run:
	$(info =================================)
	$(info Execution)
	bash -c "src/main"

	