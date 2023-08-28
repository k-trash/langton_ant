#include <ant_lib.hpp>

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <random>

#define SIZE 2048

int main(int argc_, char *argv_[]){
	uint32_t interval, jump_step;
	uint32_t count = 0u;
	uint32_t max_val = 100000u;
	uint32_t i = 0;
	std::ofstream result_csv;
	LangtonAnt ant(SIZE);

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	std::uniform_int_distribution<uint32_t> dist1(0, 100000000);

	interval = atoi(argv_[1]);
	jump_step = atoi(argv_[2]);
	max_val = atoi(argv_[3]);

	result_csv.open(std::to_string(interval) + "_" + std::to_string(jump_step) + ".csv", std::ios_base::out);

	result_csv << "field, branch, loop" << std::endl;

	for(uint32_t k=0; k<max_val; k++){
		i = dist1(engine);

		ant.resetAnt();

		ant.field[(SIZE>>1)-2][(SIZE>>1)-2] = (bool)(0x01 & (i >> 23));
		ant.field[(SIZE>>1)-2][(SIZE>>1)-1] = (bool)(0x01 & (i >> 22));
		ant.field[(SIZE>>1)-2][(SIZE>>1)] = (bool)(0x01 & (i >> 21));
		ant.field[(SIZE>>1)-2][(SIZE>>1)+1] = (bool)(0x01 & (i >> 20));
		ant.field[(SIZE>>1)-2][(SIZE>>1)+2] = (bool)(0x01 & (i >> 19));
		ant.field[(SIZE>>1)-1][(SIZE>>1)-2] = (bool)(0x01 & (i >> 18));
		ant.field[(SIZE>>1)-1][(SIZE>>1)-1] = (bool)(0x01 & (i >> 17));
		ant.field[(SIZE>>1)-1][(SIZE>>1)] = (bool)(0x01 & (i >> 16));
		ant.field[(SIZE>>1)-1][(SIZE>>1)+1] = (bool)(0x01 & (i >> 15));
		ant.field[(SIZE>>1)-1][(SIZE>>1)+2] = (bool)(0x01 & (i >> 14));
		ant.field[(SIZE>>1)][(SIZE>>1)-2] = (bool)(0x01 & (i >> 13));
		ant.field[(SIZE>>1)][(SIZE>>1)-1] = (bool)(0x01 & (i >> 12));
		ant.field[(SIZE>>1)][(SIZE>>1)+1] = (bool)(0x01 & (i >> 11));
		ant.field[(SIZE>>1)][(SIZE>>1)+2] = (bool)(0x01 & (i >> 10));
		ant.field[(SIZE>>1)+1][(SIZE>>1)-2] = (bool)(0x01 & (i >> 9));
		ant.field[(SIZE>>1)+1][(SIZE>>1)-1] = (bool)(0x01 & (i >> 8));
		ant.field[(SIZE>>1)+1][(SIZE>>1)] = (bool)(0x01 & (i >> 7));
		ant.field[(SIZE>>1)+1][(SIZE>>1)+1] = (bool)(0x01 & (i >> 6));
		ant.field[(SIZE>>1)+1][(SIZE>>1)+2] = (bool)(0x01 & (i >> 5));
		ant.field[(SIZE>>1)+2][(SIZE>>1)-2] = (bool)(0x01 & (i >> 4));
		ant.field[(SIZE>>1)+2][(SIZE>>1)-1] = (bool)(0x01 & (i >> 3));
		ant.field[(SIZE>>1)+2][(SIZE>>1)] = (bool)(0x01 & (i >> 2));
		ant.field[(SIZE>>1)+2][(SIZE>>1)+1] = (bool)(0x01 & (i >> 1));
		ant.field[(SIZE>>1)+2][(SIZE>>1)+2] = (bool)(0x01 & i);

		count = 0u;

		while(true){
			try{
				count = (count + 1) % interval;

				if(count != 0){
					if(ant.readColor() == BLACK){
						ant.turnAnt(RIGHT);
					}else{
						ant.turnAnt(LEFT);
					}

					ant.updateField();
					if(ant.moveAnt(1, ant.direction) == 1){
						break;
					}
				}else{
					ant.updateField();
					if(ant.moveAnt(jump_step, ant.direction) == 1){
						break;
					}
				}
			}catch(std::exception& e){
				std::cerr << "!" << e.what() << std::endl;
				exit(1);
			}
		}

//		ant.displayShape(std::to_string(interval) + "_" + std::to_string(jump_step) + "_" + std::to_string(i) + ".png");

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
