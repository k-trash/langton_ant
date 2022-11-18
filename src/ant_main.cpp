#include <ant_lib.hpp>

#include <iostream>
#include <string>

#define SIZE 2048

int main(int argc_, char *argv_[]){
	LangtonAnt ant(SIZE);

	for(uint8_t i=0u; i<8;i++){
		ant.resetAnt();

		ant.field[SIZE/2-1][SIZE/2-1] = 0x01 & (i >> 7);
		ant.field[SIZE/2-1][SIZE/2] = 0x01 & (i >> 6);
		ant.field[SIZE/2-1][SIZE/2+1] = 0x01 & (i >> 5);
		ant.field[SIZE/2][SIZE/2-1] = 0x01 & (i >> 4);
		ant.field[SIZE/2][SIZE/2+1] = 0x01 & (i >> 3);
		ant.field[SIZE/2+1][SIZE/2-1] = 0x01 & (i >> 2);
		ant.field[SIZE/2+1][SIZE/2] = 0x01 & (i >> 1);
		ant.field[SIZE/2+1][SIZE/2+1] = 0x01 & i;

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

		ant.displayShape("0_0_" + std::to_string(i) + ".png");

		std::cout << i << ':';

		ant.checkLoop(0,2);
	}

	ant.finishAnt();

	return 0;
}
