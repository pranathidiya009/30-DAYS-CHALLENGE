#include <stdio.h>

#define ZONES 5
#define DAYS 7

void inputData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]);
void displayData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]);
void calculateAverages(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS],
                       float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES]);
void detectRiskZones(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS],
                     int riskDays[ZONES]);
void computeGreenIndex(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES],
                       float greenIndex[ZONES]);
void displayRanking(float greenIndex[ZONES]);
void displayRecommendations(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES],
                            int riskDays[ZONES]);

/* helpers */
float absDiff(float a, float b)
{
    if (a > b) return a - b;
    return b - a;
}

float zeroFloor(float x)
{
    if (x < 0) return 0;
    return x;
}

void printName(int z)
{
    if (z == 0) printf("Academic Block");
    else if (z == 1) printf("Hostel");
    else if (z == 2) printf("Library");
    else if (z == 3) printf("Cafeteria");
    else printf("Sports Area");
}

void inputData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS])
{
    int z, d;
    printf("Enter readings (real/authorised OR clearly labelled SAMPLE data)\n");
    for (z = 0; z < ZONES; z++)
    {
        for (d = 0; d < DAYS; d++)
        {
            printf("Zone %d Day %d\n", z + 1, d + 1);
            do {
                printf("  Temp (10-50): ");
                scanf("%f", &temp[z][d]);
            } while (temp[z][d] < 10 || temp[z][d] > 50);
            do {
                printf("  Humidity (0-100): ");
                scanf("%f", &humidity[z][d]);
            } while (humidity[z][d] < 0 || humidity[z][d] > 100);
            do {
                printf("  AQI (0-500): ");
                scanf("%d", &aqi[z][d]);
            } while (aqi[z][d] < 0 || aqi[z][d] > 500);
        }
    }
}

void displayData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS])
{
    int z, d;
    printf("\nTemperature\n");
    for (z = 0; z < ZONES; z++)
    {
        printf("Zone %d: ", z + 1);
        for (d = 0; d < DAYS; d++) printf("%6.1f", temp[z][d]);
        printf("\n");
    }
    printf("\nHumidity\n");
    for (z = 0; z < ZONES; z++)
    {
        printf("Zone %d: ", z + 1);
        for (d = 0; d < DAYS; d++) printf("%6.1f", humidity[z][d]);
        printf("\n");
    }
    printf("\nAQI\n");
    for (z = 0; z < ZONES; z++)
    {
        printf("Zone %d: ", z + 1);
        for (d = 0; d < DAYS; d++) printf("%6d", aqi[z][d]);
        printf("\n");
    }
}

void calculateAverages(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS],
                       float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES])
{
    int z, d;
    for (z = 0; z < ZONES; z++)
    {
        avgTemp[z] = 0;
        avgHumidity[z] = 0;
        avgAQI[z] = 0;
        for (d = 0; d < DAYS; d++)
        {
            avgTemp[z] += temp[z][d];
            avgHumidity[z] += humidity[z][d];
            avgAQI[z] += aqi[z][d];
        }
        avgTemp[z] /= DAYS;
        avgHumidity[z] /= DAYS;
        avgAQI[z] /= DAYS;
    }
}

void detectRiskZones(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS],
                     int riskDays[ZONES])
{
    int z, d;
    for (z = 0; z < ZONES; z++)
    {
        riskDays[z] = 0;
        printf("Zone %d: risk days on day(s): ", z + 1);
        for (d = 0; d < DAYS; d++)
        {
            if (aqi[z][d] > 150 || temp[z][d] > 35 || humidity[z][d] > 80)
            {
                riskDays[z]++;
                printf("%d ", d + 1);
            }
        }
        printf("| count = %d\n", riskDays[z]);
    }
}

void computeGreenIndex(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES],
                       float greenIndex[ZONES])
{
    int z;
    float a, t, h;
    for (z = 0; z < ZONES; z++)
    {
        a = zeroFloor(100 - avgAQI[z] / 5);
        t = zeroFloor(100 - 4 * absDiff(avgTemp[z], 25));
        h = zeroFloor(100 - 2 * absDiff(avgHumidity[z], 50));
        greenIndex[z] = 0.4 * a + 0.3 * t + 0.3 * h;
    }
}

void displayRanking(float greenIndex[ZONES])
{
    int rank[ZONES];
    int i, j, r, better;

    /* rank = 1 + number of zones with a higher Green Index (ties share a rank) */
    for (i = 0; i < ZONES; i++)
    {
        better = 0;
        for (j = 0; j < ZONES; j++)
            if (greenIndex[j] > greenIndex[i]) better++;
        rank[i] = better + 1;
    }

    printf("Rank  Zone  Green Index\n");
    for (r = 1; r <= ZONES; r++)          /* print rank 1 first, then 2, ... */
        for (i = 0; i < ZONES; i++)
            if (rank[i] == r)
            {
                printf("%-5d ", r);
                printName(i);
                printf("  %.2f\n", greenIndex[i]);
            }
}

void displayRecommendations(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES],
                            int riskDays[ZONES])
{
    int z, flag;
    for (z = 0; z < ZONES; z++)
    {
        flag = 0;
        printf("\nZone %d (", z + 1);
        printName(z);
        printf("):\n");
        if (avgAQI[z] > 150)
        {
            printf("  Reduce vehicle idling or improve ventilation.\n");
            flag = 1;
        }
        if (avgTemp[z] > 35)
        {
            printf("  Add shade or green cover.\n");
            flag = 1;
        }
        if (avgHumidity[z] > 80)
        {
            printf("  Check ventilation or stagnant-water sources.\n");
            flag = 1;
        }
        if (flag == 0 && riskDays[z] > 0)
            printf("  Review the flagged days.\n");
        else if (flag == 0)
            printf("  No risk detected. Continue monitoring.\n");
    }
}

int main()
{
    float temp[ZONES][DAYS], humidity[ZONES][DAYS];
    int aqi[ZONES][DAYS];
    float avgTemp[ZONES], avgHumidity[ZONES], avgAQI[ZONES], greenIndex[ZONES];
    int riskDays[ZONES];
    int choice, z;
    int dataReady = 0;

    do
    {
        printf("\n1 Input/Update Data\n2 Display Data\n3 Zone-wise Averages\n");
        printf("4 Detect Risk Days\n5 Green Index and Ranking\n6 Recommendations\n7 Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            inputData(temp, humidity, aqi);
            dataReady = 1;
        }
        else if (choice >= 2 && choice <= 6 && dataReady == 0)
        {
            printf("Enter data first (option 1).\n");
        }
        else if (choice == 2)
        {
            displayData(temp, humidity, aqi);
        }
        else if (choice == 3)
        {
            calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
            for (z = 0; z < ZONES; z++)
                printf("Zone %d: Temp %.2f  Humidity %.2f  AQI %.2f\n",
                       z + 1, avgTemp[z], avgHumidity[z], avgAQI[z]);
        }
        else if (choice == 4)
        {
            detectRiskZones(temp, humidity, aqi, riskDays);
        }
        else if (choice == 5)
        {
            calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
            computeGreenIndex(avgTemp, avgHumidity, avgAQI, greenIndex);
            displayRanking(greenIndex);
        }
        else if (choice == 6)
        {
            calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
            detectRiskZones(temp, humidity, aqi, riskDays);
            displayRecommendations(avgTemp, avgHumidity, avgAQI, riskDays);
        }
        else if (choice != 7)
        {
            printf("Invalid choice.\n");
        }
    } while (choice != 7);

    return 0;
}
