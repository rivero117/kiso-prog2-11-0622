/* step4_all.c — 書き込みと読み込みを1つにまとめた完成形 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char  location[32];
    int   temperature;
    float humidity;
} SensorData;

void writeSensorData(FILE *fp, SensorData data) {
    fprintf(fp, "%s,%d,%.1f\n",
            data.location, data.temperature, data.humidity);
}

int parseSensorLine(const char *line, SensorData *out) {
    return sscanf(line, "%31[^,],%d,%f",
                  out->location,
                  &out->temperature,
                  &out->humidity) == 3;
}

int main(void) {
    const char *filename = "sensor.csv";

    /* ── 書き込み ──────────────────────────────── */
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "書き込み用にファイルを開けませんでした\n");
        return 1;
    }

    SensorData records[3] = {
        {"教室", 25, 60.5},
        {"廊下", 22, 55.0},
        {"食堂", 28, 70.0},
    };
    for (int i = 0; i < 3; i++) {
        writeSensorData(fp, records[i]);
    }

    fclose(fp);
    fp = NULL;

    /* ── 読み込み ──────────────────────────────── */
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "読み込み用にファイルを開けませんでした\n");
        return 1;
    }

    char line[256];
    SensorData data;

    printf("=== 読み込み結果 ===\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (parseSensorLine(line, &data)) {
            printf("場所: %s / 気温: %d°C / 湿度: %.0f%%\n",
                   data.location, data.temperature, data.humidity);
        }
    }

    fclose(fp);
    fp = NULL;
    return 0;
}
