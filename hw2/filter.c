#include <stdio.h>

int main() {
        char line[1024];
        while (fgets(line, sizeof(line), stdin)) {
                printf("record.out> %s", line);
        }
        return 0;
}
