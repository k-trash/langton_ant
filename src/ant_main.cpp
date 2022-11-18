#include <ant_lib.hpp>

#include <iostream>
#include <cstdlib>
#include <string>

const uint16_t SIZE = 1024;

int main(int argc_, char *argv_[]){
	LangtonAnt ant(SIZE);

	uint16_t i = 0u;

	for(i=0u; i<256; i++){
		ant.resetAnt();

		ant.field[(SIZE>>1)-1][(SIZE>>1)-1] = (bool)(0x01 & (i >> 7));
		ant.field[(SIZE>>1)-1][SIZE>>1] = (bool)(0x01 & (i >> 6));
		ant.field[(SIZE>>1)-1][(SIZE>>1)+1] = (bool)(0x01 & (i >> 5));
		ant.field[SIZE>>1][(SIZE>>1)-1] = (bool)(0x01 & (i >> 4));
		ant.field[SIZE>>1][(SIZE>>1)+1] = (bool)(0x01 & (i >> 3));
		ant.field[(SIZE>>1)+1][(SIZE>>1)-1] = (bool)(0x01 & (i >> 2));
		ant.field[(SIZE>>1)+1][SIZE>>1] = (0x01 & (i >> 1) == 1) ? true : false;
		ant.field[(SIZE>>1)+1][(SIZE>>1)+1] = (bool)(0x01 & i);

		while(true){
			try{
				if(ant.readColor() == BLACK){
					ant.turnAnt(RIGHT);
				}else{
					ant.turnAnt(LEFT);
				}

				ant.updateField();
				if(ant.moveAnt(1, ant.direction) == 1){
					break;
				}
			}catch(std::exception& e){
				std::cerr << "!" << e.what() << std::endl;
				exit(1);
			}
		}

		ant.displayShape("0_0_" + std::to_string(i) + ".png");

		std::cout << std::to_string(i) << ':';

		ant.checkLoop(0,2);
	}

	ant.finishAnt();

	return 0;
}
