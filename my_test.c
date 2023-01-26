#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int s[32];
int s_v[8];
int str[32], top = -1;

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
void MULL(int x, int y)
{
    int z = s[x] * s[y];
    int i = 0;
    char k[32];
    int u = z;
    while (u != 0)
    {
        k[i] = z % 2;
        u = u / 2;
        i++;
    }
    s[y] = z & 15;
    s[x] = z >> (i - 4);
}

void DIV(int x, int y)
{
    int q, r;
    q = s[x] / s[y];
    r = s[x] % s[y];

    s[x] = q;
    s[y] = r;
}
void push(int x)
{
    if (top == 31)
    {
        printf("\nover flow condition: cant add more elements into the stack!");
    }
    else
    {
        top += 1;
        str[top] = s[x];
    }
}
void pop(int x)
{
    if (top == -1)
    {
        printf("\nunder flow condition: stack is emty cant  delete any element");
    }
    else
    {
        s[x] = str[top];
        top -= 1;
    }
}

/****************************************************************************************************************************************************************************************/
int main()
{
    char filename[25];
    char har_dastor[100];
    char buffer[100];
    char jmp[200][200], t;
    // strcpy(filename, argv[1]);
    scanf("%s", &filename);
    int x, y, z, i;
    int shomaresh_khat = 0, count = 0;
    FILE *fpointer = fopen(filename, "r");

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

            printf("%s ", har_dastor);

            if (strcmp(har_dastor, "MOV") == 0)
            {

                sscanf(buffer, "MOV S%d, %c", &x, &t);
                if (t == 'S')
                {
                    sscanf(buffer, "MOV S%d, S%d", &x, &y);

                    if (x > 31 || y > 31)
                    {
                        printf("ERROR!");
                    }
                    else
                    {

                        s[x] = s[y];
                    }
                }
                else
                {
                    sscanf(buffer, "MOV S%d, %d", &x, &y);

                    if (x > 31)
                    {
                        printf("ERROR!");
                    }
                    else
                    {

                        s[x] = y;
                    }
                }
            }
            else if (strcmp(har_dastor, "ADD") == 0)
            {
                sscanf(buffer, "ADD S%d, S%d, S%d", &x, &y, &z);

                if (x > 31 || y > 31 || z > 31)
                {
                    printf("ERROR!");
                }
                else
                {

                    bitwiseadd(x, y, z);
                }
            }

            else if (strcmp(har_dastor, "SUB") == 0)
            {
                sscanf(buffer, "SUB S%d, S%d, S%d", &x, &y, &z);

                if (x > 31 || y > 31 || z > 31)
                {
                    printf("EROR!");
                }
                else
                {

                    bitwisesub(x, y, z);
                }
            }

            else if (strcmp(har_dastor, "AND") == 0)
            {
                sscanf(buffer, "AND S%d, S%d, S%d", &x, &y, &z);
                if (x > 31 || y > 31 || z > 31)
                {
                    printf("EROR!");
                }
                else
                {
                    bitwiseand(x, y, z);
                    parityflag(s[x]);
                }
            }
            else if (strcmp(har_dastor, "XOR") == 0)
            {
                sscanf(buffer, "XOR S%d, S%d, S%d", &x, &y, &z);
                if (x > 31 || y > 31 || z > 31)
                {
                    printf("EROR!");
                }
                else
                {
                    bitwisexor(x, y, z);
                    parityflag(s[x]);
                }
            }
            else if (strcmp(har_dastor, "OR") == 0)
            {

                sscanf(buffer, "OR S%d, S%d, S%d", &x, &y, &z);
                if (x > 31 || y > 31 || z > 31)
                {
                    printf("EROR!");
                }
                else
                {
                    bitwiseor(x, y, z);
                }
            }
            else if (strcmp(har_dastor, "ADDI") == 0)
            {

                sscanf(buffer, "ADDI S%d, S%d, %d", &x, &y, &z);
                if (x > 31 || y > 31 || z > 31)
                {
                    printf("EROR!");
                }
                else
                {
                    ADDi(x, y, z);
                }
            }
            else if (strcmp(har_dastor, "SUBI") == 0)
            {
                sscanf(buffer, "SUBI S%d, S%d, %d", &x, &y, &z);
                if (x > 31 || y > 31 || z > 31)
                {
                    printf("EROR!");
                }
                else
                {
                    SUBI(x, y, z);
                }
            }
            else if (strcmp(har_dastor, "ANDI") == 0)
            {
                sscanf(buffer, "ANDI S%d, S%d, %d", &x, &y, &z);
                if (x > 31 || y > 31 || z > 31)
                {
                    printf("EROR!");
                }
                else
                {
                    ANDI(x, y, z);
                }
            }
            else if (strcmp(har_dastor, "XORI") == 0)
            {
                sscanf(buffer, "XORI S%d, S%d, %d", &x, &y, &z);
                if (x > 31 || y > 31 || z > 31)
                {
                    printf("EROR!");
                }
                else
                {

                    XORI(x, y, z);
                }
            }
            else if (strcmp(har_dastor, "ORI") == 0)
            {
                sscanf(buffer, "ORI S%d, S%d, %d", &x, &y, &z);
                if (x > 31 || y > 31 || z > 31)
                {
                    printf("EROR!");
                }
                else
                {
                    ORI(x, y, z);
                }
            }
            else if (strcmp(har_dastor, "SWP") == 0)
            {
                sscanf(buffer, "SWP S%d, S%d", &x, &y);
                if (x > 31 || y > 31)
                {
                    printf("EROR!");
                }
                else
                {
                    swp(x, y);
                }
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

            else if (strcmp(har_dastor, "JMP") == 0)
            {
                sscanf(buffer, "JMP %d", &x);
                count = x;
                fseek(fpointer, 0, SEEK_SET);
                shomaresh_khat = 0;
            }

            else if (strcmp(har_dastor, "EXIT") == 0)
            {
                break;
            }
            else if (strcmp(har_dastor, "MULL") == 0)
            {
                sscanf(buffer, "MULL S%d, S%d", &x, &y);
                if (x > 31 || y > 31)
                {
                    printf("ERROR!");
                }
                else
                {

                    MULL(x, y);
                }
            }

            else if (strcmp(har_dastor, "DIV") == 0)
            {
                sscanf(buffer, "DIV S%d, S%d", &x, &y);
                if (x > 31 || y > 31)
                {
                    printf("ERROR!");
                }
                else
                {
                    DIV(x, y);
                }
            }
            else if (strcmp(har_dastor, "SKIE") == 0)
            {
                sscanf(buffer, "SKIE S%d S%d", &x, &y);
                if (s[x] == s[y])
                {
                }
                else
                {
                    continue;
                }
            }
            else if (strcmp(har_dastor, "PUSH") == 0)
            {
                sscanf(buffer, "PUSH S%d", &x);
                if (x > 31 || y > 31)
                {
                    printf("ERROR!");
                }
                else
                {
                    push(x);
                }
            }
            else if (strcmp(har_dastor, "POP") == 0)
            {
                sscanf(buffer, "POP S%d", &x);
                if (x > 31 || y > 31)
                {
                    printf("ERROR!");
                }
                else
                {
                    pop(x);
                }
            }

            else
            {
                printf("\nYour command is incorrect!\n");
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
    printf("\n%d %d", s[1], s[0]);
}
