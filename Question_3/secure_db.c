#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[20];
    float salary;
} Employee;

int main(void) {
    // Open file using low-level POSIX I/O with strict 0600 permissions (user read/write only)
    int fd = open("database.dat", O_CREAT | O_RDWR | O_TRUNC, 0600);
    if (fd < 0) {
        perror("Failed to open database file");
        return EXIT_FAILURE;
    }

    // Populate and write initial binary structures
    Employee emp1 = {1, "Alice", 50000.0f};
    Employee emp2 = {2, "Bob", 60000.0f};

    write(fd, &emp1, sizeof(Employee));
    write(fd, &emp2, sizeof(Employee));
    printf("Initial records written to database.\n");

    // Random access seek to target Record 2 offset
    off_t offset = sizeof(Employee) * 1;
    if (lseek(fd, offset, SEEK_SET) == (off_t)-1) {
        perror("lseek failed");
        close(fd);
        return EXIT_FAILURE;
    }

    // Update Record 2 in-place
    Employee emp2_update = {2, "Bob", 65000.0f};
    write(fd, &emp2_update, sizeof(Employee));
    printf("Record 2 successfully updated in-place.\n");

    // Seek back to start and read back Record 1 to verify
    lseek(fd, 0, SEEK_SET);
    Employee read_emp;
    read(fd, &read_emp, sizeof(Employee));
    printf("Retrieved Record 1: ID=%d, Name=%s, Salary=%.2f\n", 
            read_emp.id, read_emp.name, read_emp.salary);

    close(fd);
    return EXIT_SUCCESS;
}