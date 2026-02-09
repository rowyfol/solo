#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static char *set_arg = "";
static int  ignore_element = 0;
static bool ignore_element_active = false;

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
            if (strcmp(argv[i], "-n") == 0)
            {
                    set_arg = "-n";
                    ignore_element = i;
                    ignore_element_active = true;
            }
            if (strcmp(argv[i], "-e") == 0)
            {
                    set_arg = "-e";
                    ignore_element = i;
                    ignore_element_active = true;
            }
            if (strcmp(argv[i], "-E") == 0)
            {
                    set_arg = "-E";
                    ignore_element = i;
                    ignore_element_active = true;
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

    char *complete = "";
    bool set_flag = false;

    for (int cou = 0; cou < argc; cou++)
    {
        if (cou == 0)
        {
            continue;
        }
        if (ignore_element_active == true)
        {
            if (cou == ignore_element)
            {
                continue;
            }
        }

        if (strcmp(set_arg, "-n") == 0)
        {        
            if (cou == argc)
            {
                break;
            }

            printf("%s ", argv[cou]);
        }
        if (strcmp(set_arg, "-e") == 0)
        {

            if (set_flag == true) {
                strcat(complete, argv[cou]);
                set_flag = false;
            } else if (strcmp(argv[cou], "\\") == 0) {
                complete = "\\";
                set_flag = true;
            } else if (strcmp(complete, "\\n") == 0)
            {
                printf("\n");
                complete = "";
            } else if (strcmp(argv[cou], "\\t") == 0) {
                printf("\t");
                complete = "";
            } else {
                printf("%s", argv[cou]);
            }
        }
        if (strcmp(set_arg, "-E") == 0)
        {
            if (cou == argc)
            {
                printf("\n");
            }

            printf("%s ", argv[cou]);
        }
        if (strcmp(set_arg, "none") == 0)
        {
            continue;
        }
    }

    return 0;
}
