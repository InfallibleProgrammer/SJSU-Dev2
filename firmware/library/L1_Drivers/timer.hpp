#include <cstdint>=
#include "L0_LowLevel/LPC40xx.h"
#include "LPC40xx.hpp"

class TimerInterface {
 public:
  enum class Mode : uint8_t { kcont = 0x0, kreset = 0x1, kstop = 0x2 };
  Mode operator|(Mode left, Mode right) 
  {
    return static_cast<Mode>(static_cast<int>(left) | static_cast<int>(right));
  }
  enum class TimerPort : uint8_t
  {
    Timer1 = 0,
    Timer2 = 1,
    Timer3 = 2,
    Timer4 = 3
  }
  
    virtual void Initialize(TimerPort timer, const 32_t us_per_tick,
                            Mode current_mode);
  = 0;
  virtual void SetTimer(uint32_t timer);
  = 0;
  virtual uint32_t GetTimer(uint32_t timer) = 0;
}

class Timer : public TimerInterface {
 private:
  uint8_t timer_port;

 public:
  static LPC_TIM_TypeDef* timer_peripherals[4];

  void Initalize(TimerPort timer, const 32_t us_per_tick,
                 Mode current_mode) override {
    timer_port = static_cast<uint8_t>(timer);
    timer_peripherals[timer_port]
  }
}