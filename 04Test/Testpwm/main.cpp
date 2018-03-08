#include <QCoreApplication>
#include "pwm.h"

const int pwmstep = 1;  // 舵机每次转动的delta角度
const int ctrlstep = 3;     //  手动控制时，每加一次或减一次，转动的角度

void getinput(char* input, int inputsize)
{
    memset(input, 0, inputsize);

    int inbit = 0;
    char ch;

    while ((ch=getchar())!='\n')
    {
        if (inbit<inputsize)
        {
            input[inbit] = ch;
            inbit++;
        }
    }

    return;
}

// 测试程序
int pwmtest()
{
    int ret = E_PWM_SUCCESS;

    ret = pwmInit();
    if (ret!=E_PWM_SUCCESS)
    {
        exit(0);
        return -1;
    }

    int initAngle = 90;

    PWMParam param;
    param.m_homeAngle = initAngle;
    param.m_stepAngle = pwmstep;
    pwmSetParam(param);

    pwmInitAngle();

//    pwmMoveToDestAngle(63);

    const int inputsize=5;
    char input[inputsize];

    int inputAngle = initAngle;

    bool running = true;

    while(running)
    {
        printf("Please enter '+'' or '-' to adjust angle, enter 'q' to quit :");
        getinput(input, inputsize);
        if (input[0]=='q')
        {
            running = false;
        }

        if (input[0]=='+')
        {
            inputAngle+=ctrlstep;
        }

        if (input[0]=='-')
        {
            inputAngle-=ctrlstep;
        }

        pwmMoveToDestAngle(inputAngle);

    }

    pwmUninit();

    exit(0);

    return 0;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    pwmtest();

    return a.exec();
}
