# OpenJam2017

A simple VR wave shooter for the OpenJam 2017. Theme is "Leave a Mark".

Made to test livestream and livecoding using hte Opensource RunebergVR plugin and the "open code" UE4 engine.

In this series I will try to use mostly open source tools & assets or create one from scratch. This is nto meant to be a sphisticated game but is meant for "open" education purposes.

1. Goal:
Shoot waves of targets which could either be benign or dangerous, player needs to "mark" them first via a continous gaze to see what's inside them and then destroying ones that are dangerous via a four laser beam sequence.

Win condition: 
Stay alive until the end of song "The Spectre" (3:26) from ALan Walker which was made "copyright free" recently.

Lose condition:
Get hit x number of times

2. Shooting Mechanic:
Gaze shooting, one hand near the headset "marks" a target and when both hands are near the headset we fire four laser beams on the corners of the VR camera.

3. TODO:

a. Create an actor that will act as a target
    - Expose scale
b. Enable gaze component in the project
    - Expose SMC for BP
c. Laser mechanic
d. Life marker/indicator
e. Level blocking / Use splines for the path of the target "waves"
f. Coding / troubleshooting / polishing
g. Dressing up
