#define FILENAME "BasicStrategy.csv"

#import <iostream>
#import <fstream>
#import <ctype.h>

int main(){
	std::ifstream file(FILENAME);
	char c;
	while (file.get(c)) {
		if (isdigit(c)) std::cout << c << std::endl;
	}
	file.close();

	return 0;
}
