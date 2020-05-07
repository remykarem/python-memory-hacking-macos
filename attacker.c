#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mach/mach.h>

int hehe(int pid)
{
    mach_port_t process_to_write;
    kern_return_t kernel_return;
    int value;
    unsigned long int address;

    if (getuid() && geteuid())
    {
        printf("You need to be root!\n");
        return 1;
    }

    // printf("Enter process id: ");
    // scanf("%i", &pid);

    kernel_return = task_for_pid(mach_task_self(), pid, &process_to_write);
    if ((kernel_return != KERN_SUCCESS) || !MACH_PORT_VALID(process_to_write))
    {
        printf("Error getting the process\n");
        return 1;
    }

    while (1)
    {
        printf("Enter address (-1 to quit): ");
        scanf("%lx", &address);

        if (address == -1)
            return 1;

        uint32_t size = 0;
        uint32_t num = 0;
        pointer_t buffer_pointer = 0;
        unsigned char buffer[64] = {0};
        // unsigned char buffer[4] = {0};

        kernel_return = vm_read(process_to_write, (vm_address_t)address, 64, // 64 bytes
                                &buffer_pointer, &size);
        if (kernel_return == KERN_SUCCESS)
        {
            memcpy(buffer, (const void *)buffer_pointer, size);
            for (int i = 0; i < 64; i++) {
                if (i % 8 == 0)
                    printf("-----------------\n");
                printf("0x%lx: %x\n", address + i, buffer[i]);
            }
            printf("\n");
            // memcpy(&num, buffer, sizeof(uint32_t));
            // printf("%d\n", num);
        }
        else
            return 1;

        // int c;
        // printf("Change value? [y/n] ");
        // scanf("%d", &c);
        // printf("%c", c);

        printf("Enter value to change at 0x%lx (-1 to skip): ", address);
        scanf("%d", &value);

        if (value != -1)
        {
            kernel_return = vm_write(process_to_write, (vm_address_t)address,
                                     (vm_address_t)&value, sizeof(value));
            if (kernel_return == KERN_SUCCESS)
                printf("Hehe.\n");
            else
                printf("Cannot write. Error %d\n", (int)kernel_return);
        }
    }

    return 0;
}
