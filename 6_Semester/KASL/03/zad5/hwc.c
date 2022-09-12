#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

static struct option long_options[] = {
		{ "capitalize", no_argument, 				NULL, 'c' },
		{ "greeting", 	required_argument,	NULL, 'g' },
		{ "color", 			required_argument, 	NULL, 'd' },
		{ "world", 			no_argument, 				NULL, 'w' },
		{ "version", 		no_argument, 				NULL, 'v' },
		{ "help", 			no_argument, 				NULL, 'h' },
};

char *greeting = "Hello,";
char *color = "auto";
int capitalize = false;
int world = 0;

static const char version_string[] = "Version 0.1337\n\
2022 Artur Jankowski";

static const char help_string[] = "hwb - the ultimate greeter\n\
\n\
Usage: hwb [OPTIONS] {ARGS...}\n\
Where ARGS are people to greet\n\
\n\
Options:\n\
-c --capitalize         = capitalize the string\n\
-g text --greeting=text = the first part of the greeting\n\
-h --help               = prints help (this message)\n\
-v --version            = current version and license\n\
-w --world              = prints an additional line with 'world' argument\n\
--color=[always|auto|never] (default auto)  = colorize the output\n\
\n\
Example usage:\n\
./hwb --color=never artur sample\n\
./hwb -w --greeting='HI' -c artur dawid";

void print_greet(char *name) {
	if (capitalize)
		name[0] = toupper(name[0]);

	printf("%s ", greeting);

	if (!strcmp(color, "always")) {
    printf("\033[0;33m%s\n",  name);
    printf("\033[0m");
  }
  else if (!strcmp(color, "auto") && isatty(1)) {
    printf("\033[0;33m%s\n", name);
    printf("\033[0m");
  }
  else 
	  printf("%s\n", name);
}

int main(int argc, char *argv[]) {
  int opt = 0;
  int option_index = 0;

	while ((opt = getopt_long(argc, argv, "cg:wvh", long_options, &option_index)) >= 0) {
		switch (opt) {
			case 'c': capitalize = 1; break;
			case 'h': printf("%s\n", help_string); break;
			case 'g': greeting = optarg; break;
			case 'd': 
				if(!strcmp(optarg, "never") || !strcmp(optarg, "auto") || !strcmp(optarg, "always"))
					color = optarg; 
				break;
			case 'w': world = 1; break;
			case 'v': printf("%s\n", version_string); return 0;
			default:  printf("%s", optarg); return 0;
		}
	}

	while (optind < argc) 
		print_greet(argv[optind++]);

	char *name = "world";
	if (world)
		print_greet(name);

	return 0;
}
