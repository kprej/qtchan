qtchan is a 4chan browser written with qt5.\
I started developing it because browsers suck.\
There's still a lot to do.


# Features
* browse and post on 4chan
* auto update threads and auto download original file
* download all media as original filename
* tree style tabs and save state (./session.txt)
* open files in OS's default application
* search and filter


## a few keyboard commands and instructions
* ctrl+l opens up the nav bar; you can type g or g/boardnum or /g/ or https://boards.4chan... etc
* ctrl+w (ctrl+f4 on windows) or delete to close tab
* ctrl+p opens settings-ctrl+tab ctrl+shift+tab, ctrl+1-4 to switch tabs
* ctrl+f to search and filter
* r manually refreshes thread
* q opens up post form, shift+enter to post from there
* e expands all images and auto expands future posts on current tab
* f10 saves tree state (it'll also save on exit)
* f11 hides menubar
* j and k scroll (opposite of standard vim)
* o opens image at top of view
* if you have mpv, g opens all the images/videos in the thread.

there are more shortcuts; look at the source for now for info.

need to restart qtchan if changing to use 4chan pass or not. signals/slots still not finished for that.

## Using 4chan pass to post
Create a file ~/.config/qtchan/settings like below. Look at your browser cookies for values.
Open settings with Ctrl+P and check Use 4chan pass.
```
4chan_pass:your_4chanpass
pass_id:your_pass_id
pass_enabled:1
```

![qtchan ss](https://i.abcdn.co/qtchan.png)

## TODO
### MAJOR
* unread, read, (You) display
* notifications
* instructions

### MINOR
* show loading state
* search/filter by different post fields (right now combo of sub and com)
* more settings
* themes
