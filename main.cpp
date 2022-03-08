#include <iostream>
#include "EncoderReader.h"

int main() {

    int MultiRound = 0;
    float SingleRound = 0.1;

    int64_t cnt = 131072 * SingleRound + 131072 * MultiRound;

    EncoderReader encoderReader;

    encoderReader.read(cnt);

    printf("single cnt = %d\n", encoderReader.getSingleData());
    printf("multi cnt = %d\n", encoderReader.getMultiData());

    printf("total round = %0.2f [round]\n", encoderReader.getTotalRound());
    printf("motorAngular = %0.2f [rad]\n", encoderReader.getAngular());


    float GearRatio = 80;

    EncoderReader encoderReader1(GearRatio);
    encoderReader1.read(cnt);

    printf("output round = %0.3f [round]\n", encoderReader1.getOutputRound());
    printf("output Angular = %0.3f [rad]\n", encoderReader1.getOutputAngular());

    return 0;
}
