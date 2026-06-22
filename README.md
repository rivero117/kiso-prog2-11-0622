# 基礎プログラミングII — 第11回 演習（2026-06-22）

**科目:** 基礎プログラミングII　**対象:** 2年生

---

## 前回（#10）から今回（#11）へのつながり

前回は「CSV ファイルを行単位で読む」技術を学びました。

```
前回（#10）でできるようになったこと
  fgets  → 1行まるごと読む
  sscanf → 読んだ行をフィールドごとに分解する
  → 「夕焼け オレンジ,30,90,...」のような行を扱えた

でも、データが増えると管理が大変になった
  「気温」「湿度」「場所」をバラバラな変数で持っていた
```

```
今回（#11）で解決する
  構造体（struct）→ バラバラなデータを1つのかたまりにまとめる
  構造体 ＋ CSV  → センサーデータを構造体で管理してファイルに保存・読み込みできる
```

---

## これができるようになると何が変わるか

| やりたいこと | 今回学ぶ技術 |
|------------|------------|
| 場所・気温・湿度をまとめて扱う | `typedef struct` で `SensorData` 型を作る |
| 構造体をファイルに保存する | `fprintf` で CSV に書き出す |
| CSV を構造体に読み込む | `fgets` → `sscanf` → 構造体に代入 |
| 関数の中で構造体を変更する | ポインタ渡し（`SensorData *`）を使う |

**今回の最終ゴール：**  
温湿度センサーのデータを構造体で管理し、CSV に保存・読み込みできるプログラムを作る。  
→ プログラミング演習の Arduino データをそのまま C 言語で処理できるようになる。

---

## ファイル構成（この順番に進めてください）

| 順番 | ファイル | 内容 |
|:---:|---------|------|
| 0 | `debug_quiz.c` | 【復習】バグを3つ直してコンパイル・実行する |
| 1 | `step1_struct_define.c` | 構造体の定義と変数の作り方 |
| 2 | `step2_struct_write.c` | 構造体を CSV ファイルに書く（`fprintf`） |
| 3 | `step3_struct_read.c` | CSV を構造体に読み込む（`fgets` + `sscanf`） |
| 4 | `step4_all.c` | 書き込み → 読み込みの完成形 |
| ★ | `ex_write.c` | 演習：`/* TODO */` を埋めて書き込み関数を完成させる |
| ★ | `ex_read.c` | 演習：`/* TODO */` を埋めて読み込み関数を完成させる |
| ★★ | `task_max.c` | 発展：最高気温の場所を探す |

**デモ用データ**

| ファイル | 内容 |
|---------|------|
| `sensor.csv` | サンプルのセンサーデータ（step3・step4・task で使用） |

---

## コマンド一覧

### ターミナルを開く
```
Ctrl + `（バッククォート）
```

### コンパイルして実行する

```bash
gcc debug_quiz.c -o debug_quiz && ./debug_quiz

gcc step1_struct_define.c -o step1 && ./step1

gcc step2_struct_write.c -o step2 && ./step2
cat sensor.csv            # 書き込まれた中身を確認

gcc step3_struct_read.c -o step3 && ./step3

gcc step4_all.c -o step4 && ./step4

gcc ex_write.c -o ex_write && ./ex_write
gcc ex_read.c  -o ex_read  && ./ex_read

gcc task_max.c -o task_max && ./task_max
```

### ファイルの中身を確認する

```bash
cat sensor.csv
```

### エラーが出たとき

```bash
# エラーメッセージの例
step2_struct_write.c:12:5: error: ...
       ↑              ↑
    ファイル名       行番号  ← VS Code でその行にジャンプして確認する
```

---

## 今回のポイント整理

### 構造体の定義と変数の作り方

```c
typedef struct {
    char  location[32];  // 場所
    int   temperature;   // 気温（℃）
    float humidity;      // 湿度（%）
} SensorData;

SensorData data = {"教室", 25, 60.5};  // まとめて初期化
```

### 構造体 → CSV に書く

```c
fprintf(fp, "%s,%d,%.1f\n",
        data.location, data.temperature, data.humidity);
```

### CSV → 構造体に読む

```c
fgets(line, sizeof(line), fp);          // 1行まるごと読む
sscanf(line, "%31[^,],%d,%f",           // 分解して構造体に入れる
       out->location, &out->temperature, &out->humidity);
```

### ポインタ渡しが必要な理由

```c
// ❌ 値渡し：関数の中で変えても呼び出し元に届かない
void parse(const char *line, SensorData out) { ... }

// ✅ ポインタ渡し：関数の中で変えると呼び出し元の変数が変わる
int parseSensorLine(const char *line, SensorData *out) { ... }
//                                                ↑
//                    呼び出し側は &data を渡す → out が data のアドレスを指す
```

### よくある間違い

| 間違い | 正しいコード |
|--------|------------|
| `%d` で float を出力 | `%.1f` を使う |
| `out->location` に `=` で代入 | `sscanf` か `strcpy` を使う |
| `sscanf` で char 配列に `&` をつける | 配列名はアドレスなので `&` 不要 |
| fopen 後に NULL チェックをしない | `if (fp == NULL) { return 1; }` を必ず書く |

---

## Pull Request の送り方

### 1. Fork する

画面右上の **「Fork」** ボタンをクリック → 自分のアカウントにリポジトリがコピーされる。

### 2. Clone する

Fork した**自分の**リポジトリの URL をコピーして実行：

```bash
git clone https://github.com/自分のユーザー名/kiso-prog2-11-0622.git
cd kiso-prog2-11-0622
```

### 3. ファイルを順に進めて Push する

```bash
git add .
git commit -m "演習完了"
git push origin main
```

### 4. Pull Request を出す

#### ① GitHub で自分の Fork ページを開く

`https://github.com/自分のユーザー名/kiso-prog2-11-0622`

#### ② 「Contribute」→「Open pull request」をクリック

#### ③ 設定を確認する（ここが間違いやすい）

```
base repository: yamashu00/kiso-prog2-11-0622   ← やましゅうのリポジトリ
base:            main
head repository: 自分のユーザー名/kiso-prog2-11-0622
compare:         main
```

#### ④ タイトルを自分の名前にする

```
タイトル欄: 山田太郎    ← 自分の名前（フルネーム）を入力
```

#### ⑤「Create pull request」をクリック
