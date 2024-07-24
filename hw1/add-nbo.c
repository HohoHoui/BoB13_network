#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;

    uint8_t buffer[4];

    if(argc != 3){
        fprintf(stderr, "how to use : %s file1 file2\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "rb");
    if (fp1 == NULL) {
        printf("Error opening file : %s", argv[1]);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, 4, fp1);
    if (bytesRead != 4) {
        printf("Error reading file : %s", argv[1]);
        fclose(fp1);
        return 1;
    }

    uint32_t fb1_value = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
    fclose(fp1);

    fp2 = fopen(argv[2], "rb");
    if (fp2 == NULL) {
        printf("Error opening file : %s", argv[2]);
        return 1;
    }
   
    bytesRead = fread(buffer, 1, 4, fp2);
    if (bytesRead != 4) {
        printf("Error reading file : %s", argv[2]);
        fclose(fp2);
        return 1;
    }
    uint32_t fb2_value = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
    fclose(fp2);

    printf("fb1 : %u (0x%04x)\n", fb1_value, fb1_value);
    printf("fb2 : %u (0x%04x)\n", fb2_value, fb2_value);
    
    uint32_t sum = fb1_value + fb2_value;
    printf("sum : %u (0x%04x)\n", sum, sum);
    return 0;
}