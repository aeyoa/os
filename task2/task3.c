#include <fcntl.h>
#include <unistd.h>

void write_to(char *file_input_path, int output){
	int input = open(file_input_path, O_RDONLY);
	char str;
	while(read(input, &str, 1) != 0){
		write(output, &str, 1);
	}
	close(input);
}
		
int main(int argc, char *argv[]){
	int output = open(argv[3], O_WRONLY);
	write_to(argv[1], output);
	write_to(argv[2], output);
	close(output);
}
