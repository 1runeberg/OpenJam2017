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

3. Tools used:
- Unreal Engine 4
- Runeberg VR Plugin 
- OBS - For livestreaming of all coding sessions
- Reaper
- Gimp
- Blender
- Audacity

4. Attributions:

Music:
Alan Walker, The Spectre (released copyright free)

Sky: https://www.flickr.com/photos/ericrumor07/3569830070/in/photolist-6rsj7j-jJdCQt-9iiHX4-nLxi8s-oD5GU7-49Jtfj-bBx5ko-bm9mMU-d39S15-6xsWLV-btqpSW-8C8SnW-p4UqA4-qhEpUk-5dGxWi-ohnET-T8sx28-fctuMQ-8Wernb-fW7Zvg-8Qj6qE-6Wv3HC-nP7nBX-c3cxdQ-5ydX2z-rvUC1L-71wUXE-4GFfP7-fK9heX-qJHvGe-avsqJd-dBNPGe-EFv6o-iArNEu-aW7hvi-dHo5qe-jbSc4f-gPew8R-pJPpcy-tXVf3-cSyiTS-bmdEV-A65wch-kVoG1b-7xiQQz-ec4CuS-qW7Yop-ftegba-DK1Sah-e5T1WT

Laser sound:
https://freesound.org/people/jeremysykes/sounds/344513/

Laser impact:
https://freesound.org/people/211redman112/sounds/234082/

Win sound:
https://freesound.org/people/Mativve/sounds/391539/

Lose sound:
https://freesound.org/people/josepharaoh99/sounds/364929/


5. Polish/Still left to do/known issues:

1. Laser scale at end is a bit off
2. Check in-editor warning for Gaze Broadcast Hit
3. Remove tick for C++ classes that dont need it
4. Dynamic shadows for targets (disable)
5. Rejig ATarget to be a SM Actor


