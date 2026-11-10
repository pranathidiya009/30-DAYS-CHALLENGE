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


float absDiff(float a, float b);
float floorZero(float x);
void clearBuffer(void);
void printZoneName(int z);

void printZoneName(int z)
{
    if (z == 0)      printf("Academic Block");
    else if (z == 1) printf("Hostel");
    else if (z == 2) printf("Library");
    else if (z == 3) printf("Cafeteria");
    else             printf("Sports Area");
}

float absDiff(float a, float b)
{
    if (a > b)
        return a - b;
    return b - a;
}

float floorZero(float x)
{
    if (x < 0)
        return 0;
    return x;
}

void clearBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void inputData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS])
{
    int z, d;

    printf("\nEnter readings (use authorised data or clearly labelled SIMULATED sample data).\n");

    for (z = 0; z < ZONES; z++)
    {
        printf("\n--- Zone %d: ", z + 1);
        printZoneName(z);
        printf(" ---\n");

        for (d = 0; d < DAYS; d++)
        {
            /* Temperature */
            do
            {
                printf("Day %d Temperature (10-50 C): ", d + 1);
                if (scanf("%f", &temp[z][d]) != 1)
                {
                    clearBuffer();
                    temp[z][d] = -1;   
                }
                if (temp[z][d] < 10 || temp[z][d] > 50)
                    printf("  Invalid! Re-enter.\n");
            } while (temp[z][d] < 10 || temp[z][d] > 50);

            /* Humidity */
            do
            {
                printf("Day %d Humidity (0-100 %%): ", d + 1);
                if (scanf("%f", &humidity[z][d]) != 1)
                {
                    clearBuffer();
                    humidity[z][d] = -1;
                }
                if (humidity[z][d] < 0 || humidity[z][d] > 100)
                    printf("  Invalid! Re-enter.\n");
            } while (humidity[z][d] < 0 || humidity[z][d] > 100);

          
            do
            {
                printf("Day %d AQI (0-500): ", d + 1);
                if (scanf("%d", &aqi[z][d]) != 1)
                {
                    clearBuffer();
                    aqi[z][d] = -1;
                }
                if (aqi[z][d] < 0 || aqi[z][d] > 500)
                    printf("  Invalid! Re-enter.\n");
            } while (aqi[z][d] < 0 || aqi[z][d] > 500);
        }
    }
    printf("\nData entered successfully.\n");
}

void displayData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS])
{
    int z, d;

    printf("\n=== Temperature (C) ===\n");
    printf("%-16s", "Zone");
    for (d = 0; d < DAYS; d++)
        printf("Day%-5d", d + 1);
    printf("\n");
    for (z = 0; z < ZONES; z++)
    {
        printf("%d ", z + 1);
        printf("%-14s", z == 0 ? "Academic" : z == 1 ? "Hostel" : z == 2 ? "Library" : z == 3 ? "Cafeteria" : "Sports");
        for (d = 0; d < DAYS; d++)
            printf("%-8.1f", temp[z][d]);
        printf("\n");
    }

    printf("\n=== Humidity (%%) ===\n");
    printf("%-16s", "Zone");
    for (d = 0; d < DAYS; d++)
        printf("Day%-5d", d + 1);
    printf("\n");
    for (z = 0; z < ZONES; z++)
    {
        printf("%d ", z + 1);
        printf("%-14s", z == 0 ? "Academic" : z == 1 ? "Hostel" : z == 2 ? "Library" : z == 3 ? "Cafeteria" : "Sports");
        for (d = 0; d < DAYS; d++)
            printf("%-8.1f", humidity[z][d]);
        printf("\n");
    }

    printf("\n=== AQI ===\n");
    printf("%-16s", "Zone");
    for (d = 0; d < DAYS; d++)
        printf("Day%-5d", d + 1);
    printf("\n");
    for (z = 0; z < ZONES; z++)
    {
        printf("%d ", z + 1);
        printf("%-14s", z == 0 ? "Academic" : z == 1 ? "Hostel" : z == 2 ? "Library" : z == 3 ? "Cafeteria" : "Sports");
        for (d = 0; d < DAYS; d++)
            printf("%-8d", aqi[z][d]);
        printf("\n");
    }
}

void calculateAverages(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS],
                       float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES])
{
    int z, d;
    float sumT, sumH, sumA;

    for (z = 0; z < ZONES; z++)
    {
        sumT = 0;
        sumH = 0;
        sumA = 0;
        for (d = 0; d < DAYS; d++)
        {
            sumT += temp[z][d];
            sumH += humidity[z][d];
            sumA += aqi[z][d];
        }
        avgTemp[z] = sumT / DAYS;
        avgHumidity[z] = sumH / DAYS;
        avgAQI[z] = sumA / DAYS;
    }
}

void detectRiskZones(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS],
                     int riskDays[ZONES])
{
    int z, d;

    printf("\n=== Risk Day Report ===\n");
    printf("(Risk day: AQI > 150 OR Temp > 35 C OR Humidity > 80%%)\n");

    for (z = 0; z < ZONES; z++)
    {
        riskDays[z] = 0;
        printf("\nZone %d (", z + 1);
        printZoneName(z);
        printf("): ");

        /* first pass: count */
        for (d = 0; d < DAYS; d++)
        {
            if (aqi[z][d] > 150 || temp[z][d] > 35 || humidity[z][d] > 80)
                riskDays[z]++;
        }

        printf("%d risk day(s)", riskDays[z]);

        if (riskDays[z] > 0)
        {
            printf(" -> Day(s): ");
         
            for (d = 0; d < DAYS; d++)
            {
                if (aqi[z][d] > 150 || temp[z][d] > 35 || humidity[z][d] > 80)
                    printf("%d ", d + 1);
            }
        }
        printf("\n");
    }
}

