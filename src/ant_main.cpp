#include <ant_lib.hpp>

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#define SIZE 2048

int main(int argc_, char *argv_[]){
	uint16_t interval, jump_step;
	ofstream result_csv;
	LangtonAnt ant(SIZE);

	std::cout << "interval:";
	std::cin >> interval;
	std::cout << "jump step:";
	std::cin >> jump_step;

	result_csv.open(std::to_string(interval) + "_" + std::to_string(jump_step) + ".csv", std::ios_base::out);

	result_csv << "field, branch, loop" << std::endl;

	for(uint8_t i=0u; i<256; i++){
		ant.resetAnt();

		ant.field[(SIZE>>1)-1][(SIZE>>1)-1] = (bool)(0x01 & (i >> 7));
		ant.field[(SIZE>>1)-1][SIZE>>1] = (bool)(0x01 & (i >> 6));
		ant.field[(SIZE>>1)-1][(SIZE>>1)+1] = (bool)(0x01 & (i >> 5));
		ant.field[SIZE>>1][(SIZE>>1)-1] = (bool)(0x01 & (i >> 4));
		ant.field[SIZE>>1][(SIZE>>1)+1] = (bool)(0x01 & (i >> 3));
		ant.field[(SIZE>>1)+1][(SIZE>>1)-1] = (bool)(0x01 & (i >> 2));
		ant.field[(SIZE>>1)+1][SIZE>>1] = (bool)(0x01 & (i >> 1));
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

		if(ant.checkLoop(0,2) == 0){
			result_csv << std::to_string(i) << ", " << std::to_string(ant.branch_len) << ", " << std::to_string(ant.loop_len) << std::endl;
		}else{
			result_csv << std::to_string(i) << ", x, x" << std::endl;
		}
	}

	result_csv.close();

	ant.finishAnt();

	return 0;
}
