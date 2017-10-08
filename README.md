# OpenJam2017

A simple VR shooter for the OpenJam 2017. Theme is "Leave a Mark". 
Works on both Oculus Rift & the Vive-

Made to test livestream and livecoding using the Opensource RunebergVR plugin and the "open code" UE4 engine.

In this series I will try to use mostly open source tools & assets or create one from scratch. This is not meant to be a sophisticated game but is meant for "open" education purposes.

1. Goal:
Shoot falling icospheres/targets using your laser eyes (ala Cyclops of the X-Men), use the trigger of either motion controller to fire a four beam laser to targets. Do this to prevent the icospheres from touching the Octa "Mark" (Octagonal cloud below you) which shrinks each time an icosphere hits it.

Survive until the end of the song "The Spectre" by Alan Walker (released copyright free) making sure you leave at least a portion of the Octa "Mark". If the entire mark is destroyed before the song ends, you lose the game.

Game will automatically restart in its current iteration after 3 seconds after you win or lose.

Have fun, challenge yourself to leave as big a mark as possible!

2. Tools used:
- Unreal Engine 4
- Runeberg VR Plugin 
- OBS - For livestreaming of all coding sessions
- Reaper
- Gimp
- Blender
- Audacity

3. Attributions:

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


4. Polish/Still left to do/known issues:

1. Laser scale at end is a bit off
2. Check in-editor warning for Gaze Broadcast Hit
3. Remove tick for C++ classes that dont need it
4. Dynamic shadows for targets (disable)
5. Rejig ATarget to be a SM Actor
