#include <sys/file.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>


void usage();

int main(int argc, char* argv[]) {
	if(argc != 3) {
		usage();
		return 1;
	}

	// Get the source and destination filenames and their lengths
	char* src_fn = argv[1];
	char* dest_fn = argv[2];
	int src_fn_len = strlen(src_fn);
	int dest_fn_len = strlen(dest_fn);

	// Attempt to open the source file
	int src_fd = open(src_fn, O_RDONLY, 00644);
	if(src_fd == -1) {
		write(1, "Error opening source file\n", 26);
		return 1;
	}

	// Get the filesize
	struct stat st;
	fstat(src_fd, &st);
	long src_fs = st.st_size;

	// Load the source file into memory
	char* src_fb = malloc(src_fs);
	read(src_fd, src_fb, src_fs);
	close(src_fd);

	// Allocate a buffer for the destination file
	char* dest_fb = malloc(src_fs);
	
	// Store the amount of characters to be written to the destination file
	long dest_fs = src_fs;
	long dest_i = 0;

	// Loop over every character in the source file
	for(long i = 0; i < src_fs; i++) {
		if(src_fb[i] == '\n') {
			// Skip this character
			dest_fs--;
		} else {
			// Write the current character to the destination buffer
			dest_fb[dest_i] = src_fb[i];
			dest_i++;
		}
	}

	// Write the destination filebuffer to the destination file
	int dest_fd = open(dest_fn, O_WRONLY | O_CREAT, 00644);
	if(dest_fd == -1) {
		write(1, "Error opening destination file\n", 31);
		return 1;
	}

	write(dest_fd, dest_fb, dest_fs);
	close(dest_fd);

	return 0;
}

void usage() {
	char* usage_text = "\nusage: rnl [source] [destination]\n";
	write(1, usage_text, 35);
}

