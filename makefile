all:
	g++ *.cpp -lncurses -o program.o
install:
	sudo apt-get install libncurses5-dev libncursesw5-dev
