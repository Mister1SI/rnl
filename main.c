#include <sys/file.h>
#include <sys/types.h>



int main(int argc, char* argv[]) {
	if(argc != 3) {
		usage();
		return 1;
	}

	

	return 0;
}

void usage() {
	char* usage_text = "\nusage: rnl [source] [destination]\n";
	write(1, usage_text, 35);
}

