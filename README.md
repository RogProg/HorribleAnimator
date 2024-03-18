Wecome to Horrible Animator,..   the program for making horrible animations, fast.

HorribleAnimator is a RogProg (www.rogprog.com) project under GPL 3.0.

For any questions or feedback please e-mail to rogerkjode@hotmail.com

Horrible animator is written in c++, for Windows (sorry) using direct2d.

For mpeg4 compression it uses FFMpeg (https://ffmpeg.org/) under the LGPL lisense.




About the use of HorribleAnimator:


Start by selecting File->Open images and select the image files you want for the animation. Alpha channel images are reccomeded for figures.

To set background, select Scene->select background and select from the files you just loaded.

Drag and drop into the animation window (big cetre window) 

You can then adjust rotation and size by pulling the squares at an selected image.

Press rigth mouse button on image (visible part) to open menu.

To make que point select Set CuePoint or press * to set current cue point



Rememer to select Scene-> set endpoint or else playback will fail!


To make child/parent couplings rigth press on parent and select "select child" With cross mouse pointer then click at image to make child.
Theese will now be coupled.


To change image, rigth click and select change image, and select image,..
or simply rigth click at the browser to the left.



Keys:

Up and down selects prev/next cuepoint and left/rigth moves cuepoints one frame. Note a cuepoint cant overlap.

Del deletes current cuepoint

+/-  moves frames

Space starts/stops animation

* sets cuepoint

insert inserts frame

delete deletes frame (note: if a cuepoint exists at current frame no deletion is done)