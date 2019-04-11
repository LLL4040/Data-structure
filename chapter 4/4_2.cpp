# include "4_2.h"

void VehicleFerrySimulator();

int main()
{
    VehicleFerrySimulator();
    return 0;
}

void VehicleFerrySimulator()
{
    int car_minTime, car_maxTime, track_minTime, track_maxTime;
    int car_num, track_num;
    double car_avgTime, track_avgTime;

    cout << "**********车辆渡口管理模拟**********" << endl << endl;
    cout << "请输入客车到达时间间隔的上下限：";
    cin >> car_minTime >> car_maxTime;
    cout << "请输入货车到达时间间隔的上下限：";
    cin >> track_minTime >> track_maxTime;
    cout << "请输入客车的个数：";
    cin >> car_num;
    cout << "请输入货车的个数：";
    cin >> track_num;

    /* 客车和货车各自到达时间的队列 */
    seqQueue<int> carArrivalTime(car_num), trackArrivalTime(track_num);

    srand((unsigned)time(NULL));
    for (int i = 0; i < car_num; i++)
        carArrivalTime.enQueue(rand() % (car_maxTime - car_minTime + 1) + car_minTime);
    for (int i = 0; i < track_num; i++)
        trackArrivalTime.enQueue(rand() % (track_maxTime - track_minTime + 1) + track_minTime);

    int n = 1, num = 0;
    int car_sum = 0, track_sum = 0;
    int car_time = 0, track_time = 0;
    while (!carArrivalTime.isEmpty() || !trackArrivalTime.isEmpty())
    {
        num = 0;

        /* 先上客车 */
        while (!carArrivalTime.isEmpty() && num < 11)
        {
            if (carArrivalTime.getHead() + car_time > 10 * n) break;
            car_time += carArrivalTime.deQueue();
            car_sum += 10 * n - car_time;//累加等待时间 = 上船时间 - 到达时间
            num++;
            if ((num == 4 || num == 9) && trackArrivalTime.getHead() + track_time <= 10 * n)
            {
                track_time += trackArrivalTime.deQueue();
                track_sum += 10 * n - track_time;
                num++;
            }
        }

        /* 再上货车 */
        while (!trackArrivalTime.isEmpty() && num < 11)
        {
            if (trackArrivalTime.getHead() + track_time > 10 * n) break;
            track_time += trackArrivalTime.deQueue();
            track_sum += 10 * n - track_time;//累加等待时间 = 上船时间 - 到达时间
            num++;
        }

        n++;
    }

    car_avgTime = double(car_sum) / car_num;
    track_avgTime = double(track_sum) / track_num;

    cout << "客车平均等待时间为：" << car_avgTime << endl;
    cout << "货车平均等待时间为：" << track_avgTime << endl;
}