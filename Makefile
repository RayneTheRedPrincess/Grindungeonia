TARGET       := Grindungeonia
BUILD        := build
LIBBUTANO    ?= $(BUTANO_ROOT)
PYTHON       ?= python3
SOURCES      := src
INCLUDES     := include
DATA         :=
GRAPHICS     := graphics
AUDIO        :=
AUDIOBACKEND := null
AUDIOTOOL    :=
DMGAUDIO     :=
DMGAUDIOBACKEND := null
ROMTITLE     := GRINDUNGEON
ROMCODE      := GRDN
USERFLAGS    :=
USERCXXFLAGS :=
USERASFLAGS  :=
USERLDFLAGS  :=
USERLIBDIRS  :=
USERLIBS     :=
DEFAULTLIBS  :=
STACKTRACE   :=
USERBUILD    :=
EXTTOOL      :=

ifndef LIBBUTANOABS
export LIBBUTANOABS := $(realpath $(LIBBUTANO))
endif

ifeq ($(LIBBUTANOABS),)
$(error BUTANO_ROOT must point to Butano's butano/ directory)
endif

include $(LIBBUTANOABS)/butano.mak
