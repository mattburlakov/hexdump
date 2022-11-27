#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc, char** args) {
	std::ifstream stream;
	stream.open(args[1], std::ios::in | std::ios::binary);

	if (stream.is_open()) {
		std::cout << ":: File open:\n" << std::hex << std::setfill('0');

		unsigned long offset = 0;
		int totalBytes = 0;

		while (true) {
			std::cout << std::setw(8) << offset << '\t';

			char* chunk = new char[16];
			int bytes = stream.read(chunk, 16).gcount();
			totalBytes += bytes;

			for (int i = 0; i < bytes; i++) {
				if (i % 8 == 0) { std::cout << ' '; }
				std::cout << std::setw(2) << (unsigned int)(unsigned char)chunk[i] << "  ";
			}

			std::cout << ' ';
			for (int i = 0; i < bytes; i++) {
				if (chunk[i] < 32) std::cout << '.';
				else std::cout << chunk[i];
			}

			offset += 16;

			std::cout << '\n';
			delete[] chunk;

			if (bytes == 0) {
				std::cout << ":: Stream empty\n" << ":: Total bytes: " << std::dec << totalBytes << '\n';
				break;
			}
		}
	}
	else {
		std::cout << "Unable to open the file";
	}

	stream.close();
	return 0;
}