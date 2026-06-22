/* task_max.c — 発展：全レコードを読み込んで最高気温の場所を表示する */
/* 事前に step2（または step4）を実行して sensor.csv を作成しておくこと */

#include <stdio.h>
#include <string.h>

typedef struct {
    char  location[32];
    int   temperature;
    float humidity;
} SensorData;

int parseSensorLine(const char *line, SensorData *out) {
    return sscanf(line, "%31[^,],%d,%f",
                  out->location,
                  &out->temperature,
                  &out->humidity) == 3;
}

int main(void) {
    FILE *fp = fopen("sensor.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "sensor.csv が見つかりません（先に step2 を実行してください）\n");
        return 1;
    }

    char line[256];
    SensorData data;
    SensorData maxData;
    int found = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (parseSensorLine(line, &data)) {
            if (!found || data.temperature > maxData.temperature) {
                maxData = data;
                found = 1;
            }
        }
    }

    fclose(fp);
    fp = NULL;

    if (found) {
        printf("最高気温: %s / %d°C\n", maxData.location, maxData.temperature);
    } else {
        printf("データがありません\n");
    }

    return 0;
}
