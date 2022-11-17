#include <ant_lib.hpp>

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <png.h>

LangtonAnt::LangtonAnt(uint16_t field_size_){
	field_size = field_size_;

	try{
		field = new bool*[field_size];
		for(uint16_t i=0; i<field_size; i++){
			field[i] = new bool[field_size];
		}
	}catch(const std::bad_alloc& e){
		std::cerr << "Couldn't prepare enough field." << std::endl;

		exit(1);
	}

	for(uint16_t i=0; i<field_size; i++){
		for(uint16_t j=0; j<field_size; j++){
			field[i][j] = 0;
		}
	}

	pos_x = pos_y = field_size >> 1;
}

int LangtonAnt::moveAnt(uint16_t step_, uint8_t direction_){
	if(steps.size() >= steps.max_size()){
		std::cout << "Step overflow." << std::endl;

		return 1;
	}

	switch(direction_){
		case 0:
			if(pos_y < step_){
				std::cout << "Field overflow." << std::endl;

				return 1;
			}
			pos_y -= step_;
			steps.push_back(0);
		
			break;
		case 1:
			if(pos_x > field_size - step_){
				std::cout << "Field overflow." << std::endl;

				return 1;
			}
			pos_x += step_;
			steps.push_back(1);

			break;
		case 2:
			if(pos_y > field_size - step_){
				std::cout << "Field overflow." << std::endl;

				return 1;
			}
			pos_y += step_;
			steps.push_back(2);

			break;
		case 3:
			if(pos_x < step_){
				std::cout << "Field overflow." << std::endl;

				return 1;
			}
			pos_x -= step_;
			steps.push_back(3);

			break;
	}

	return 0;
}

void LangtonAnt::turnAnt(uint8_t way_){
	direction = (direction + 3 + 2 * way_) % 4;
}

void LangtonAnt::updateField(void){
	field[pos_y][pos_x] = 1 - readColor();
}

bool LangtonAnt::readColor(void){
	return field[pos_y][pos_x];
}

int LangtonAnt::displayShape(std::string file_name_){
	FILE* image_file;
	png_structp image_ptr;
	png_infop info_ptr;
	png_bytep *row_ptrs;

	row_ptrs = new png_bytep[field_size];
	for(uint16_t i=0; i<field_size; i++){
		row_ptrs[i] = new png_byte[(field_size+7)/8];
		for(uint16_t j=0; j<(field_size+7)/8; j++){
			row_ptrs[i][j] = 0;
		}
		for(uint16_t j=0; j<field_size; j++){
			row_ptrs[i][j/8] |= field[i][j] << (7-j%8);
		}
	}

	image_file = fopen(file_name_.c_str(), "wb");

	if(!image_file){
		std::cerr << "Couldn't create image file." << std::endl;

		return 1;
	}

	image_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if(!image_ptr){
		std::cerr << "Couldn't prepare png structure." << std::endl;

		fclose(image_file);

		return 1;
	}

	info_ptr = png_create_info_struct(image_ptr);

	if(!info_ptr){
		std::cerr << "Couldn't prepare infomation structure." << std::endl;

		fclose(image_file);

		return 1;
	}

	if(setjmp(png_jmpbuf(image_ptr))){
		std::cerr << "Error during init_io." << std::endl;

		png_destroy_write_struct(&image_ptr, &info_ptr);
		fclose(image_file);

		return 1;
	}

	png_init_io(image_ptr, image_file);

	if(setjmp(png_jmpbuf(image_ptr))){
		std::cerr << "Error during writing image header." << std::endl;

		png_destroy_write_struct(&image_ptr, &info_ptr);
		fclose(image_file);

		return 1;
	}

	png_set_IHDR(image_ptr, info_ptr, field_size, field_size, 1, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(image_ptr, info_ptr);

	if(setjmp(png_jmpbuf(image_ptr))){
		std::cerr << "Error during writing image." << std::endl;
	
		png_destroy_write_struct(&image_ptr, &info_ptr);
		fclose(image_file);

		return 1;
	}

	png_write_image(image_ptr, row_ptrs);

		
	if(setjmp(png_jmpbuf(image_ptr))){
		std::cerr << "Error at end of writing." << std::endl;
	
		png_destroy_write_struct(&image_ptr, &info_ptr);
		fclose(image_file);

		return 1;
	}

	png_write_end(image_ptr, NULL);

	fclose(image_file);

	return 0;
}

void LangtonAnt::finishAnt(void){
	for(uint16_t i=0; i<field_size; i++){
		delete[] field[i];
	}
	delete[] field;
}
