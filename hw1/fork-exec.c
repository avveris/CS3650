#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// You must fill in wherever it says 'HOMEWORK'.
void help();
int read_command(char *program);
// In C, a string is of type 'char []' or equivalently, 'char *'
int main(int argc, char *argv[]) {
  help();
  while (1) { // This is a "read-exec-print" loop.
    printf("%% "); // print prompt
    fflush(stdout); // Don't wait for 'newline'.  Flush stdout to screen now.
    int cmd;
    while (1) {
      cmd = read_command(argv[0]);
      if (cmd == '\n') { continue; } // Ignore newlines
      if (cmd == '#') {
        char c;
        while ((c = read_command(argv[0])) !='\n');
        continue;
      }
      break;
    }
    // The syntax "1" is an int and "'1'" is a char.
    switch (cmd) {
      case 'h':
        help();
        break; // Don't forget 'break'.  Otherwise control passes to next case.
      case 'x':
      case 'q':
        printf("Exiting\n");
        exit(0); // The argument 0 of exit says return code is 0:  success.
      case '1': {
              int childpid = fork();
              if(childpid ==0) {
                      char*args[] = {"ls", NULL};
                      execvp("ls", args);
                      exit(1);
              } else {
                      sleep(2);
                      printf("ls should have just been executed");
              }
              break;
      }
      case '2': {
              int childpid = fork();
              if (childpid == 0) {
                      char *args[] = {"ls", "-l", NULL};
                      execvp("ls", args);
                      exit(1);
              } else {
                      sleep(2);
                      printf("-ls -l should have now executed");
              }
              break;
      }
      case '3': {
                char dir[256];
                fflush(stdout);
                char c;
                int i = 0;
                while (read(0, &c, 1) == 1 && c != '\n') dir[i++] = c;
                dir [i] = '\0';
                fflush(stdout);
                chdir(dir);
                fflush(stdout);
                sleep(2);
                printf("cd should have been executed");
                break;
                }
      case '4': {
                char var[256];
                int i = 0;
                char c;
                do {
                        if (read(0, &c, 1) != 1) break;
                } while (c == ' ' || c == '\t');
                    // First non-whitespace character
                 if (c != '\n') var[i++] = c;
    // Rest of the variable name
                 while (read(0, &c, 1) == 1 && c != '\n') var[i++] = c;
                var[i] = '\0';
                char *value = getenv(var);
                if (value) {
                printf("%s\n", value);
                 }
                sleep(2);
               sleep(2);
                printf("get env should have just been executed");
                break;
                }
      case '5' : {
                char var [256], value[256];
                char c;
                int i = 0;
                while (read(0, &c, 1) == 1 && c != '\n') var[i++] = c;
                var[i] = '\0';
                i = 0;
                while (read(0, &c, 1) == 1 && c != '\n') value[i++] = c;
                value[i] = '\0';
                setenv(var, value, 1);
                sleep(2);
                printf("set env should have been executed");
                break;
                 }
      case '6': {
                    char src[256], dest[256];
                    char c;
                    int i = 0;
                    while (read(0, &c, 1) == 1 && c != '\n') src[i++] = c;
                    src[i] = '\0';
                    i = 0;
                    while (read(0, &c, 1) == 1 && c != '\n') dest[i++] = c;
                    dest[i] = '\0';
                    int childpid = fork();
                    if (childpid == 0) {
                            char *args[] = {"cp", src, dest, NULL};
                            execvp("cp", args);
                            exit(1);
                    } else {
                            sleep(2);
                    }
                    printf("cp should have been executed");
                    break;
                }
      case '7': {
                char dir[256];
                char c;
                int i = 0;
                while(read(0, &c, 1) == 1 && c != '\n') dir[i++] = c;
                dir[i] = '\0';
                int childpid = fork();
                if (childpid == 0) {
                        char *args[] = {"mkdir", dir, NULL};
                        execvp("mkdir", args);
                        exit(1);
                } else {
                        sleep(2);
                        printf("mkdir should have been executed");
                }
                break;
                }
      case '8' : {
                char file[256];
                char c;
                int i =0;
                while(read(0, &c, 1) == 1 && c != '\n') file[i++] = c;
                file[i] = '\0';
                int childpid = fork();
                if (childpid == 0) {
                        char *args[] = {"rm", file, NULL};
                        execvp("rm", args);
                        exit(1);
                } else {
                        sleep(2);
                        printf("rm should have just been executed on a file");
                }
                break;
                }
        case '9': {
              char dir[256];
              char c;
              int i=0;
              while(read(0, &c, 1) == 1 && c != '\n') dir[i++] = c;
              dir[i] = '\0';
              int childpid = fork();
              if (childpid ==0) {
                      char *args[] = {"rmdir", dir, NULL};
                      execvp("rmdir", args);
                      exit(1);
              } else {
                      sleep(2);
                      printf("rm should have just been executed on a directory");
              }
              break;
                                                                          
     }
      default:
        printf("Unrecognized command: %c\n", (char)cmd);
        char c;
        while(read(0, &c, 1) == 1 && c != '\n');
        break;
    }
  }
  return 0;  // When the process exits, this is its return code. 0 is success.
}
void help() {
        printf("command list:\n");
        printf(" 1: (l)ist file(s) -- (ls)\n");
        printf(" 2: (l)ist all file(s) detai(l)s --(ls -l)\n");
        printf(" 3: (c)hange (d)irectory --(cd)\n");
        printf(" 4: (p)rint (w)orking (d)irectory --(pwd)\n");
        printf(" 5: set a variable in environment --(=)\n");
        printf(" 6: (c)o(p)y file --(cp)\n");
        printf(" 7: (m)a(k)e (dir)ectory --(mkdir)\n");
        printf(" 8: (r)e(m)ove file -- (rm)\n");
        printf(" 9: (r)e(m)ove (dir)ectory -- (rmdir)\n");
}
int read_command(char *program) {
  char buf[1];
  while (1) {
    int rc;
    rc = read(0, buf, 1);  // fd is 0 (stdin); read just 1 character into buf.
    if (rc == 1) { // If 1 char was read
      break;
    } else if (rc == -1) { // If error
      if (rc == EAGAIN || rc == EINTR) {
        continue;  // The O/S kernel wasn't ready.  Ask it again.
      } else {
        fprintf(stderr, "%s: Error in reading command\n", program);
        exit(1);  // Error:  Set return code to error number 1
      }
    } else if (rc == 0) {
      printf("%s: End-of-input\n", program);
      exit(0);
    }
  }
  int cmd = buf[0];  // Convert 'char' to an 'int'.
  return cmd;
}
                                      
