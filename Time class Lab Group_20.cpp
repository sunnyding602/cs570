//
//  main.cpp
//  570_lab_week4
//
//  Created by sunny on 9/25/15.
//  Copyright © 2015 bunengzhai. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

class Time{
    private:
    int hour, minutes = 0;
    double seconds = 0.0;
    
    
    public:
    Time(int hour, int minutes){
        this->hour = hour;
        this->minutes = minutes;
    }
    
    Time(int hour, int minutes, double seconds){
        this->hour = hour;
        this->minutes = minutes;
        this->seconds = seconds;
    }
    
    int get_hour(){
        return this->hour;
    }
    
    int get_minutes(){
        return this->minutes;
    }
    
    double get_seconds(){
        return this->seconds;
    }
    
    friend ostream& operator<<(ostream &out, Time &t);
};

ostream& operator<<(ostream &out, Time &t)
{
    out << "["<< t.get_hour() << ":"<< t.minutes <<  ":"<< t.seconds <<"]";
    return out;
}

class TimeSpan{
    
private:
    int hours=0, minutes=0;
    double seconds = 0.0;
    double hours_fraction, minutes_fraction, seconds_fraction;
   
public:
    TimeSpan(double seconds){
        this->hours_fraction = seconds/3600;
        this->minutes_fraction = seconds/60;
        this->seconds_fraction = seconds;
        
        this->hours = static_cast<int>(seconds)/3600;
        seconds = seconds - this->hours * 3600;
        this->minutes = static_cast<int>(seconds)/60;
        seconds = seconds - this->minutes*60;
        this->seconds = seconds;
    }
    
    TimeSpan(float seconds){
    }
    
    TimeSpan(int seconds){
    }
    
    int get_hours(){
        return this->hours_fraction;
    }
    
    int get_minutes(){
        return this->minutes_fraction;
    }
    
    double get_seconds(){
        return this->seconds_fraction;
    }

    friend ostream& operator<<(ostream &out, TimeSpan &ts);
};

ostream& operator<<(ostream &out, TimeSpan &ts)
{
    out << "["<< ts.hours << ":"<< ts.minutes <<  ":"<< ts.seconds <<"]";
    return out;
}


Time operator+(Time t, TimeSpan ts)
{
    int hour=0, minutes=0;
    double seconds=0.0;
    double totalSeconds = 0;
    totalSeconds = t.get_hour() * 3600  + t.get_minutes() * 60 + t.get_seconds() + ts.get_seconds();
    
    hour = static_cast<int>(totalSeconds)/3600;
    totalSeconds = totalSeconds - hour * 3600;
    
    minutes = static_cast<int>(totalSeconds)/60;
    totalSeconds = totalSeconds - minutes * 60;
    seconds = totalSeconds;
    
    Time time(hour, minutes, seconds);
    return time;
}

Time operator+( TimeSpan ts, Time t)
{
    int hour=0, minutes=0;
    double seconds=0.0;
    double totalSeconds = 0;
    totalSeconds = t.get_hour() * 3600  + t.get_minutes() * 60 + t.get_seconds() + ts.get_seconds();
    
    hour = static_cast<int>(totalSeconds)/3600;
    totalSeconds = totalSeconds - hour * 3600;
    
    minutes = static_cast<int>(totalSeconds)/60;
    totalSeconds = totalSeconds - minutes * 60;
    seconds = totalSeconds;
    
    Time time(hour, minutes, seconds);
    return time;
}

TimeSpan operator+(TimeSpan ts1, TimeSpan ts2){
    return TimeSpan(ts1.get_seconds() + ts2.get_seconds()) ;
}


int main(int argc, const char * argv[]) {

    Time t1(12, 30);
    // output time
    cout << t1 <<endl;
    
    //output timespan
    TimeSpan ts1(65.5);
    cout << ts1 <<endl;
    
    // time plus timespan
    Time t3 = t1 + ts1;
    cout << t3 <<endl;
    
    // timespan plus time
    Time t4 = ts1 +t1;
    cout << t4 <<endl;
    
    //timespan plus timespan
    TimeSpan ts2 = ts1 + ts1;
    cout << ts2<<endl;
    return 0;
}