void computeGreenIndex(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES],
                       float greenIndex[ZONES])
{
    int z;
    float aqiScore, tempScore, humScore;

    for (z = 0; z < ZONES; z++)
    {
        aqiScore = 100 - (avgAQI[z] / 5);
        tempScore = 100 - 4 * absDiff(avgTemp[z], 25);
        humScore = 100 - 2 * absDiff(avgHumidity[z], 50);

        aqiScore = floorZero(aqiScore);
        tempScore = floorZero(tempScore);
        humScore = floorZero(humScore);

        greenIndex[z] = 0.4f * aqiScore + 0.3f * tempScore + 0.3f * humScore;
    }
}

void displayRanking(float greenIndex[ZONES])
{
    int order[ZONES];
    int rank[ZONES];
    int i, j, z, temp, better;
    float eps = 0.0001f;

   
    for (i = 0; i < ZONES; i++)
    {
        better = 0;
        for (j = 0; j < ZONES; j++)
        {
            if (greenIndex[j] > greenIndex[i] + eps)
                better++;
        }
        rank[i] = better + 1;
    }

    
    for (i = 0; i < ZONES; i++)
        order[i] = i;

    for (i = 0; i < ZONES - 1; i++)
    {
        for (j = 0; j < ZONES - 1 - i; j++)
        {
            if (greenIndex[order[j]] < greenIndex[order[j + 1]])
            {
                temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;
            }
        }
    }

    printf("\n=== Green Index Ranking (higher = better) ===\n");
    printf("%-6s %-5s %-16s %s\n", "Rank", "Zone", "Name", "Green Index");
    for (i = 0; i < ZONES; i++)
    {
        z = order[i];
        printf("%-6d %-5d ", rank[z], z + 1);
        printf("%-16s", z == 0 ? "Academic Block" : z == 1 ? "Hostel" : z == 2 ? "Library" : z == 3 ? "Cafeteria" : "Sports Area");
        printf(" %.2f\n", greenIndex[z]);
    }
    printf("(Classroom scoring model, not an official environmental rating.)\n");
}

void displayRecommendations(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES],
                            int riskDays[ZONES])
{
    int z, flagged;

    printf("\n=== Recommendations ===\n");
    for (z = 0; z < ZONES; z++)
    {
        flagged = 0;
        printf("\nZone %d (", z + 1);
        printZoneName(z);
        printf(")  [Avg T=%.1f, H=%.1f, AQI=%.1f, Risk days=%d]\n",
               avgTemp[z], avgHumidity[z], avgAQI[z], riskDays[z]);

        if (avgAQI[z] > 150)
        {
            printf("  - Average AQI is high: reduce vehicle idling or improve ventilation.\n");
            flagged = 1;
        }
        if (avgTemp[z] > 35)
        {
            printf("  - Average temperature is high: add shade or green cover.\n");
            flagged = 1;
        }
        if (avgHumidity[z] > 80)
        {
            printf("  - Average humidity is high: check ventilation or stagnant-water sources.\n");
            flagged = 1;
        }

        if (!flagged)
        {
            if (riskDays[z] > 0)
                printf("  - Averages are fine, but individual days were flagged: review those dates.\n");
            else
                printf("  - No risk detected: continue monitoring.\n");
        }
    }
}

int main(void)
{
    float temp[ZONES][DAYS], humidity[ZONES][DAYS];
    int aqi[ZONES][DAYS];
    float avgTemp[ZONES], avgHumidity[ZONES], avgAQI[ZONES];
    float greenIndex[ZONES];
    int riskDays[ZONES];
    int choice;
    int dataReady = 0;

    do
    {
        printf("\n========== ECOGUARD: Monitor. Analyse. Act. ==========\n");
        printf("1 Input / Update Data\n");
        printf("2 Display Data\n");
        printf("3 Zone-wise Averages\n");
        printf("4 Detect Risk Days\n");
        printf("5 Green Index and Ranking\n");
        printf("6 Recommendations\n");
        printf("7 Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            clearBuffer();
            choice = 0;
        }

        if (choice == 1)
        {
            inputData(temp, humidity, aqi);
            dataReady = 1;
        }
        else if (choice >= 2 && choice <= 6)
        {
            if (!dataReady)
            {
                printf("\nNo data yet. Please enter data first (option 1).\n");
            }
            else if (choice == 2)
            {
                displayData(temp, humidity, aqi);
            }
            else if (choice == 3)
            {
                int z;
                calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
                printf("\n=== Zone-wise 7-Day Averages ===\n");
                printf("%-5s %-16s %-10s %-10s %-10s\n", "Zone", "Name", "Avg Temp", "Avg Hum", "Avg AQI");
                for (z = 0; z < ZONES; z++)
                {
                    printf("%-5d ", z + 1);
                    printf("%-16s", z == 0 ? "Academic Block" : z == 1 ? "Hostel" : z == 2 ? "Library" : z == 3 ? "Cafeteria" : "Sports Area");
                    printf(" %-10.2f %-10.2f %-10.2f\n", avgTemp[z], avgHumidity[z], avgAQI[z]);
                }
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
        }
        else if (choice == 7)
        {
            printf("\nExiting EcoGuard. Stay green!\n");
        }
        else
        {
            printf("\nInvalid choice. Enter 1-7.\n");
        }
    } while (choice != 7);

    return 0;
}
