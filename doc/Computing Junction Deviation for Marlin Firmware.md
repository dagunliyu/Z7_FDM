### Computing Junction Deviation for Marlin Firmware

https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html

As part of developing my own 3D printer firmware, I also keep an eye on what is happening in other firmware. One feature that is causing confusion in the Marlin community is the junction deviation setting. Up until recently, Marlin used the jerk method (hence forth referred to as "archaic jerk") it inherited from Grbl for computing corning speed (junction velocity). With the option now in Marlin to use junction deviation instead of jerk, there are many people who want to know what are good settings for junction deviation to insure they get reasonable movement while printing. In this post I will give an equation for converting the jerk values into junction deviation and my derivation of this equation.

I will not rehash what junction deviation is in this post, so anyone interested in learning more about it should refer to these two links:

https://onehossshay.wordpress.com/2011/09/24/improving_grbl_cornering_algorithm/

https://reprap.org/forum/read.php?1,739819

For those who are only here for the end results, here is the equation to compute junction deviation:

[![d=0.4\frac{Jerk^{2}}{Acceleration_{printing}}](https://latex.codecogs.com/gif.latex?d=0.4\frac{Jerk^{2}}{Accel_{printing}})](https://www.codecogs.com/eqnedit.php?latex=d=0.4\frac{Jerk^{2}}{Accel_{printing}})

A typical Cartesian machine might have a jerk setting of 9mm/s and a printing acceleration of 1500mm/s^2. Plugging these numbers into the above equation goes like this:

[![0.4*9*9/1500=0.022](https://latex.codecogs.com/gif.latex?0.4*9*9/1500=0.022)](https://www.codecogs.com/eqnedit.php?latex=0.4*9*9/1500=0.022)

So for this example the junction deviation would be set to 0.022 and the configuration_adv.h file would look like this:

//
// Use Junction Deviation instead of traditional Jerk Limiting
//
\#define JUNCTION_DEVIATION
\#if ENABLED(JUNCTION_DEVIATION) 
 \#define JUNCTION_DEVIATION_MM 0.022 // (mm) distance from real junction edge
\#endif

The smaller the junction deviation number, the more the machine will slow down when encountering corners. Making this number too small may slow down the print speed and cause over extrusion in the corners. Making the number larger will increase the speed at which the machine traverses corners. Setting this number too high may cause vibrations in the mechanism that produce ringing in the print surface or in extreme cases a stepper motor to loose position.

If you only came here for the basic equation, you do not need to read any further. For those who would like to learn where the above equation came from, keep on reading.

To setup this problem, we are going to imagine a situation where the printer traverses two moves that are at right angles to each other:

[![img](https://1.bp.blogspot.com/-_1P1ovm-Ei4/W7-Zsy93o-I/AAAAAAAA2kA/OFPoHSa_Hv8SDWJPObKF4tkgIDgH_R_5ACPcBGAYYCw/s1600/Corner%2BMove.JPG)](https://1.bp.blogspot.com/-_1P1ovm-Ei4/W7-Zsy93o-I/AAAAAAAA2kA/OFPoHSa_Hv8SDWJPObKF4tkgIDgH_R_5ACPcBGAYYCw/s1600/Corner%2BMove.JPG)

This is a convenient situation as it is the case where one axis suddenly stops moving, and the other axis suddenly starts moving. When using the archaic jerk functionality the first axis will decelerate down to the the jerk velocity in the corner and then instantly stop, at the same moment the second axis will suddenly jump up to the jerk velocity in its direction and accelerate back up to printing speed. To simplify this, we can say that with a 90 degree corner, the junction velocity is the same as the jerk setting. (note: this is not the case for any junction that is not 90 deg).

Next we can take that same corner move and add the virtual arc that junction deviation uses to compute the junction velocity:

[![img](https://3.bp.blogspot.com/-n0XseZZP9MA/W7-gJw1nhLI/AAAAAAAA2kM/n8AXWhq6USYZ6sTbfbPw5gIiuac5L-csgCLcBGAs/s1600/Corner%2BMove%2Bwith%2BArc.JPG)](https://3.bp.blogspot.com/-n0XseZZP9MA/W7-gJw1nhLI/AAAAAAAA2kM/n8AXWhq6USYZ6sTbfbPw5gIiuac5L-csgCLcBGAs/s1600/Corner%2BMove%2Bwith%2BArc.JPG)

In the above picture **d** represents the junction deviation and **R** is the radius of the virtual arc.

Using the Pythagorean theorem and a little algebra and we get this relationship between **R** and **d**:

[![\left ( R+d \right )^{2}=R^{2}+R^{2}](https://latex.codecogs.com/gif.latex?\left&space;(&space;R+d&space;\right&space;)^{2}=R^{2}+R^{2})](https://www.codecogs.com/eqnedit.php?latex=\left&space;(&space;R+d&space;\right&space;)^{2}=R^{2}+R^{2})

[![d=\sqrt{2*R^{2}}-R](https://latex.codecogs.com/gif.latex?d=\sqrt{2*R^{2}}-R)](https://www.codecogs.com/eqnedit.php?latex=d=\sqrt{2*R^{2}}-R)

[![d=\left ( \sqrt{2}-1 \right )*R](https://latex.codecogs.com/gif.latex?d=\left&space;(&space;\sqrt{2}-1&space;\right&space;)*R)](https://www.codecogs.com/eqnedit.php?latex=d=\left&space;(&space;\sqrt{2}-1&space;\right&space;)*R)

[![d\approx 0.4*R](https://latex.codecogs.com/gif.latex?d\approx&space;0.4*R)](https://www.codecogs.com/eqnedit.php?latex=d\approx&space;0.4*R)      (1)

Next we take the equation for radial acceleration and solve for the radius:



[![A_{radial}=\frac{V^{2}}{R}](https://latex.codecogs.com/gif.latex?A_{radial}=\frac{V^{2}}{R})](https://www.codecogs.com/eqnedit.php?latex=A_{radial}=\frac{V^{2}}{R})

[![R=\frac{V^{2}}{A_{radial}}](https://latex.codecogs.com/gif.latex?R=\frac{V^{2}}{A_{radial}})](https://www.codecogs.com/eqnedit.php?latex=R=\frac{V^{2}}{A_{radial}})    (2)


If we combine equations 1 and 2 above we find the following:



[![d\approx 0.4\frac{V^{2}}{A_{radial}}](https://latex.codecogs.com/gif.latex?d\approx&space;0.4\frac{V^{2}}{A_{radial}})](https://www.codecogs.com/eqnedit.php?latex=d\approx&space;0.4\frac{V^{2}}{A_{radial}})


In this situation, the radial acceleration is the same as the printing acceleration and the junction velocity is the same as the archaic jerk setting. Substituting these in, we get the final equation:



[![d=0.4\frac{Jerk^{2}}{Acceleration_{printing}}](https://latex.codecogs.com/gif.latex?d=0.4\frac{Jerk^{2}}{Accel_{printing}})](https://www.codecogs.com/eqnedit.php?latex=d=0.4\frac{Jerk^{2}}{Accel_{printing}})


Using this equation will allow someone who is migrating from the archaic jerk to junction deviation to start with settings that are very close to each other without excessive experimentation or testing.

Please let me know if you have any questions.

Phillip



***\*LABELS:\** [3D PRINT](https://blog.kyneticcnc.com/search/label/3D print) [JERK](https://blog.kyneticcnc.com/search/label/jerk) [JUNCTION DEVIATION](https://blog.kyneticcnc.com/search/label/junction deviation) [MARLIN](https://blog.kyneticcnc.com/search/label/marlin) [MARLIN FIRMWARE](https://blog.kyneticcnc.com/search/label/marlin firmware)**

SHARE



### Comments

1. ![img](https://www.blogger.com/img/blogger_logo_round_35.png)

   [Kento](https://www.blogger.com/profile/17872347066798931862)*[May 28, 2019 at 12:26 AM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1559028374009#c5325420488523878703)*

   Wow that singular diagram of what Junction Deviation is makes the whole thing make so much more sense.

   **REPLY**

   

   

2. ![img](https://www.blogger.com/img/blogger_logo_round_35.png)

   [Unknown](https://www.blogger.com/profile/08138775061609371348)*[November 25, 2019 at 11:17 PM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1574752675709#c1532696705348114168)*

   Thank you Phillip

   **REPLY**

   

   

3. ![img](https://www.blogger.com/img/blogger_logo_round_35.png)

   [İbrahim N](https://www.blogger.com/profile/03108059099641157843)*[February 8, 2020 at 4:15 AM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1581164104161#c1470905994327529386)*

   
   Thanks Philip. Perfect explanation

   **REPLY**

   

   

4. ![img](https://www.blogger.com/img/blogger_logo_round_35.png)

   [Unknown](https://www.blogger.com/profile/02431068404317424106)*[April 3, 2020 at 8:33 AM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1585928036142#c1410007707304475051)*

   Great work. If I can give some constructive feedback, you probably shouldn't call jerk a velocity.. it really isn't. At least if correctly implemented in the firmware, it would be a limit to the change in acceleration over the change in time in mm/sec^3. Calling it a velocity isn't really right, its a bound on how quickly you can change acceleration (not how quickly you can accelerate).

   **REPLY**

   

   1. ![img](https://www.blogger.com/img/blogger_logo_round_35.png)

      [Phillip](https://www.blogger.com/profile/08394194635600733975)*[May 26, 2020 at 9:12 AM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1590509566843#c8522059652559480417)*

      In Marlin, the units for jerk are mm/s, as such it is a velocity. In my opinion Marlin abuses the term Jerk as it is not the same as classic kinematic jerk (rate of change of acceleration). In Marlin, jerk is used to limit the rate of change of velocity when starting, stopping or changing direction.

      

      

      

   

5. ![img](https://www.blogger.com/img/blogger_logo_round_35.png)

   [Unknown](https://www.blogger.com/profile/03607171380618848024)*[November 23, 2020 at 10:39 PM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1606199947174#c7991740782821625372)*

   Great explanation. What would the G-code be to define a custom junction deviation in your start code?

   **REPLY**

   

   1. ![img](https://www.blogger.com/img/blogger_logo_round_35.png)

      [Phillip](https://www.blogger.com/profile/08394194635600733975)*[November 23, 2020 at 11:34 PM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1606203269221#c4517916643745503703)*

      https://marlinfw.org/docs/gcode/M205.html

      M205 J0.022

      

      

      

   

6. ![img](https://3.bp.blogspot.com/-f_K_XUEXZ1w/TyIwp2W7CII/AAAAAAAAACQ/TYwZACT4u8M/s35/face.jpg)

   [Yair Herrera Music](https://www.blogger.com/profile/08297733805178602805)*[December 12, 2020 at 10:59 AM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1607799548621#c817249712746855937)*

   Hi, how does one find out if JD is active or not? Thanks

   **REPLY**

   

   

7. ![img](https://www.blogger.com/img/blogger_logo_round_35.png)

   [Unknown](https://www.blogger.com/profile/08684289998389786024)*[March 23, 2021 at 8:15 AM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1616512508755#c4911346252909514270)*

   Quick question. The jerk setting can be done in the firmware. On the acceleration spped, are you refering tonthe slicer setting or the max accel setting in the firmware?

   **REPLY**

   

   

8. ![img](https://www.blogger.com/img/blogger_logo_round_35.png)

   [Unknown](https://www.blogger.com/profile/16683418694142224848)*[March 27, 2021 at 8:56 AM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1616860595888#c1529066069271199665)*

   Thank you very much for this information, it's always fascinating to see how these firmware implementations affect print quality. I know it may have been a while since you've been back to this post, but theoretically since we have this equation with variables of known value we can solve this to find the Jerk setting. However, since Jerk would be commented out to allow for use of Juction Deviation how can it be used in the equation to find Junction Deviation? Since its not a set or known value that we give to the printer, the actual Junction Deviation value cannot be calculated unless there is some hidden Jerk setting that we need to find, otherwise we just arbitrarily define the value in the firmware. Am I missing something or is the equation somewhat misleading, and rather we actually need to do (like with Linear Advance) calibration tests to find the best range of values for Junction Deviation?

   **REPLY**

   

   1. ![img](https://www.blogger.com/img/blogger_logo_round_35.png)

      [Phillip](https://www.blogger.com/profile/08394194635600733975)*[March 27, 2021 at 9:07 AM](https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html?showComment=1616861247934#c5319070680720256621)*

      This equation was intended to help people transitioning from known good jerk settings to JD. Regardless of how you get your starting number, real world test prints are the best way to determine the "right" final value.

      

      

      

   





#### Post a Comment