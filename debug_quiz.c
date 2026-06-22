/* debug_quiz.c — バグを3つ直してコンパイル・実行できるようにしよう */

#include <stdio.h>
#include <string.h>

typedef struct {
    char  location[32];
    int   temperature;
    float humidity;
} SensorData;

int main(void) {
    FILE *fp = fopen("sensor.csv", "w");
    /* バグ1: fopen が失敗したとき（fp == NULL のとき）の処理がない */

    SensorData data = {"教室", 25, 60.5};

    /* バグ2: humidity は float なのに %d を使っている */
    fprintf(fp, "%s,%d,%d\n", data.location, data.temperature, data.humidity);

    /* バグ3: fclose がない（ファイルを閉じていない） */

    printf("書き込み完了\n");
    return 0;
}
