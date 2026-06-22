/* ex_write.c — 演習：writeSensorData 関数を自分で実装する */
/* TODO の部分を埋めて、sensor_ex.csv に3件書き込めるようにしよう */

#include <stdio.h>
#include <string.h>

typedef struct {
    char  location[32];
    int   temperature;
    float humidity;
} SensorData;

/* TODO: 構造体を CSV の1行として fp に書き出す関数を実装する */
/*       書き出す形式: "場所,気温,湿度\n"                      */
/*       例: "実験室,23,58.0\n"                                */
void writeSensorData(FILE *fp, SensorData data) {
    /* TODO: fprintf を使って "%s,%d,%.1f\n" の形式で書き出す */
}

int main(void) {
    FILE *fp = fopen("sensor_ex.csv", "w");
    if (fp == NULL) {
        fprintf(stderr, "ファイルを開けませんでした\n");
        return 1;
    }

    SensorData records[3] = {
        {"実験室", 23, 58.0},
        {"体育館", 31, 75.0},
        {"図書室", 20, 50.0},
    };

    for (int i = 0; i < 3; i++) {
        writeSensorData(fp, records[i]);
    }

    fclose(fp);
    fp = NULL;

    printf("sensor_ex.csv に書き込みました\n");
    printf("cat sensor_ex.csv で中身を確認してみよう\n");
    return 0;
}
