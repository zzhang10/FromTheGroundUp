CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD
EXEC = FTGU
OBJECTS = main.o observer.o globalSettings.o subject.o world.o item/item.o\
	display/cell.o display/displaymsg.o display/textdisplay.o enemy/enemy.o\
	enemy/defender.o enemy/ninja.o enemy/mercenary.o enemy/xenosite.o\
	enemy/tankmaster.o enemy/vindicator.o enemy/warlock.o enemy/wizard.o\
	player/player.o player/mannequin.o player/hacker.o player/middleman.o\
	player/meatshield.o player/maddude.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}



