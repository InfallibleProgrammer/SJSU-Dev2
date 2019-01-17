#pragma once
#include <cstdint>
#include "L0_LowLevel/LPC40xx.h"
#include "LPC40xx.h"

class TimerInterface {
 public:

  static LPC_TIM_TypeDef * tim_register;
  static LPC_SC_TypeDef * sc_ptr;
  static LPC_IOCON_TypeDef * iocon_register;
  enum class Mode : uint8_t { kcont = 0xb0, kreset = 0xb10, kstop = 0xb100 };
  Mode operator|(Mode left, Mode right) 
  {
    return static_cast<Mode>(static_cast<int>(left) | static_cast<int>(right));
  }
  enum class TimerPort : uint8_t
  {
    kTimer1 = 0,
    kTimer2 = 1,
    kTimer3 = 2,
    kTimer4 = 3
  }
  
    virtual void Initialize(TimerPort timer, const 32_t us_per_tick,
                            Mode current_mode);
  = 0;
  virtual void SetTimer(uint32_t timer);
  = 0;
  virtual uint32_t GetTimer(uint32_t timer) = 0;
}

class Timer : public TimerInterface {

 public:

  static constexpr uint8_t kTime0Mat0   = 0b011;
  static constexpr uint8_t kPrescaleMicro   = 48;



  enum class TimerPower : uint8_t
  {
    kTime0 = 1;
    kTime1 = 2;
    kTime3 = 22;
    kTime4 = 23;
  }
  static LPC_TIM_TypeDef* timer_peripherals[4];

  constexpr Timer() : timer_(&timer_pin_), timer_pin_(1, 28) {}
  // May not need this right now? ->
  explicit constexpr Timer(PinInterface * Timer_pin)
      : timer_(timer_pin), timer_pin_(Pin::CreateInactivePin())  // P1.28
  {
  }

  void Initalize(TimerPort timer, const 32_t us_per_tick,
                 Mode current_mode) override 
  {
    timer_port = static_cast<uint8_t>(timer);
    timer_peripherals[timer_port]
    // Power up Timer 0, 2, 3, and 4 (Not sure if 
    // all need to be started in initialize)
    sc_ptr->PCONP |= (1<<kTime0);
    // sc->PCONP |= (1<<kTime1);
    // sc->PCONP |= (1<<kTime2);
    // sc->PCONP |= (1<<kTime3);
    // Timer 0 Match Register 0
    timer_->SetPinFunction(kTime0Mat0);
    timer_->SetAsAnalogMode(true);
    timer_->SetMode(PinInterface::Mode::kInactive);
    // set Prescale register for Prescale Counter
    tim_register->PR |= (kPrescaleMicro << 0);

  }

  void SetTimer(uint32_t timer)
  {
    // enable interrupts on timer 0 match register 0 (Reset 0, Stop 0)
    tim_register->TIMER0 |= (1 << 0);

    // Set Timer by setting match register
    tim_register->MR0 |= (timer << 0)
  }

  uint32_t GetTimer(uint32_t timer)
  {

  }
   private:
   uint8_t timer_port;
   PinInterface * timer_;
   Pin timer_pin_;

}