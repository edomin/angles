#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
    private:
        double last_time;

    public:
        Timer();
        ~Timer();

        double update();
};

#endif // TIMER_HPP
