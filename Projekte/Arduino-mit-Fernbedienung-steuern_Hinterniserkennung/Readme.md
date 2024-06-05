# Control Arduino with remote control & obstacle detection
My goal is to build and program a robot that can be controlled by a remote control. I am also working on an all-round obstacle detection system.
### Remote control numbers

| Button | Value | Variable | Command |
| ------ | ------ | ------ | ------ |
|     On/Off    |  3125149440        |        |        |
|     Mode      |  3108437760        |        |        |
|     Mute      |  3091726080        |        |        |
|     Play      |  3141861120        |        |        |
|     Previous  |  3208707840        |        |        |
|     Next      |  3158572800          |        |        |
|     EQ        |  4161273600            |        |        |
|     Quieter   |  3927310080       |        |        |
|     Louder    |  4127850240        |        |        |
|     0         |  3910598400              |       |        |
|     ?         |  3860463360              |       |        |
|     U/SD SCAN |  4061003520      |        |        |
|     1         |  4077715200                  |        |        |
|     2         |  3877175040      |        |        |
|     3         |  2707357440      |        |        |
|     4         |  4144561920      |        |        |
|     5         |  3810328320      |        |        |
|     6         |  2774204160      |        |        |
|     7         |  3175284480      |        |        |
|     8         |  2907897600      |        |        |
|     9         |  3041591040      |        |        |


### Needed pins

| Pin | Status | Usecase | 
| ------ | ------ | ------ |
|     1    |  free        | -       | 
|     2    |  used        | LED Status lamp       | 
|     3    |  used        | ECHO       | 
|     4    |  used        | Transmitting (SENDEN)       | 
|     5    |  free        | -       | 
|     6    |  used        | motor left 1       | 
|     7    |  used        | motor left 2       | 
|     8    |  free        | -       | 
|     9    |  used        | motor right 1       | 
|     10   |  used        | motor right 2       | 
|     11   |  used        | -       | 
|     12   |  free        | -       | 
|     13   |  free        | -       | 
