#include <stdio.h>

struct batsman
{
    char name[25];
    int runs, score, balls, toruns, tobal, ones, twos, threes, fours, sixes;
    int max_six, max_run, max_four;
    float str;
} pl1[100], pl3;
struct bowler
{
    char name[25];
    int runsgv, wkttkn, overs;
    int max_x;
    float econ;
} pl2[100], pl4;
int main()
{
    int dat,mo,ye;
    int plno, choice;
    int i, n, m, a;
    char nam[25];
    printf("Enter the date of match in DD/MM/YYYY\n");
    scanf("%d",&dat);
    scanf("%d",&mo);
    scanf("%d",&ye);

    printf("Enter the Batsman details:\n");
    printf("Enter the number of batsmen:\n");
    scanf("%d", &m);
    FILE *batsmenFile = fopen("batsmen.txt", "w");
    if (batsmenFile == NULL)
    {
        printf("Error opening batsmen file!\n");
        return 1;
    }
    for (i = 0; i < m; i++)
    {
        printf("Enter the name of batsman%d :\n", i + 1);
        scanf("%s", &nam);
        fprintf(batsmenFile, "%s ", nam);
        printf("Enter the number of ones scored by player%d:\n", i + 1);
        scanf("%d", &a);
        fprintf(batsmenFile, "%d ", a);

        printf("Enter the number of twos scored by player%d:\n", i + 1);
        scanf("%d", &a);
        fprintf(batsmenFile, "%d ", a);

        printf("Enter the number of threes scored by player%d:\n", i + 1);
        scanf("%d", &a);
        fprintf(batsmenFile, "%d ", a);

        printf("Enter the number of fours scored by player%d:\n", i + 1);
        scanf("%d", &a);
        fprintf(batsmenFile, "%d ", a);

        printf("Enter the number of sixes scored by player%d:\n", i + 1);
        scanf("%d", &a);
        fprintf(batsmenFile, "%d ", a);

        printf("Enter the balls played by player%d:\n", i + 1);
        scanf("%d", &a);
        fprintf(batsmenFile, "%d\n", a);
    }
    fclose(batsmenFile);
    FILE *bowlersFile = fopen("bowlers.txt", "w");
    if (bowlersFile == NULL)
    {
        printf("Error opening bowlers file!\n");
        return 1;
    }
    printf("Enter the Bowler details:\n");
    printf("Enter the number of bowlers:\n");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter the name of bowler%d:", i + 1);
        scanf("%s", &nam);
        fprintf(bowlersFile, "%s ", nam);
        printf("Enter the runs given by bowler%d:", i + 1);
        scanf("%d", &a);
        fprintf(bowlersFile, "%d ", a);
        printf("Enter the overs bowled by bowler%d:", i + 1);
        scanf("%d", &a);
        fprintf(bowlersFile, "%d ", a);
        printf("Enter the wickets taken by bowler%d:", i + 1);
        scanf("%d", &a);
        fprintf(bowlersFile, "%d\n", a);
    }
    fclose(bowlersFile);
    printf("Thank You! All the details are recorded :) \n");
    do
    {
        printf("Enter the choice:\n 1)Batsman details:\n 2)Bowlers detail:\n 3)Match Summary:\n 4)Record:\n 5)Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the batsman number to see his details\n");
            scanf("%d", &plno);
            plno--;
            printf("DATE = %d/%d/%d \n",dat,mo,ye);
            printf("          Player Detail\n");
            printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
            printf("Batsman         Runs         Balls         Fours         Sixes         SR       \n");
            printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
            batsmenFile = fopen("batsmen.txt", "r");
            if (batsmenFile == NULL)
            {
                printf("Error opening the Batsmen File.\n Please try again later!\n");
                break;
            }
            for (i = 0; i < plno; i++)
            {
                fscanf(batsmenFile, "%s %d %d %d %d %d %d", pl1[i].name, &pl1[i].ones, &pl1[i].twos, &pl1[i].threes, &pl1[i].fours, &pl1[i].sixes, &pl1[i].balls);
            }
            fscanf(batsmenFile, "%s %d %d %d %d %d %d %d %f", pl1[plno].name, &pl1[plno].ones, &pl1[plno].twos, &pl1[plno].threes, &pl1[plno].fours, &pl1[plno].sixes, &pl1[plno].balls, &pl1[plno].runs, &pl1[plno].str);
            pl1[plno].runs = (pl1[plno].ones) + (2 * pl1[plno].twos) + (3 * pl1[plno].threes) + (4 * pl1[plno].fours) + (6 * pl1[plno].sixes);
            pl1[plno].str = ((pl1[plno].runs * 100.0) / pl1[plno].balls);
            printf(" %-15s %-14d %-13d %-11d %-9d %.2f\n\n", pl1[plno].name, pl1[plno].runs, pl1[plno].balls, pl1[plno].fours, pl1[plno].sixes, pl1[plno].str);
            fclose(batsmenFile);
            break;
        case 2:
            printf("Enter the bowlers number to see his details\n");
            scanf("%d", &plno);
            plno--;
            printf("DATE = %d/%d/%d \n",dat,mo,ye);
            printf("          Player Detail\n");
            printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
            printf("Bowlers       Overs          Runs       Wickets       Economy             \n");
            printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
            bowlersFile = fopen("bowlers.txt", "r");
            if (bowlersFile == NULL)
            {
                printf("Error opening the Bowlers File.\n Please try again later!\n");
                break;
            }
            for (i = 0; i <plno; i++)
            {
                fscanf(bowlersFile, "%s %d %d %d %f", pl2[i].name, &pl2[i].runsgv, &pl2[i].overs, &pl2[i].wkttkn, &pl2[i].econ);
            }
            fscanf(bowlersFile, "%s %d %d %d %f", pl2[plno].name, &pl2[plno].runsgv, &pl2[plno].overs, &pl2[plno].wkttkn, &pl2[plno].econ);
            pl2[plno].econ =(float) pl2[plno].runsgv / pl2[plno].overs;
            printf("%-15s %-14d %-13d %-11d %-9.2f\n\n", pl2[plno].name, pl2[plno].overs, pl2[plno].runsgv, pl2[plno].wkttkn, pl2[plno].econ);
            fclose(bowlersFile);
            break;
        case 3:
        printf("DATE = %d/%d/%d \n",dat,mo,ye);
            printf("        Match Summary \n");
            printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
            printf("Batsman        Runs        Balls       Fours       Sixes        SR       \n");
            printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
            batsmenFile = fopen("batsmen.txt", "r");
            if (batsmenFile == NULL)
            {
                printf("Error opening the Batsmen File.\n Please try again later!\n");
                break;
            }
            for (i = 0; i < m; i++)
            {
                fscanf(batsmenFile, "%s %d %d %d %d %d %d", &pl1[i].name, &pl1[i].ones, &pl1[i].twos, &pl1[i].threes, &pl1[i].fours, &pl1[i].sixes, &pl1[i].balls);
                pl1[i].runs = (pl1[i].ones) + (2 * pl1[i].twos) + (3 * pl1[i].threes) + (4 * pl1[i].fours) + (6 * pl1[i].sixes);
                pl1[i].str = ((pl1[i].runs * 100.0) / pl1[i].balls);
                printf("%-15s %-14d %-13d %-11d %-9d %.2f\n\n", pl1[i].name, pl1[i].runs, pl1[i].balls, pl1[i].fours, pl1[i].sixes, pl1[i].str);
                pl3.toruns += pl1[i].runs;
            }

            printf("TOTAL RUNS: %d \n\n", pl3.toruns);
            fclose(batsmenFile);
            printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
            printf("Bowlers       Overs       Runs       Wickets       Economy             \n");
            printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
            bowlersFile = fopen("bowlers.txt", "r");
            if (bowlersFile == NULL)
            {
                printf("Error opening the Bowlers File.\n Please try again later!\n");
                break;
            }
            for (i = 0; i < n; i++)
            {
                fscanf(bowlersFile, "%s %d %d %d", &pl2[i].name, &pl2[i].runsgv, &pl2[i].overs, &pl2[i].wkttkn);
                pl2[i].econ =(float) pl2[i].runsgv / pl2[i].overs;
                printf("%-15s %-14d %-13d %-11d %-9.2f\n\n", pl2[i].name, pl2[i].overs, pl2[i].runsgv, pl2[i].wkttkn, pl2[i].econ);
            }

            fclose(bowlersFile);
            break;
        case 4:
            pl3.max_run = 0, pl4.max_x = 0, pl3.max_four = 0, pl3.max_six = 0;
            batsmenFile = fopen("batsmen.txt", "r");
            if (batsmenFile == NULL)
            {
                printf("Error opening the Batsmen File.\n Please try again later!\n");
                break;
            }
            for (i = 0; i < m; i++)
            {
                fscanf(batsmenFile, "%s %d %d %d %d %d %d", &pl1[i].name, &pl1[i].ones, &pl1[i].twos, &pl1[i].threes, &pl1[i].fours, &pl1[i].sixes, &pl1[i].balls);
                int runs = (pl1[i].ones) + (2 * pl1[i].twos) + (3 * pl1[i].threes) + (4 * pl1[i].fours) + (6 * pl1[i].sixes);
                if (runs > pl3.max_run)
                    pl3.max_run = runs;

                if (pl1[i].fours > pl3.max_four)
                    pl3.max_four = pl1[i].fours;

                if (pl1[i].sixes > pl3.max_six)
                    pl3.max_six = pl1[i].sixes;
            }

            fclose(batsmenFile);
            bowlersFile = fopen("bowlers.txt", "r");
            if (bowlersFile == NULL)
            {
                printf("Error opening the Bowlers File.\n Please try again later!\n");
                break;
            }

            for (i = 0; i < n; i++)
            {
                fscanf(bowlersFile, "%s %d %d %d", &pl2[i].name, &pl2[i].runsgv, &pl2[i].overs, &pl2[i].wkttkn);

                if (pl2[i].wkttkn > pl4.max_x)
                    pl4.max_x = pl2[i].wkttkn;
            }

            fclose(bowlersFile);
            printf("DATE = %d/%d/%d \n",dat,mo,ye);
            printf("Highest runs scored by the batsman: %d\n", pl3.max_run);
            printf("Maximum fours scored by the batsman: %d\n", pl3.max_four);
            printf("Maximum sixes scored by the batsman: %d\n", pl3.max_six);
            printf("Maximum wickets taken by the bowler: %d\n", pl4.max_x);
            break;
        case 5:
            exit(1);
        default:
            printf("Invalid Choice!\n");
            printf("Enter the correct choice \n");
            break;
        }
    } while (choice != 5);
}
