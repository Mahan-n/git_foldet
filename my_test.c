#include <stdio.h>
#include <string.h>
#include <ctype.h>

int s[32];
int s_v[8];

void bitwiseadd(int x, int y, int z)
{
    s[x] = s[y] + s[z];
}
void bitwisesub(int x, int y, int z)
{

    s[x] = s[y] - s[z];
}
void bitwiseand(int x, int y, int z)
{
    s[x] = s[y] & s[z];
}

void bitwisexor(int x, int y, int z)
{
    s[x] = s[y] ^ s[z];
}
void bitwiseor(int x, int y, int z)
{
    s[x] = s[y] | s[z];
}
void ADDi(int x, int y, int z)
{
    s[x] = s[y] + z;
}
void SUBI(int x, int y, int z)
{

    s[x] = s[y] - z;
}
void ANDI(int x, int y, int z)
{
    s[x] = s[y] & z;
}

void XORI(int x, int y, int z)
{
    s[x] = s[y] ^ z;
}
void ORI(int x, int y, int z)
{
    s[x] += s[y] | z;
}
void swp(int x, int y)
{
    int temp = s[x];
    s[x] = s[y];
    s[y] = temp;
}
int dump_regs()
{
    for (int i = 0; i < 32; i++)
    {
        if (i == 0)
        {
            printf("\n");
            printf("omomi:");
        }
        printf("%d: %d ", i, s[i]);
        if (i == 31)
        {
            printf("\n");
            printf("vaziat:");
        }
    }
    for (int i = 0; i < 8; i++)
    {
        printf("%d: %d ", i, s_v[i]);
    }
}
void dump_regs_f()
{
    FILE *fptr = fopen("C:\\Users\\Asus\\Desktop\\regs.txt", "w");
    for (int i = 0; i < 32; i++)
    {
        if (i == 0)
        {
            printf("\n");
            printf("omomi:");
        }
        printf("%d: %d ", i, s[i]);
        if (i == 31)
        {
            fprintf(fptr, "\n");
            fprintf(fptr, "vaziat:");
        }
    }
    for (int i = 0; i < 8; i++)
    {
        fprintf(fptr, "%d: %d ", i, s_v[i]);
    }

    fclose(fptr);
}
void input()
{
    int c;
    scanf("%d", &c);
    s[0] = c;
}
void output()
{
    printf("\narray asli aval: %d", s[0]);
}
void MOV(int x, int y)
{
}
void parityflag(int x)
{
    int count = 0;
    while (x > 0)
    {
        count += 1;
        x = x & (x - 1);
    }
    if (count % 2 == 0)
    {
        s_v[0] = 0;
    }
    else
    {
        s_v[0] = 1;
    }
}
void zeroflag(int x)
{
    if (x == 0)
    {
        s_v[1] = 1;
    }
    else if (x != 0)
    {
        s_v[1] = 0;
    }
}
void signflag(int x)
{
    if (x < 0)
    {
        s_v[2] = 1;
    }
    else
    {
        s_v[2] = 0;
    }
}
void overflowflag(int x)
{
}
void overflow(int x, int y, int z)
{
    if (y > 0 && z > 0 && x < 0)
    {
        s_v[5] = 1;
    }
    else if (y < 0 && z < 0 && x > 0)
    {
        s_v[5] = 1;
    }
    else
    {
        s_v[5] = 0;
    }
}

