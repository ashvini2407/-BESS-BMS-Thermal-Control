BESS BMS Thermal Control Simulator
Overview
             This C program simulates thermal management logic for Battery Energy Storage System (BESS).
It implements a state-machine based protection system as per UL1973/IEC62619 standards.

Features
           State Machine: COLD, NORMAL, WARM, HOT, CRITICAL states
           Safety: Automatic shutdown above 55°C, derate above 45°C
           Interactive: User can input temperature values to test all states
          Standards: Follows UL1973, IEC62619 thermal requirements
Temperature Limits
State	Temperature	Action
          COLD	< 0°C	Heater ON, Charge limit 30%
          NORMAL	0-35°C	Fan 20%, Full power
          WARM	35-45°C	Fan 60%, Full power
          HOT	45-55°C	Fan 100%, Derate 50%
          CRITICAL	> 55°C	System Shutdown
