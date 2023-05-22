FOLDER := $(shell basename $(CURDIR))
BLASTEM := $(HOME)/bin/blastem64-0.6.2/blastem
BLASTEM_WIN := $(HOME)/bin/blastem-win64-0.6.3-pre-a8080240cb92/blastem
USER_NAME := $(shell id -u ${USER})
USER_GROUP := $(shell id -g ${USER})

dev: opensupaplex
	wine $(BLASTEM_WIN) "out\rom.bin"

dev2: opensupaplex
	$(BLASTEM) "$(CURDIR)/out/rom.bin"

prepare:
	sh prepare.sh

opensupaplex: prepare
	docker run --rm -ti -v "${PWD}":/src -u $(USER_NAME):$(USER_GROUP) sgdk

clean:
	rm -rf out
	rm -f res/**.h
	rm -f res/**.rs
	find . -name "*.o" -type f -delete