/****************************************************************************************************************************************************************************************/
int main()
{
    char har_dastor[100];
    char buffer[100];
    char jmp[200][200], t;

    int x, y, z, i;
    int shomaresh_khat = 0, count = 0;
    FILE *fpointer = fopen("C:\\Users\\Asus\\Desktop\\in.txt", "r");

    while (fscanf(fpointer, "%[^\n]\n", buffer) != EOF)

    {
        for (int i = 0; i < 100; i++)
        {
            buffer[i] = toupper(buffer[i]);
        }
        shomaresh_khat++;

        if (shomaresh_khat >= count)
        {

            if (buffer[0] == 'D' && buffer[10] == 'F')
            {
                buffer[11] = ' ';
            }
            else if (buffer[0] == 'D' && buffer[8] == 'S')
            {
                buffer[9] = ' ';
            }
            else if (buffer[0] == 'O' && buffer[5] == 'T')
            {
                buffer[6] = ' ';
            }
            else if (buffer[0] == 'I' && buffer[4] == 'T')
            {
                buffer[5] = ' ';
            }
            else if (buffer[0] == 'E' && buffer[3] == 'T')
            {
                buffer[4] = ' ';
            }
            if (buffer[0] == '/')
            {
                continue;
            }

            for (int i = 0; buffer[i] != ' '; i++)
            {
                har_dastor[i] = buffer[i];
            }

            if (strcmp(har_dastor, "MOV") == 0)
            {
                sscanf(buffer, "MOV S%d, %c", &x, &t);
                if (t == 'S')
                {
                    sscanf(buffer, "MOV S%d, S%d", &x, &y);
                    s[x] = s[y];
                }
                else
                {
                    sscanf(buffer, "MOV S%d, %d", &x, &y);
                    s[x] = y;
                }
            }
            else if (strcmp(har_dastor, "ADD") == 0)
            {
                sscanf(buffer, "ADD S%d, S%d, S%d", &x, &y, &z);
                bitwiseadd(x, y, z);
            }

            else if (strcmp(har_dastor, "SUB") == 0)
            {

                sscanf(buffer, "SUB S%d, S%d, S%d", &x, &y, &z);
                bitwisesub(x, y, z);
            }

            else if (strcmp(har_dastor, "AND") == 0)
            {
                sscanf(buffer, "AND S%d, S%d, S%d", &x, &y, &z);
                bitwiseand(x, y, z);
                parityflag(s[x]);
            }
            else if (strcmp(har_dastor, "XOR") == 0)
            {
                sscanf(buffer, "XOR S%d, S%d, S%d", &x, &y, &z);
                bitwisexor(x, y, z);
                parityflag(s[x]);
            }
            else if (strcmp(har_dastor, "OR") == 0)
            {

                sscanf(buffer, "OR S%d, S%d, S%d", &x, &y, &z);
                bitwiseor(x, y, z);
            }
            else if (strcmp(har_dastor, "ADDI") == 0)
            {

                sscanf(buffer, "ADDI S%d, S%d, %d", &x, &y, &z);
                ADDi(x, y, z);
            }
            else if (strcmp(har_dastor, "SUBI") == 0)
            {
                sscanf(buffer, "SUBI S%d, S%d, %d", &x, &y, &z);
                SUBI(x, y, z);
            }
            else if (strcmp(har_dastor, "ANDI") == 0)
            {
                sscanf(buffer, "ANDI S%d, S%d, %d", &x, &y, &z);
                ANDI(x, y, z);
            }
            else if (strcmp(har_dastor, "XORI") == 0)
            {
                sscanf(buffer, "XORI S%d, S%d, %d", &x, &y, &z);
                XORI(x, y, z);
            }
            else if (strcmp(har_dastor, "ORI") == 0)
            {
                sscanf(buffer, "ORI S%d, S%d, %d", &x, &y, &z);
                ORI(x, y, z);
            }
            else if (strcmp(har_dastor, "SWP") == 0)
            {
                sscanf(buffer, "SWP S%d, S%d", &x, &y);
                swp(x, y);
            }
            else if (strcmp(har_dastor, "DUMP_REGS") == 0)
            {
                dump_regs();
            }
            else if (strcmp(har_dastor, "DUMP_REGS_F") == 0)
            {
                dump_regs_f();
            }
            else if (strcmp(har_dastor, "INPUT") == 0)
            {
                input();
            }
            else if (strcmp(har_dastor, "OUTPUT") == 0)
            {
                output();
            }
            /************************************************************************************************************************************/
            else if (strcmp(har_dastor, "JMP") == 0)
            {
                sscanf(buffer, "JMP %d", &x);
                count = x;
                fseek(fpointer, 0, SEEK_SET);
                shomaresh_khat = 0;
            }
            /************************************************************************************************************************************/
            else if (strcmp(har_dastor, "EXIT") == 0)
            {
                break;
            }
            else
            {
                printf("\nYou command is incorrect!\n");
            }
            for (i = 0; i < 100; i++)
            {
                buffer[i] = '\0';
                har_dastor[i] = '\0';
            }
            parityflag(s[x]);
            zeroflag(s[x]);
            signflag(s[x]);
            overflow(s[x], s[y], s[z]);
        }
    }
    // printf("hello world");
    printf("\n%d %d %d %d %d %d %d %d %d %d %d %d", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9], s[10], s[11]);
}
