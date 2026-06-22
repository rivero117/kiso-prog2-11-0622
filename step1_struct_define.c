/* step1_struct_define.c — 構造体の定義と変数の作り方 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char  location[32];
    int   temperature;
    float humidity;
} SensorData;

int main(void) {
    /* メンバを1つずつ代入する方法 */
    SensorData data1;
    strcpy(data1.location, "教室");
    data1.temperature = 25;
    data1.humidity    = 60.5;

    /* まとめて初期化する方法 */
    SensorData data2 = {"廊下", 22, 55.0};
    SensorData data3 = {"食堂", 28, 70.0};

    printf("場所: %s / 気温: %d°C / 湿度: %.0f%%\n",
           data1.location, data1.temperature, data1.humidity);
    printf("場所: %s / 気温: %d°C / 湿度: %.0f%%\n",
           data2.location, data2.temperature, data2.humidity);
    printf("場所: %s / 気温: %d°C / 湿度: %.0f%%\n",
           data3.location, data3.temperature, data3.humidity);

    return 0;
}
