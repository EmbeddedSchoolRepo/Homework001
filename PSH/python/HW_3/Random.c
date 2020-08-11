/*
 * srand: 호출할 때 전달받는 인자를 기반으로 해서 난수를 초기화
 * rand: srand로 인해 생성된 값을 바탕으로 난수를 생성해줌
 * time: 인자값으로 NULL을 받으면 1970년 1월 1일 0시(UTC 타임존)이후부터
 *       현배까지 흐른 초수를 린턴해줌
 * 
 * 시간은 멈추지 않고 계속해서 흐르므로 time 함수로 구한 초 수를 기반으로 
 * srand함수를 이용하여 난수 기준값을 초기화 한다성, rand 함수를 호출하면 
 * 시간을 기반으로 한 진정한 무작위 숫자가 생성됨
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int random = rand() % 100;
    printf("%d", random);
    return 0;
}