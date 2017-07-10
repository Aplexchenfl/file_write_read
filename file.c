#include <stdio.h>
#include <errno.h>
#include <string.h>

struct student
{
    int num;
    char name[8];
    int age;
    int score;
};

#define SAVE_FILE  "stu.file"
#define STU_MAX  50
struct student stu[STU_MAX];
int exit_flag = 0;

void show_stu(void)
{
    int i = 0;
    for (i = 0; i < 50; i++)
    {
        printf(" student num : %d    name : %s   age : %d  score : %d\n", stu[i].num, stu[i].name, stu[i].age, stu[i].score);
    }
}

void init_stu(void)
{
    int tmp_num = -1;

    printf("Please input student number, 10 - 50:");

    while(tmp_num < 0 || tmp_num >= 50)
        scanf("%d", &tmp_num);

    printf("\nPlease input student name :");
    scanf("%s", stu[tmp_num].name);

    printf("\nPlease input student age  :");
    scanf("%d", &stu[tmp_num].age);

    printf("\nPlease input student score  :");
    scanf("%d", &stu[tmp_num].score);
}

void stu_input_while(void)
{
    char flag = 'y';
    while( flag == 'y' || flag == 'Y')
    {
        init_stu();
        printf("continue or break : y/n: ");
        scanf("%c", &flag);
    }
}

int save_stu_score()
{
    FILE *stu_file;
    int retval, i = 0;

    stu_file = fopen(SAVE_FILE, "a+");
    if (stu_file == NULL)
    {
        perror("stu_file");
        return -1;
    }

    fseek(stu_file, 0, SEEK_SET);

    for (i = 0; i < 50; i++)
    {
        if (stu[i].num == 0)
            strcpy(stu[i].name, "stu");

        fprintf(stu_file, "%4d%10s%4d%4d\n", stu[i].num, stu[i].name, stu[i].age, stu[i].score);
    }

    fclose(stu_file);

    return 0;
}

int load_stu_score()
{
    FILE *stu_file;
    int retval, i;

    stu_file = fopen(SAVE_FILE, "a+");
    if (stu_file == NULL)
    {
        perror("stu_file");
        return -1;
    }

    fseek(stu_file, 0, SEEK_SET);

    for (i = 0; i < 50; i++)
    {
        fscanf(stu_file, "%4d%10s%4d%4d", &stu[i].num, stu[i].name, &stu[i].age, &stu[i].score);
    }

    fclose(stu_file);

    return 0;
}

void show_interface(void)
{
    printf("                please choose :\n");
    printf("                1.  Add     student score \n");
    printf("                2.  Load    student score \n");
    printf("                3.  Save    student score \n");
    printf("                4.  Show    student score \n");
    printf("                5.  Change  student score \n");
    printf("                6.  exit \n");
}

int main(void)
{
    unsigned int choose_flag;

    while(!exit_flag)
    {
        show_interface();

        printf("Input you choose:");
        scanf("%d", &choose_flag);

        switch(choose_flag)
        {
        case 1:
            stu_input_while();
            break;
        case 2:
            load_stu_score();
            break;
        case 3:
            save_stu_score();
            break;
        case 4:
            show_stu();
            break;
        case 5:
            break;
        case 6:
            return 0;
            break;
        default:
            break;
        }
    }

    return 0;
}
