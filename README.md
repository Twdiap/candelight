# CANDELIGHT
A dangerous and stupid IoT device that brings **light (and fire)** to your livingroom.

![](https://github.com/Twdiap/candelight/blob/401684eaa64b8484ce8360bf1a1483adcd3d3ae6/candelight_triplebuse.gif)
![](https://github.com/Twdiap/candelight/blob/5c5c1967fc67fba97c73a3a6e5a90c5af62afa38/candelight_small.gif)



**CANDELIGHT** is a wifi candle with a real flame.

The three versions are still in developement and if you feel the urge to improve security I NEED YOUR HELP.


The big one is called *Triple Buse*.

The small one is called *La flamme*.

The last one is meant to power old oil lamps and react to a double tap on the side of the device (it isn't wifi connected but feel free to add connectivity).


The heart of this project is a ESP8266 from Espressif and was originally made using Micropython but I quickly changed to Arduino IDE (for library management purposes).


To be clear you SHOULD NOT build this object yourself unless you're aware of security risks involving a flame AND wifi connectivity.


To build it you'll need:
  - 1 ESP8266 microcontroller
  - 1 SG90 with metal gears and with sufficient torque to press on the gas release
  - 1 spark igniter or a plasma generator (from electric lighters or else)
  - 1 BMS (like TP4050 or better) to power the candle with 18650 or lipo battery (min 800mAh to provide sufficent power to all components)
  - 1 relay or transistor to trigger the spark
  - 1 gas lighter or canister (you should use a gas lighter like a Clipper to reduce gas leak risks)
  - 1 3d printer nozzle .4 to .6 (for ventury effect to help the flame detach from the nozzle and keep it as cold as possible)
  - Anything that might help you build it.


Electronic schematics are on their way (for Triple Buse and Flamme only).
3D models are also on their way but need tweaking.



# DISCLAIMER

This project is provided "as is" without any warranties, express or implied.

**BY USING THIS CODE, YOU AGREE THAT:**

1. The author shall not be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services, loss of use, data, or profits, or business interruption) arising from the use of this code.

2. The user assumes full responsibility for the use of this code and its consequences.

3. This code is provided for educational and experimental purposes only. The author does not encourage or endorse any malicious or illegal use.

4. Users are responsible for checking compliance with local laws and regulations before any use.

5. The author reserves the right to modify or remove this project at any time without prior notice.

6. Any action you take upon the information provided in this repository is strictly at your own risk.

7. The author makes no representations or warranties regarding the accuracy, completeness, or reliability of this code.

**USE AT YOUR OWN RISK.**
