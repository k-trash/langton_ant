#include <ant_lib.hpp>

#include <iostream>

int main(int argc_, char *argv_[]){
	uint32_t count = 0u;
	uint32_t interval, jump_step;

	LangtonAnt ant(1024);

	std::cout << "interval:";
	std::cin >> interval;
	
	std::cout << "jump step:";
	std::cin >> jump_step;

	while(true){
		if((++count)%interval != 0){
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
	}

	ant.displayShape(std::to_string(interval) + "_" + std::to_string(jump_step) + ".png");

	ant.checkLoop(0,2);

	ant.finishAnt();

	return 0;
}
