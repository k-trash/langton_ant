#pragma once

#include <string>
#include <vector>

#define RIGHT 0
#define LEFT 1
#define BLACK 0
#define WHITE 1

class LangtonAnt{
	public:
		LangtonAnt(uint16_t field_size_);

		int moveAnt(uint16_t step_, uint8_t direction_);
		void turnAnt(uint8_t way_);
		void updateField(void);
		bool readColor(void);
		int displayShape(std::string file_name_);
		int checkLoop(uint32_t start_branch_, uint32_t start_loop);
		void finishAnt(void);
		
		uint8_t direction;
	private:
		bool **field;
		uint16_t field_size;
		std::vector<uint8_t> steps;
		uint16_t pos_x, pos_y;
};
