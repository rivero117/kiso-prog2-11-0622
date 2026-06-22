/* ex_write.c -- Enshuu 1: Kozo wo CSV ni kakidasu (yaku 10 pun) */
/* 演習①: 構造体を CSV に書き出す（約10分）                       */
/* TODO を埋めてコンパイル・実行してみよう。                       */
/* 今の状態でもコンパイルは通る。実行すると意図しない動作になる。  */

#include <stdio.h>
#include <string.h>

typedef struct {
    char  location[32];
    int   temperature;
    float humidity;
} SensorData;

/*
 * TODO 1: fprintf の引数を直して、構造体を CSV の1行として書き出す。
 *
 *   書き出したい形式の例:
 *     実験室,23,58.0
 *     体育館,31,75.0
 *
 *   フォーマット指定子の対応:
 *     文字列 -> %s    整数 -> %d    小数 -> %.1f
 *
 *   data のメンバ: data.location  data.temperature  data.humidity
 *
 *   直すべき箇所: 2行目と3行目の引数（0 と 0.0f を正しいメンバ名に変える）
 */

 SensorData records[2] = {
    {"実験室",23,58.0},
    {"体育館",31,75.0}
 };

void writeSensorData(FILE *fp, SensorData data) {
    fprintf(fp, "%s,%d,%.1f\n",
            data.location,
            data.temperature,       /* TODO 1: data.temperature に直す */
            data.humidity);   /* TODO 1: data.humidity に直す   */
}

int main(void) {
    /*
     * TODO 2: fopen のモードを "r" から正しいモードに直す。
     *
     *   "r" -> 読み込み専用（書き込めない）
     *   "w" -> 新規書き込み（ファイルがあれば上書き）
     *   "a" -> 追記（ファイルの末尾に足す）
     *
     *   今回は毎回新しく書き直したい -> どれが正しい？
     */
    FILE *fp = fopen("sensor_ex.csv", "w"); /* TODO 2: "r" を正しいモードに直す */
    if (fp == NULL) {
        fprintf(stderr, "ファイルを開けませんでした\n");
        return 1;
    }

    SensorData records[] = {
        {"実験室", 23, 58.0},
        {"体育館", 31, 75.0},
        {"図書室", 20, 50.0},
        {"職員室", 26, 62.0},
        {"寮室", 22, 42.0}
        /* TODO 3: ここに自分でデータを1件追加する。場所・気温・湿度は自由。
         *   書き方の例: {"屋上", 33, 80.0},                                */
    };
    int n = sizeof(records) / sizeof(records[0]);

    for (int i = 0; i < n; i++) {
        writeSensorData(fp, records[i]);
    }

    fclose(fp);
    fp = NULL;

    printf("sensor_ex.csv に書き込みました（%d 件）\n", n);
    return 0;
}
