#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include <stdlib.h>


int main( int argc, char *argv[] )  {

    openlog(NULL,0,LOG_USER);

    char *FILE_P;
    char *STR;

    int status = 0;

   if( argc == 3 ) {
    FILE_P = argv[1];
    STR = argv[2];
   }
   else if( argc > 2 ) {
      syslog(LOG_ERR, "Too many arguments supplied %d", argc);
      return 1;
   }
   else {
      syslog(LOG_ERR, "Less arguments %d", argc);
      return 1;
   }

   syslog(LOG_DEBUG, "Writing %s to file %s\n", STR, FILE_P);
    
    FILE *file = fopen(FILE_P, "w");
    int rc = fwrite(STR, 1, strlen(STR), file);

    if (rc <= 0)
    {
        syslog(LOG_ERR, "Error writing file\n");
        status = 1;
    }
    fclose(file);

    return status;
}