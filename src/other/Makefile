all: ois ogre mocha rbgui
	@echo 'Compiling everything...'
ois:
	@echo 'Compiling OIS...'
	cd ois && ./bootstrap && ./configure && make -s; cd ..
	@echo 'Done compiling OIS.'
ogre:
	@echo 'Compiling Ogre...'
	cd ogre && ./bootstrap && ./configure --disable-ogre-demos && make -s; cd ..
	@echo 'Done compiling Ogre.'
mocha:
	@echo 'Compiling Mocha...'
	[ -d mocha/build -a -x mocha/build ] || mkdir mocha/build
	cd mocha/build && cmake .. && make; cd ../..
	@echo 'Done compiling Mocha.'
rbgui:
	@echo 'Compiling RBGui...'
	[ -d rbgui/build -a -x rbgui/build ] || mkdir rbgui/build
	cd rbgui/build && cmake ../Gui/ && make; cd ../..
	@echo 'Done compiling RBGui.'

install: install-ois install-ogre install-mocha install-rbgui

install-ois: ois
	@echo 'Installing OIS...'
	cd ois && make install;	cd ..
	@echo 'Done installing OIS.'
install-ogre: ogre
	@echo 'Installing Ogre...'
	cd ogre && make install; cd ..
	@echo 'Done installing Ogre.'
install-mocha: mocha
	@echo 'Installing Mocha...'
	cd mocha/build && make install; cd ../..
	@echo 'Done installing Mocha.'
install-rbgui: rbgui
	@echo 'Installing RBGui...'
	cd rbgui/build && make install; cd ../..
	@echo 'Done installing RBGui.'


.PHONY: ois ogre mocha rbgui
