#include <iostream>
#include <cmath>
#define DEBUG true
#define MAX_ALLOWED_HOUR 23
#define MIN_ALLOWED_HOUR 0
#define MAX_ALLOWED_MINUTE 59
#define MIN_ALLOWED_MINUTE 0
#define MAX_ALLOWED_TIMEZONE 12
#define MIN_ALLOWED_TIMEZONE -11

class Time
{
private:
    int hour, minute;
public:

    Time(int h=0, int m=0) {
        hour = h;
        minute = m;
        this->sanitize();
    }
    int getHour() const;
    int getMinute() const;
    void incrementHour();
    void incrementMinute();
    void decrementHour();
    void decrementMinute();
    void sanitize();
    void printSanitizerMessage(int oldVal, int newVal);
    void printTime() const;
    void setHour(int newHour, bool ignoreSanityCheck);
    void setMinute(int newMinute);

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

void Time::incrementHour(){
    this->hour++;
    this->sanitize();
}

void Time::incrementMinute(){
    this->minute++;
    this->sanitize();
}

void Time::decrementHour(){
    this->hour--;
    this->sanitize();
}

void Time::decrementMinute(){
    this->minute--;
    this->sanitize();
}

void Time::sanitize(){
    bool flagH, flagM = false;
    int hourModulo = MAX_ALLOWED_HOUR - MIN_ALLOWED_HOUR + 1;
    int minuteModulo = MAX_ALLOWED_MINUTE - MIN_ALLOWED_MINUTE + 1;

    // sanitize hour
    int oldHour = this->hour; // take snapshot before overwriting
    while(this->hour > MAX_ALLOWED_HOUR){
        this->hour -= hourModulo;
        if (DEBUG)
            flagH = true;
    }
    while(this->hour < MIN_ALLOWED_HOUR){
        this->hour += hourModulo;
        if (DEBUG)
            flagH = true;
    }
    if(flagH)
        printSanitizerMessage(oldHour, this->hour);

    // sanitize minute
    int oldMinute = this->minute; // take snapshot before overwriting
    while (this->minute > MAX_ALLOWED_MINUTE){
        this->minute -= minuteModulo;
        if (DEBUG)
            flagM = true;
    }
    while (this->minute < MIN_ALLOWED_MINUTE){
        this->minute += minuteModulo;
        if (DEBUG)
            flagM = true;
    }
    if(flagM)
        printSanitizerMessage(oldMinute, this->minute);
}

void Time::printSanitizerMessage(int oldVal, int newVal){
    std::cout << "Sanitized invalid value [" + std::to_string(oldVal) + "] to valid value [" + std::to_string(newVal) + "] ." << std::endl;
}

void Time::printTime() const{
    std::string timeStr = "";

    if(this->hour < 10)
        timeStr += "0" + std::to_string(this->hour);
    else
        timeStr += std::to_string(this->hour);

    timeStr += ":";

    if(this->minute < 10)
        timeStr += "0" + std::to_string(this->minute);
    else
        timeStr += std::to_string(this->minute);

    std::cout << timeStr << std::endl;
}

void Time::setHour(int newHour,  bool checkSanity=true){
    this->hour = newHour;
    if(checkSanity)
        this->sanitize();
}

void Time::setMinute(int newMinute){
    this->minute = newMinute;
    this->sanitize();
}


class TimeZone: public Time
{
private:
    int timeZone, absHour;
public:
    TimeZone(int tz=0, int h=0, int m=0);
    void calcAbsHour();
    void calcHour();
    void setTimeZone(int newTimeZone);
    int getTimeZone() const;
    int getAbsHour() const;
    void sanitizeTimezone();
    void printGMT() const;

};

TimeZone::TimeZone(int tz, int h, int m): Time(h, m), timeZone(tz){
    this->sanitizeTimezone();
    this->calcAbsHour();
};

void TimeZone::calcAbsHour(){
    this->absHour = this->getHour() - this->timeZone;
}

void TimeZone::calcHour(){
    this->setHour(this->absHour + this->timeZone, false);
}

void TimeZone::setTimeZone(int newTimeZone){
    this->timeZone = newTimeZone;
    this->sanitizeTimezone();
    this->calcHour();
}

int TimeZone::getTimeZone() const{
    return this->timeZone;
}

int TimeZone::getAbsHour() const{
    return this->absHour;
}

void TimeZone::sanitizeTimezone(){
    bool flag = false;
    int timeZoneModulo = MAX_ALLOWED_TIMEZONE - MIN_ALLOWED_TIMEZONE + 1;
    int oldTimezone = this->timeZone; // take snapshot before overwriting
    while(this->timeZone > MAX_ALLOWED_TIMEZONE){
        this->timeZone -= timeZoneModulo;
        if (DEBUG)
            flag = true;
    }
    while(this->timeZone < MIN_ALLOWED_TIMEZONE){
        this->timeZone += timeZoneModulo;
        if (DEBUG)
            flag = true;
    }
    if (flag)
        printSanitizerMessage(oldTimezone, this->timeZone);
}

void TimeZone::printGMT() const{
    std::string ttbp = ""; // text to be printed

    if(this->getAbsHour() < 10)
        ttbp += "0" + std::to_string(this->getAbsHour());
    else
        ttbp += std::to_string(this->getAbsHour());

    ttbp += ":";

    if(this->getMinute() < 10)
        ttbp += "0" + std::to_string(this->getMinute());
    else
        ttbp += std::to_string(this->getMinute());

    ttbp += " GMT";

    if(this->timeZone < 0){
        //ttbp += "-"; it already have an -
        ;
    }
    else{
        ttbp += "+";
    }
    if(abs(this->timeZone) < 10){
        ttbp += "0" + std::to_string(this->getTimeZone());
    }
    else{
        ttbp += std::to_string(this->getTimeZone());
    }

    ttbp += ":00";
    std::cout << ttbp << std::endl;
}



int main()
{
    // empty call
    Time mytimeEmpty;
    std::cout << "HOUR:" + std::to_string(mytimeEmpty.getHour()) << std::endl;
    std::cout << "MINUTE:" + std::to_string(mytimeEmpty.getMinute()) << std::endl;

//    // normal call
    Time mytime(0, 5);
    std::cout << "HOUR:" + std::to_string(mytime.getHour()) << std::endl;
    std::cout << "MINUTE:" + std::to_string(mytime.getMinute()) << std::endl;

    // derived call
    std::cout << "derived" << std:: endl;
    Time mytime2(mytime);
    std::cout << "HOUR:" + std::to_string(mytime2.getHour()) << std::endl;
    std::cout << "MINUTE:" + std::to_string(mytime2.getMinute()) << std::endl;

    mytime.incrementHour();
    std::cout << "HOUR:" + std::to_string(mytime.getHour()) << std::endl;
    std::cout << "MINUTE:" + std::to_string(mytime.getMinute()) << std::endl;

    mytime.decrementMinute();
    mytime.decrementHour();
    mytime.decrementHour();
    std::cout << "HOUR:" + std::to_string(mytime.getHour()) << std::endl;
    std::cout << "MINUTE:" + std::to_string(mytime.getMinute()) << std::endl;

    mytime.printTime();

    mytime.setHour(10); mytime.setMinute(70);
    mytime.printTime();

    std::cout << "TimeZone class" << std::endl;
    TimeZone mytimezone(3, 3, 5);
    mytimezone.printTime();

    mytimezone.setTimeZone(13);
    mytimezone.printTime();     // do not use it. formatting is terrible,
                                // but I will not fix it since i dont wanna modify base class anymore
                                // I will implement printGMT() instead
    mytimezone.printGMT();

    std::system("pause");
    return 0;
}
