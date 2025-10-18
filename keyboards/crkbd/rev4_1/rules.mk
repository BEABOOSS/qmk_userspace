# BOOTLOADER_SIZE = 6144
# each one has 127MB of space

# debugging
CONSOLE_ENABLE ?= no
AVR_USE_MINIMAL_PRINTF = no

# reducing size
MUSIC_ENABLE = no

# RGB
RGB_MATRIX_CUSTOM_USER ?= no

# split
COMBO_ENABLE = yes
TAP_DANCE_ENABLE ?= yes

LAYER_LOCK_ENABLE = no


SELECT_WORD_ENABLE ?= no
ifeq ($(strip $(SELECT_WORD_ENABLE)), yes)
	OPT_DEFS += -DSELECT_WORD_ENABLE
	SRC += ../../../../features/select_word.c
endif

KEYCODE_STRING_ENABLE ?= no
ifeq ($(strip $(KEYCODE_STRING_ENABLE)), yes)
	OPT_DEFS += -DKEYCODE_STRING_ENABLE
	SRC += ../../../../features/keycode_string.c
endif
