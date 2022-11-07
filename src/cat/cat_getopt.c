#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
	int flag = 0;
    int flags[6][2] = {
        { (int)'b', 0 },
        { (int)'e', 0 },
        { (int)'n', 0 },
        { (int)'s', 0 },
        { (int)'t', 0 },
        { (int)'v', 0 }
    };
    
	const char* short_options = "beEnstTv";

	const struct option long_options[] = {
		{ "number-nonblank", no_argument, 0, 'b' },
		{ "number", no_argument, 0, 'n'},
		{ "squeeze-blank", no_argument, 0, 's'},
		{ NULL, 0, NULL, 0}
	};

	opterr = 0;

	while ((flag = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
		switch (flag) {
		case 'b': flags[0][1] = 1; break;
		case 'e': flags[1][1] = 1; flags[5][1] = 1; break;
		case 'E': flags[1][1] = 1; break;
		case 'n': flags[2][1] = 1; break;
		case 's': flags[3][1] = 1; break;
        case 't': flags[4][1] = 1; flags[5][1] = 1; break;
        case 'T': flags[4][1] = 1; break;
        case 'v': flags[5][1] = 1; break;
        default : fprintf(stderr, "invalid option"); break; 
		}
    }

    if (optind >= argc) {
        fprintf(stderr, "no input file");
    }

    if (optind < argc) {
        do {
            char *file = argv[optind];
            // do something with file
            printf("%s\t", file);
        } while ( ++optind < argc);
    }

    return 0;
}