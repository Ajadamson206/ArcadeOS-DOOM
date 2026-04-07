ifeq ($(V),1)
	VB=''
else
	VB=@
endif


CC=gcc

# Directories
PROJECT_ROOT  := ../../..
DOOM_DIR      := $(PROJECT_ROOT)/src/DOOM-PORT/doomgeneric
OBJDIR        := $(PROJECT_ROOT)/build/kernel/doom

# Flags
CFLAGS := -m32 
CFLAGS += -ffreestanding 
CFLAGS += -fno-pic 
CFLAGS += -fno-pie
CFLAGS += -fno-stack-protector
CFLAGS += -Wall -Wextra
CFLAGS += -D_DEFAULT_SOURCE
#CFLAGS += -DNORMALUNIX -DLINUX

# Header search paths
CFLAGS += -I$(PROJECT_ROOT)/include
CFLAGS += -I$(DOOM_DIR)

# subdirectory for objects
OBJDIR=build
OUTPUT=doomgeneric


SRC_DOOM := \
	am_map.c \
	doomdef.c \
	doomstat.c \
	dstrings.c \
	d_event.c \
	d_items.c \
	d_iwad.c \
	d_loop.c \
	d_main.c \
	d_mode.c \
	d_net.c \
	f_finale.c \
	f_wipe.c \
	g_game.c \
	hu_lib.c \
	hu_stuff.c \
	info.c \
	i_cdmus.c \
	i_endoom.c \
	i_joystick.c \
	i_scale.c \
	i_sound.c \
	i_system.c \
	i_timer.c \
	memio.c \
	m_argv.c \
	m_bbox.c \
	m_cheat.c \
	m_config.c \
	m_controls.c \
	m_fixed.c \
	m_menu.c \
	m_misc.c \
	m_random.c \
	p_ceilng.c \
	p_doors.c \
	p_enemy.c \
	p_floor.c \
	p_inter.c \
	p_lights.c \
	p_map.c \
	p_maputl.c \
	p_mobj.c \
	p_plats.c \
	p_pspr.c \
	p_saveg.c \
	p_setup.c \
	p_sight.c \
	p_spec.c \
	p_switch.c \
	p_telept.c \
	p_tick.c \
	p_user.c \
	r_bsp.c \
	r_data.c \
	r_draw.c \
	r_main.c \
	r_plane.c \
	r_segs.c \
	r_sky.c \
	r_things.c \
	sha1.c \
	sounds.c \
	statdump.c \
	st_lib.c \
	st_stuff.c \
	s_sound.c \
	tables.c \
	v_video.c \
	wi_stuff.c \
	w_checksum.c \
	w_file.c \
	w_main.c \
	w_wad.c \
	z_zone.c \
	w_file_stdc.c \
	i_input.c \
	i_video.c \
	doomgeneric.c

#SRC_DOOM = dummy.o am_map.o doomdef.o doomstat.o dstrings.o d_event.o d_items.o d_iwad.o d_loop.o d_main.o d_mode.o d_net.o f_finale.o f_wipe.o g_game.o hu_lib.o hu_stuff.o info.o i_cdmus.o i_endoom.o i_joystick.o i_scale.o i_sound.o i_system.o i_timer.o memio.o m_argv.o m_bbox.o m_cheat.o m_config.o m_controls.o m_fixed.o m_menu.o m_misc.o m_random.o p_ceilng.o p_doors.o p_enemy.o p_floor.o p_inter.o p_lights.o p_map.o p_maputl.o p_mobj.o p_plats.o p_pspr.o p_saveg.o p_setup.o p_sight.o p_spec.o p_switch.o p_telept.o p_tick.o p_user.o r_bsp.o r_data.o r_draw.o r_main.o r_plane.o r_segs.o r_sky.o r_things.o sha1.o sounds.o statdump.o st_lib.o st_stuff.o s_sound.o tables.o v_video.o wi_stuff.o w_checksum.o w_file.o w_main.o w_wad.o z_zone.o w_file_stdc.o i_input.o i_video.o doomgeneric.o doomgeneric_xlib.o

SRC_PORT := doomgeneric_arcadeos.c

# Full Source Paths
SOURCES := \
	$(addprefix $(DOOM_DIR)/,$(SRC_DOOM)) \
	$(addprefix $(DOOM_DIR)/,$(SRC_PORT))

# Output Objects
OBJS := $(patsubst $(DOOM_DIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all print clean

all:	 $(OBJS)

clean:
	rm -rf $(OBJDIR)

print:
	@echo "PROJECT_ROOT  = $(PROJECT_ROOT)"
	@echo "DOOM_DIR      = $(DOOM_DIR)"
	@echo "OBJDIR        = $(OBJDIR)"
	@echo "OBJS          = $(OBJS)"

# Build Rules
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(DOOM_DIR)/%.c | $(OBJDIR)
	@echo [Compiling $<]
	$(VB)$(CC) $(CFLAGS) -c $< -o $@

# $(OUTPUT):	$(OBJS)
# 	@echo [Linking $@]
# 	$(VB)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) \
# 	-o $(OUTPUT) $(LIBS) -Wl,-Map,$(OUTPUT).map
# 	@echo [Size]
# 	-$(CROSS_COMPILE)size $(OUTPUT)
# 
# $(OBJS): | $(OBJDIR)
# 
# $(OBJDIR):
# 	mkdir -p $(OBJDIR)
# 
# $(OBJDIR)/%.o:	%.c
# 	@echo [Compiling $<]
# 	$(VB)$(CC) $(CFLAGS) -c $< -o $@


