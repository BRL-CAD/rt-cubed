all:
	@echo 'Compiling everything...'
	make ois && make ogre && make mocha && make rbgui
	@echo 'Done compiling everything.'
ois:
	@echo 'Compiling OIS...'
	cd ois && ./bootstrap && ./configure && make -s && cd ..
	@echo 'Done compiling OIS.'
ogre:
	@echo 'Compiling Ogre...'
	cd ogre && ./bootstrap && ./configure --disable-ogre-demos && make -s && cd ..
	@echo 'Done compiling Ogre.'
mocha:
	@echo 'Compiling Mocha...'
	[ -d mocha/build -a -x mocha/build ] || mkdir mocha/build
	cd mocha/build && cmake .. && make && cd ../..
	@echo 'Done compiling Mocha.'
rbgui:
	@echo 'Compiling RBGui...'
	[ -d rbgui/build -a -x rbgui/build ] || mkdir rbgui/build
	cd rbgui/build && cmake ../Gui/ && make && cd ../..
	@echo 'Done compiling RBGui.'

install:
	make install-ois && make install-ogre && make install-mocha && make install-rbgui

install-ois:
	@echo 'Installing OIS...'
	make ois && cd ois && make install && cd ..
	@echo 'Done installing OIS.'
install-ogre:
	@echo 'Installing Ogre...'
	make ogre && cd ogre && make install && cd ..
	@echo 'Done installing Ogre.'
install-mocha:
	@echo 'Installing Mocha...'
	make mocha && cd mocha/build && make install && cd ../..
	@echo 'Done installing Mocha.'
install-rbgui:
	@echo 'Installing RBGui...'
	make rbgui && cd rbgui/build && make install && cd ../..
	@echo 'Done installing RBGui.'


.PHONY: all ois ogre mocha rbgui install install-ois install-ogre install-mocha install-rbgui
