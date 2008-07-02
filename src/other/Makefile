all:
	@echo 'Type: make ogre|ois|mocha|rbgui (roughly in that order, at least mocha before rbgui)'
ogre:
	@echo 'Type: cd ogre; ./bootstrap && ./configure && make -s && su -c "make -s install"; cd ..'
ois:
	@echo 'Type: cd ois; ./bootstrap && ./configure && make -s && su -c "make -s install"; cd ..'
mocha:
	@echo 'Compiling Mocha...'
	[ -d mocha/build -a -x mocha/build ] || mkdir mocha/build
	cd mocha/build && cmake .. && make; cd ../..
rbgui:
	@echo 'Compiling RBGui...'
	[ -d rbgui/build -a -x rbgui/build ] || mkdir rbgui/build
	cd rbgui/build && cmake ../Gui/ && make; cd ../..

install: install-ois install-ogre install-mocha install-rbgui

install-ois: ois
	@echo 'Installing OIS...'
	#cd mocha/build && make install; cd ../..

install-ogre: ogre
	@echo 'Installing Ogre...'
	#cd rbgui/build && make install; cd ../..

install-mocha: mocha
	@echo 'Installing Mocha...'
	cd mocha/build && make install; cd ../..

install-rbgui: rbgui
	@echo 'Installing RBGui...'
	cd rbgui/build && make install; cd ../..


.PHONY: ogre ois rbgui mocha
