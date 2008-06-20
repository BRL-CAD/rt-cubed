all: ogre ois mocha rbgui

ogre:
	echo 'Type: cd ogre; ./bootstrap && ./configure && make -s && su -c "make -s install"; cd ..'
ois:
	echo 'Type: cd ois; ./bootstrap && ./configure && make -s && su -c "make -s install"; cd ..'
mocha:
	echo 'Type: cd mocha; scons && cp libmocha.{a,so} /usr/local/lib && ldconfig && cp ../Mocha.pc /usr/local/lib/pkgconfig; cd ..'
rbgui:
	echo 'Type: mkdir rbgui/build; cd rbgui/build; cmake ../Gui/ && make -s && su -c "make -s install"; cd ../..'
