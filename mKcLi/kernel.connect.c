#include "shell.emergancy.c"
void write(char *data) {
    // 1. Point to the Log Slab
  FILE *log_file = fopen("/IMPO/SHELL/0.txt", "a");

  if (log_file == NULL) {
    print_string("[ERROR] CANNOT FIND LOG . SKIPPING LOGGING");
    SHELL.exu();
 }

  // 2. Iron-Melt the data into the file
  fprintf(log_file, "[LOG] %s\n", data);

  // 3. Seal the Steel Container
  fclose(log_file);
  
  print_string("[OK] DATA WRITTEN");
}
  // 3. Seal the Steel Container
  fclose(log_file);
  
  print_string("[OK] DATA SEALED IN SD");
}
