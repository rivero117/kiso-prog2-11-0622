/* ex_read.c — 演習：parseSensorLine 関数を自分で実装する */
/* TODO の部分を埋めて、sensor_ex.csv を読み込んで表示できるようにしよう */
/* 事前に ex_write を実行して sensor_ex.csv を作成しておくこと           */

#include <stdio.h>
#include <string.h>

typedef struct {
    char  location[32];
    int   temperature;
    float humidity;
} SensorData;

/* TODO: CSV の1行を SensorData 構造体に変換する関数を実装する */
/*       戻り値: 成功=1、失敗=0                                */
/*       ヒント: sscanf(line, "%31[^,],%d,%f", ...)           */
int parseSensorLine(const char *line, SensorData *out) {
    /* TODO: sscanf を使って line を分解し、
             out->location, out->temperature, out->humidity に代入する */
    return 0; /* ← 実装できたら正しい戻り値に変える */
}

int main(void) {
    FILE *fp = fopen("sensor_ex.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "sensor_ex.csv が見つかりません（先に ex_write を実行してください）\n");
        return 1;
    }

    char line[256];
    SensorData data;

    printf("=== sensor_ex.csv の内容 ===\n");
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
