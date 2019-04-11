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

    cout << "**********�����ɿڹ���ģ��**********" << endl << endl;
    cout << "������ͳ�����ʱ�����������ޣ�";
    cin >> car_minTime >> car_maxTime;
    cout << "�������������ʱ�����������ޣ�";
    cin >> track_minTime >> track_maxTime;
    cout << "������ͳ��ĸ�����";
    cin >> car_num;
    cout << "����������ĸ�����";
    cin >> track_num;

    /* �ͳ��ͻ������Ե���ʱ��Ķ��� */
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

        /* ���Ͽͳ� */
        while (!carArrivalTime.isEmpty() && num < 11)
        {
            if (carArrivalTime.getHead() + car_time > 10 * n) break;
            car_time += carArrivalTime.deQueue();
            car_sum += 10 * n - car_time;//�ۼӵȴ�ʱ�� = �ϴ�ʱ�� - ����ʱ��
            num++;
            if ((num == 4 || num == 9) && trackArrivalTime.getHead() + track_time <= 10 * n)
            {
                track_time += trackArrivalTime.deQueue();
                track_sum += 10 * n - track_time;
                num++;
            }
        }

        /* ���ϻ��� */
        while (!trackArrivalTime.isEmpty() && num < 11)
        {
            if (trackArrivalTime.getHead() + track_time > 10 * n) break;
            track_time += trackArrivalTime.deQueue();
            track_sum += 10 * n - track_time;//�ۼӵȴ�ʱ�� = �ϴ�ʱ�� - ����ʱ��
            num++;
        }

        n++;
    }

    car_avgTime = double(car_sum) / car_num;
    track_avgTime = double(track_sum) / track_num;

    cout << "�ͳ�ƽ���ȴ�ʱ��Ϊ��" << car_avgTime << endl;
    cout << "����ƽ���ȴ�ʱ��Ϊ��" << track_avgTime << endl;
}