#ifndef F3D0AFE6_8B2E_44F5_92B9_3F941042C8A2
#define F3D0AFE6_8B2E_44F5_92B9_3F941042C8A2

#include <chrono>

class Timer
{
 private:
    using Clock  = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1> >;

    Clock::time_point m_beg{Clock::now()};

 public:
    void reset() { m_beg = Clock::now(); }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }

    long long elapsed_ms() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_beg).count();
    }

    long long elapsed_ns() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - m_beg).count();
    }

    std::string elapsed_ssms() const
    {
        auto dur = Clock::now() - m_beg;

        using seconds = std::chrono::seconds;
        using millis  = std::chrono::milliseconds;
        using nano    = std::chrono::nanoseconds;

        const auto s  = std::chrono::duration_cast<seconds>(dur);
        const auto ms = std::chrono::duration_cast<millis>(dur - s);
        const auto ns = std::chrono::duration_cast<nano>(dur - s - ms);

        return std::format("Time Elapsed: {:02}:{:02}:{:02}", s.count(), ms.count(), ns.count());
    }
};

#endif /* F3D0AFE6_8B2E_44F5_92B9_3F941042C8A2 */
