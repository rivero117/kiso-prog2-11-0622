# 第11回 技術資料 — 構造体とCSVファイル

**科目:** 基礎プログラミングII　**対象:** 2年生　**日付:** 2026-06-22（月）

---

## この資料で学ぶこと

| 項目 | 内容 |
|------|------|
| 構造体をファイルに書く | `fprintf` で構造体のメンバを CSV に出力する |
| CSV を構造体に読み込む | `fgets` ＋ `sscanf` で1行を構造体に変換する |
| 実践：センサーデータ | 温湿度データを構造体で管理する完成形 |

---

## 0. このレッスンの位置づけ

これまでに学んだ2つの技術を**組み合わせる**回です。

```
構造体（#2〜3）
    ↓「バラバラなデータを1つのかたまりにまとめる」
ファイル操作（#9〜10）
    ↓「プログラムが終わってもデータが残る」
────────────────────────────────
構造体＋ファイル（#11）
    ↓「センサーデータを構造体で扱い、CSVに保存・読み込みできる」
```

プログラミング演習では Arduino の温湿度センサーデータを CSV に記録する。  
このレッスンを学ぶと、**そのデータをC言語で読み込んで処理**できるようになる。

---

## 1. センサーデータを構造体で定義する

温湿度センサーのデータを表す構造体を作る。

```c
typedef struct {
    char location[32];  // 計測場所（「教室」「廊下」など）
    int  temperature;   // 気温（整数、℃）
    float humidity;     // 湿度（小数、%）
} SensorData;
```

変数を作る：

```c
SensorData data1;
strcpy(data1.location, "教室");
data1.temperature = 25;
data1.humidity    = 60.5;
```

---

## 2. 構造体のデータを CSV ファイルに書く

`fprintf` で各メンバを CSV 形式で書き出す。

```c
void writeSensorData(FILE *fp, SensorData data) {
    fprintf(fp, "%s,%d,%.1f\n",
            data.location,
            data.temperature,
            data.humidity);
}
```

呼び出し例：

```c
FILE *fp = fopen("sensor.csv", "w");
if (fp == NULL) { return 1; }

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
```

`sensor.csv` に書かれる内容：

```
教室,25,60.5
廊下,22,55.0
食堂,28,70.0
```

---

## 3. CSV ファイルを構造体に読み込む

`fgets` で1行読んで、`sscanf` で分解し、構造体に代入する。

```c
// CSV の1行を SensorData 構造体に変換する関数
// 戻り値: 成功=1、失敗=0
int parseSensorLine(const char *line, SensorData *out) {
    return sscanf(line, "%31[^,],%d,%f",
                  out->location,
                  &out->temperature,
                  &out->humidity) == 3;
}
```

呼び出し例：

```c
FILE *fp = fopen("sensor.csv", "r");
if (fp == NULL) { return 1; }

char line[256];
SensorData data;

while (fgets(line, sizeof(line), fp) != NULL) {
    if (parseSensorLine(line, &data)) {
        printf("%s: %d°C / %.0f%%\n",
               data.location, data.temperature, data.humidity);
    }
}

fclose(fp);
fp = NULL;
```

---

## 4. 完成形 — 書き込みと読み込みを1つのプログラムで

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char  location[32];
    int   temperature;
    float humidity;
} SensorData;

// CSVに1行書く
void writeSensorData(FILE *fp, SensorData data) {
    fprintf(fp, "%s,%d,%.1f\n",
            data.location, data.temperature, data.humidity);
}

// CSV1行を構造体に変換（成功=1 / 失敗=0）
int parseSensorLine(const char *line, SensorData *out) {
    return sscanf(line, "%31[^,],%d,%f",
                  out->location,
                  &out->temperature,
                  &out->humidity) == 3;
}

int main(void) {
    const char *filename = "sensor.csv";

    // ── 書き込み ───────────────────────────────────
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "書き込み失敗\n");
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

    // ── 読み込み ───────────────────────────────────
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "読み込み失敗\n");
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
```

実行結果：

```
=== 読み込み結果 ===
場所: 教室 / 気温: 25°C / 湿度: 60%
場所: 廊下 / 気温: 22°C / 湿度: 55%
場所: 食堂 / 気温: 28°C / 湿度: 70%
```

---

## 5. 構造体ポインタを引数で渡す（復習）

`parseSensorLine` の引数 `SensorData *out` を使ったのは、**関数の中で構造体の値を変更したい**から。

```c
// ❌ 値渡し：関数の中で変えても、呼び出し元には反映されない
void parse(const char *line, SensorData out) {
    sscanf(line, "%31[^,],%d,%f",
           out.location, &out.temperature, &out.humidity);
    // ← ここで変えても main 側には届かない
}

// ✅ ポインタ渡し：関数の中で変えると、呼び出し元の変数が変わる
void parse(const char *line, SensorData *out) {
    sscanf(line, "%31[^,],%d,%f",
           out->location, &out->temperature, &out->humidity);
    // ← out は呼び出し元の変数のアドレスなので、変更が届く
}
```

```
呼び出し:
parseSensorLine(line, &data);
                      ↑
                 data のアドレスを渡す

関数の中:
out → data のアドレスを指している
out->location = ... → data.location が変わる
```

---

## 6. よくある間違い

### ① `out->location` に `strcpy` を使わず直接代入する

```c
// ❌ 文字配列に = で代入はできない
out->location = "教室";   // コンパイルエラー

// ✅ sscanf で直接読む か strcpy を使う
sscanf(line, "%31[^,],...", out->location, ...);
// または
strcpy(out->location, "教室");
```

### ② fprintf の format と型が合わない

```c
SensorData data = {"教室", 25, 60.5};

// ❌ float を %d で出力しようとした
fprintf(fp, "%s,%d,%d\n", data.location, data.temperature, data.humidity);
//                                                          ~~~ floatなのに%d

// ✅ float は %.1f
fprintf(fp, "%s,%d,%.1f\n", data.location, data.temperature, data.humidity);
```

### ③ `&out->location` と `out->location` を混同する

```c
// sscanf の引数に注意
// char 配列（location）はそのまま渡す（配列名はアドレス）
// int / float はアドレス演算子 & が必要

sscanf(line, "%31[^,],%d,%f",
       out->location,      // ← char 配列なので & 不要
       &out->temperature,  // ← int なので & が必要
       &out->humidity);    // ← float なので & が必要
```

---

## 7. まとめ

| やること | コード |
|---------|--------|
| 構造体を CSV に書く | `fprintf(fp, "%s,%d,%.1f\n", d.location, d.temperature, d.humidity)` |
| CSV を構造体に読む | `fgets` → `sscanf` → 構造体に代入 |
| 関数で構造体を変更する | 引数を `SensorData *` にして `out->member` でアクセス |

---

## 前後のつながり

| 回 | テーマ | このレッスンとの関係 |
|----|--------|-------------------|
| #2〜3 | 構造体 | SensorData 型の定義はここで学んだ |
| #9 | fopen / fprintf / fscanf | 書き込み・読み込みの基本 |
| #10 | fgets / sscanf | CSV1行を文字列で読んで分解する |
| **#11（今回）** | **構造体＋CSV** | 2つを組み合わせてセンサーデータを扱う |
| #12 | データ集計 | 読み込んだ構造体配列で平均・最大・最小を計算する |
