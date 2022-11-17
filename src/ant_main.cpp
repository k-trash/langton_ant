#include <ant_lib.hpp>

int main(int argc_, char *argv_[]){
	LangtonAnt ant(1024);

	while(true){
		if(ant.readColor() == BLACK){
			ant.turnAnt(RIGHT);
		}else{
			ant.turnAnt(LEFT);
		}

		ant.updateField();
		if(ant.moveAnt(1, ant.direction) == 1){
			break;
		}
	}

	ant.displayShape("test.png");

	ant.checkLoop(0,2);

	ant.finishAnt();

	return 0;
}
