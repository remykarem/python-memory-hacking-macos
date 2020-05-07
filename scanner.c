#include <stdio.h>
#include <mach/mach.h>
#include <unistd.h>
#include "Python.h"

PyObject

int main()
{
    mach_port_t process_to_write;
    kern_return_t kernel_return;
    int pid, value;
    unsigned long int address_start, address_end;

    if (getuid() && geteuid())
    {
        printf("You need to be root!\n");
        return 1;
    }

    printf("Enter process id: ");
    scanf("%i", &pid);

    kernel_return = task_for_pid(mach_task_self(), pid, &process_to_write);
    if ((kernel_return != KERN_SUCCESS) || !MACH_PORT_VALID(process_to_write))
    {
        printf("Error getting the process\n");
        return 1;
    }

    printf("Enter start and end addresses: ");
    scanf("%lx %lx", &address_start, &address_end);

    while (address_start < address_end)
    {
        uint32_t size = 0;
        uint32_t num = 0;
        pointer_t buffer_pointer = 0;
        unsigned char buffer[1] = {0};
        // unsigned char buffer[4] = {0};

        kernel_return = vm_read(process_to_write, (vm_address_t)address_start, 1, // 1 byte
                                &buffer_pointer, &size);
        if (kernel_return == KERN_SUCCESS) {
            memcpy(buffer, (const void *)buffer_pointer, size);
        }

        address_start++;
    }

    return 0;
}