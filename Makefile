.PHONY: build
build:
	gcc -o ./build/ub ./main.c
install:
	if [ ! -d ./backup ]; then mkdir ./backup; fi

	echo "Backing up .bashrc to ./backup/.bashrc"
	cp ~/.bashrc ./backup/.bashrc

	echo "export PATH=\$$PATH:$(PWD)/build" >> ~/.bashrc