#include <iostream>

class Time
{
private:
    int hour, minute;
public:

    Time(int h=0, int m=0) {
        hour = h;
        minute = m;
    }
    int getHour() const;
    int getMinute() const;
    void incrementHour();

    Time(Time &derivedTime){
        hour = derivedTime.getHour();
        minute = derivedTime.getMinute();
    };

};

int Time::getHour() const{
    return this->hour;
}

int Time::getMinute() const{
    return this->minute;
}

int main()
{
    // empty call
    Time mytimeEmpty;
    std::cout << "HOUR:" + std::to_string(mytimeEmpty.getHour()) << std::endl;
    std::cout << "MINUTE:" + std::to_string(mytimeEmpty.getMinute()) << std::endl;

//    // normal call
    Time mytime(3, 5);
    std::cout << "HOUR:" + std::to_string(mytime.getHour()) << std::endl;
    std::cout << "MINUTE:" + std::to_string(mytime.getMinute()) << std::endl;

    // normal call
    std::cout << "derived" << std:: endl;
    Time mytime2(mytime);
    std::cout << "HOUR:" + std::to_string(mytime2.getHour()) << std::endl;
    std::cout << "MINUTE:" + std::to_string(mytime2.getMinute()) << std::endl;

    std::system("pause");

    return 0;
}
