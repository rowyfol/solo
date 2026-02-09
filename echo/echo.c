#include <stdio.h>
#include <string.h>

static char *set_arg = "";

int main(int argc, char *argv[])
{

    for (int i = 0; i < argc; i++)
    {
            if (strcmp(argv[i], "-n") == 0)
            {
                    set_arg = "-n";
            }
            if (strcmp(argv[i], "-e") == 0)
            {
                    set_arg = "-e";
            }
            if (strcmp(argv[i], "-E") == 0)
            {
                    set_arg = "-E";
            }

            if (i == argc-1)
            {
                    if (strcmp(set_arg, "-n") == 0)
                    {
                        continue;
                    } else if (strcmp(set_arg, "-e") == 0) {
                        continue;
                    } else if (strcmp(set_arg, "-E") == 0) {
                        continue;
                    } else {
                        set_arg = "none";
                    }
            }
    }

    printf("%s \n", set_arg);

    return 0;
}
