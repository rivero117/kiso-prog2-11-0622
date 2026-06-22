/* step2_struct_write.c — 構造体を CSV ファイルに書き出す */

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

int main(void) {
    FILE *fp = fopen("sensor.csv", "w");
    if (fp == NULL) {
        fprintf(stderr, "ファイルを開けませんでした\n");
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

    printf("sensor.csv に書き込みました\n");
    printf("cat sensor.csv で中身を確認してみよう\n");
    return 0;
}
