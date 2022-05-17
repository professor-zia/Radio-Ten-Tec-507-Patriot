uint32_t TimerOverFlow(uint32_t currentTime)
{
  return (currentTime + CORE_TICK_RATE * (1)); //the Core Tick Rate is 1ms
}
