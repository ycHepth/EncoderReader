#include <iostream>
#include <unistd.h>
#include "EncoderReader.h"
#include <fstream>

int main() {

    std::ofstream Log;
    Log.open("log.csv", std::ios::out);


    int MultiRound = 1;
    float SingleRound = 0.2;

    int baseMultiRound = 0;
    float baseSingleRound = 0;

    int64_t baseCnt = 131072 * baseMultiRound + 131072 * baseSingleRound;

    int64_t cnt = (131072 * SingleRound + 131072 * MultiRound);

    EncoderReader encoderReader(baseCnt);

    encoderReader.update(cnt);

    printf("total round = %0.2f [round]\n", encoderReader.getTotalRound());
    printf("motor angle = %0.2f [rad]\n", encoderReader.getAngular());


    int64_t iter = 0;
    while (iter < 8000) {
        usleep(1000);

        cnt = 131072 * 1.2  + round(5000 * sin(2 * M_PI * 80 * iter++ / 1000));

        encoderReader.update(cnt);
        printf("total round = %0.2f [round]\n", encoderReader.getTotalRound());
        printf("motor angle = %0.2f [rad]\n", encoderReader.getAngular());

        Log << encoderReader.getTotalRound() << ',' << encoderReader.getAngular() << std::endl;

    }

    Log.close();

    return 0;
}
