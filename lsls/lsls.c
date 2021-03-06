#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

/**
 * Main
 */
int main(int argc, char **argv)
{
  // no arguments provided, open current directory
  if (argc == 1)
  {
    //DIR data type represents a directory stream.
    //Use opendir to open a directory stream
    DIR *d;
    //Assign d pointer the result of opendir
    d = opendir(".");
    printf("Directory: Current\n");

    //Pointer to entry
    struct dirent *ent;

    //NULL means no more entries
    while ((ent = readdir(d)) != NULL)
    {
      // store filename in pointer
      char *filename = (*ent).d_name;
      // struct stat type pointer
      struct stat *buffer;
      // allocate size the stat struct for size pointer
      buffer = malloc(sizeof(struct stat));
      // obtain info of the filename
      stat(filename, buffer);
      // store size of buffer
      int bytes = (*buffer).st_size;
      // check if file or directory
      if (((*buffer).st_mode & S_IFDIR) == 0) printf("%5d  %s\n", bytes, filename);
      else printf("<DIR>  %s\n", filename);
      free(buffer);
    }
    printf("\n");
    closedir(d);
  }
  //otherwise print all directories input on command line
  else
  {
    for (int i = 1; i < argc; i++)
    {
      DIR *d;
      d = opendir(argv[i]);
      if (d == NULL) {
        printf("Error Opening Directory %s\nExiting Program\n", argv[i]);
        exit(0);
      }
      printf("Directory: %s\n", argv[i]);

      struct dirent *ent;
      while ((ent = readdir(d)) != NULL)
      {
        char *filename = (*ent).d_name;
        struct stat *buffer;
        buffer = malloc(sizeof(struct stat));
        stat(filename, buffer);
        int bytes = (*buffer).st_size;
        if (((*buffer).st_mode & S_IFDIR) == 0) printf("%5d  %s\n", bytes, filename);
        else printf("<DIR>  %s\n", filename);
        free(buffer);
      }
      printf("\n");
      closedir(d);
    }
  }
    return 0;
}