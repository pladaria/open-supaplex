FOLDER := $(shell basename $(CURDIR))
BLASTEM := /home/pladaria/bin/blastem64-0.6.2/blastem
USER_NAME := $(shell id -u ${USER})
USER_GROUP := $(shell id -g ${USER})

dev: opensupaplex
	$(BLASTEM) "$(CURDIR)/out/rom.bin"

prepare:
	sh prepare.sh

opensupaplex: prepare
	docker run --rm -ti -v "${PWD}":/src -u $(USER_NAME):$(USER_GROUP) sgdk

clean:
	rm -rf out
	rm -f res/**.h
	rm -f res/**.rs
