/* step3_struct_read.c — CSV ファイルを構造体に読み込む */
/* 事前に step2 を実行して sensor.csv を作成しておくこと */

#include <stdio.h>
#include <string.h>

typedef struct {
    char  location[32];
    int   temperature;
    float humidity;
} SensorData;

/* CSV の1行を SensorData に変換する。成功=1 / 失敗=0 */
int parseSensorLine(const char *line, SensorData *out) {
    return sscanf(line, "%31[^,],%d,%f",
                  out->location,       /* char 配列なので & 不要 */
                  &out->temperature,   /* int なので & が必要 */
                  &out->humidity)      /* float なので & が必要 */
           == 3;
}

int main(void) {
    FILE *fp = fopen("sensor.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "sensor.csv が見つかりません（先に step2 を実行してください）\n");
        return 1;
    }

    char line[256];
    SensorData data;

    printf("=== sensor.csv の内容 ===\n");
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
