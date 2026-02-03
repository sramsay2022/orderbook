#ifndef F3D0AFE6_8B2E_44F5_92B9_3F941042C8A2
#define F3D0AFE6_8B2E_44F5_92B9_3F941042C8A2

#include <chrono>
#include <format>
#include <string>

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
        using namespace std::chrono;

        auto dur = Clock::now() - m_beg;

        const auto s  = duration_cast<seconds>(dur).count();
        const auto ms = (duration_cast<milliseconds>(dur) % 1000).count();
        const auto ns = (duration_cast<nanoseconds>(dur) % 1'000'000).count();

        return std::format("Elapsed: {}s {}ms {}ns", s, ms, ns);
    }
};

#endif /* F3D0AFE6_8B2E_44F5_92B9_3F941042C8A2 */
