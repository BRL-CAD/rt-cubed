all:
	@echo 'Compiling everything...'
	$(MAKE_COMMAND) ois && $(MAKE_COMMAND) ogre && $(MAKE_COMMAND) mocha && $(MAKE_COMMAND) rbgui
	@echo 'Done compiling everything.'
ois:
	@echo 'Compiling OIS...'
	cd ois && ./bootstrap && ./configure CFLAGS="-I/usr/local/include" && $(MAKE_COMMAND) -s && cd ..
	@echo 'Done compiling OIS.'
ogre:
	@echo 'Compiling Ogre...'
	cd ogre && ./bootstrap && ./configure CFLAGS="-I/usr/local/include" LDFLAGS="-L/usr/local/lib" --disable-ogre-demos --disable-cg && $(MAKE_COMMAND) -s && cd ..
	@echo 'Done compiling Ogre.'
mocha:
	@echo 'Compiling Mocha...'
	[ -d mocha/build -a -x mocha/build ] || mkdir mocha/build
	cd mocha/build && cmake .. && $(MAKE_COMMAND) && cd ../..
	@echo 'Done compiling Mocha.'
rbgui:
	@echo 'Compiling RBGui...'
	[ -d rbgui/build -a -x rbgui/build ] || mkdir rbgui/build
	cd rbgui/build && cmake ../Gui/ && $(MAKE_COMMAND) && cd ../..
	@echo 'Done compiling RBGui.'

install:
	$(MAKE_COMMAND) install-ois && $(MAKE_COMMAND) install-ogre && $(MAKE_COMMAND) install-mocha && $(MAKE_COMMAND) install-rbgui

install-ois:
	@echo 'Installing OIS...'
	cd ois && $(MAKE_COMMAND) install && cd ..
	@echo 'Done installing OIS.'
install-ogre:
	@echo 'Installing Ogre...'
	cd ogre && $(MAKE_COMMAND) install && cd ..
	@echo 'Done installing Ogre.'
install-mocha:
	@echo 'Installing Mocha...'
	cd mocha/build && $(MAKE_COMMAND) install && cd ../..
	@echo 'Done installing Mocha.'
install-rbgui:
	@echo 'Installing RBGui...'
	cd rbgui/build && $(MAKE_COMMAND) install && cd ../..
	@echo 'Done installing RBGui.'


.PHONY: all ois ogre mocha rbgui install install-ois install-ogre install-mocha install-rbgui
