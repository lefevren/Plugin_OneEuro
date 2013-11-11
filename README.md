OneEuro Plugin for CryEngine SDK
=====================================

One Euro Filter for CryEngine 3.5.4

Purpose of this plugin is to smooth noisy data. You should use this plugin when using Wiimote plugin, or anything else generating raw data such as VRPN trackers for example.

To see why One Euro filter : http://www.youtube.com/watch?v=ybZR4WRjkpM

This plugin can be found here : https://github.com/lefevren/Plugin_OneEuro

The content is a part of a larger project CryVR. Learn more here : https://github.com/lefevren/CryVR

Installation / Integration
==========================

Use the installer or extract the files to your CryEngine SDK Folder so that the Code and BinXX/Plugins directories match up.

The plugin manager will automatically load up the plugin when the game/editor is restarted or if you directly load it.


CVars / Commands
================
* ```CryVR_filters_euro_frequence```
  Filter Refresh rate

* ```CryVR_filters_euro_beta```
  Filter beta parameter

* ```CryVR_filters_euro_mincutoff```
  Filter min cut off parameter

* ```CryVR_filters_enable```
  Enable/Disable all filters

* ```CryVR_filters_euro_enable```
  Enable/Disable OneEuro filter


Flownodes
=========
OneEuro : After activation, just smooth noisy float input with given console variables values.
OneEuro2D : After activation, just smooth noisy Vec2 input with given console variables values.
OneEuroVec : After activation, just smooth noisy Vec3 input with given console variables values.
OneEuroQuat : After activation, just smooth noisy Quaternion input with given console variables values.





...
