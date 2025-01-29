#BOARD= esp32_devkitc_wroom/esp32/procpu
BOARD= esp32s3_devkitc/esp32s3/procpu
OPTIONS= -p always 
BUILD_DIR= build/
ESPTOOL= /home/chroco/zephyr/zephyr-workspace/modules/hal/espressif/tools/esptool_py/esptool.py
PORT= /dev/ttyACM0
BAUD= 921600
MODE= qio
FORCE=# --force
OVERLAY= esp32s3_devkitc_procpu.overlay
BIN= /home/chroco/zephyr/blinky/build/mcuboot/zephyr/zephyr.bin
ARGS= --port $(PORT) --chip auto --baud $(BAUD) --before default_reset --after hard_reset write_flash $(FORCE) -u --flash_mode $(MODE) --flash_freq 40m --flash_size detect 0x0000

CA_CERT= sample_ca_cert
SERVER_CERT= sample_server_cert

.PHONY: all write clean

all: clean 
	@west build $(OPTIONS) -b $(BOARD) .  #--sysbuild .

cert_gen: clean
	@west build $(OPTIONS) -b $(BOARD) -t $(CA_CERT)
	@west build -t $(SERVER_CERT)
	@west build

monitor:
	@west espressif monitor

write:
	@west flash 

clean:
	@rm -rf $(BUILD_DIR)/*
