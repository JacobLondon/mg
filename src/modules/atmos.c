#include <rlu/rlu.h>
#include "atmos.h"

#define ASSET_MUSIC "music.mp3"

static void init_cb_background(scene *self);
static void init_cb_starfield(scene *self);
static void init_cb_planetfield(scene *self);

static texture_manager textureman;
static scene_manager manager;

static scene_definition scenes[] = {
	{"Background", 1, init_cb_background},
	{"Starfield", 90, init_cb_starfield},
	{"Planetfield", 10, init_cb_planetfield},
	{NULL}
};

static scene_set sets[] = {
	{"Default", {"Background", "Planetfield", "Starfield", NULL}},
	{NULL}
};

static char asset_directory[128];

void atmos_init(char *assetdir)
{
	assert(assetdir);
	snprintf(asset_directory, sizeof(asset_directory), "%s", assetdir);

	scene_man_new(&manager, scenes, sets);
	texture_man_new(&textureman);

	scene_man_load_set(&manager, "Default");
}

void atmos_cleanup(void)
{
	scene_man_del(&manager);
	texture_man_del(&textureman);
}

void atmos_update(void)
{
	scene_man_update(&manager);
}

void atmos_draw(void)
{
	scene_man_draw(&manager);
}

/**
 * Static Functions
 */

static void init_cb_background(scene *self)
{
	char path[128];
	Texture2D *t;
	anim *a;
	so *s;

	snprintf(path, sizeof(path), "%s/background.png", asset_directory);
	t = texture_man_load_or_default(&textureman, path, TEXTURE_GEN(1000, 1000, BLACK));
	a = anim_man_load(scene_man_get_anim_man(&manager), t, 1, 1);
	s = so_new(a);
	so_set_pos(s, 0, 0);
	scene_load_object(self, s);
}

static void init_cb_starfield(scene *self)
{
	int i;
	char path[128];
	Texture2D *t;
	anim *a;
	so *s;

	// 90 items max...

	snprintf(path, sizeof(path), "%s/starfar.png", asset_directory);
	t = texture_man_load_or_default(&textureman, path, TEXTURE_GEN(1, 1, WHITE));
	a = anim_man_load(scene_man_get_anim_man(&manager), t, 1, 1);
	for (i = 0; i < 30; i++) {
		s = so_new(a);
		so_set_pos(s, GetScreenWidth() * rand_uniform(), GetScreenHeight() * rand_uniform());
		so_newmov(s, so_cb_loop_down, 2, NULL);
		scene_load_object(self, s);
	}

	snprintf(path, sizeof(path), "%s/starmed.png", asset_directory);
	t = texture_man_load_or_default(&textureman, path, TEXTURE_GEN(2, 2, WHITE));
	a = anim_man_load(scene_man_get_anim_man(&manager), t, 1, 1);
	for (i = 0; i < 30; i++) {
		s = so_new(a);
		so_set_pos(s, GetScreenWidth() * rand_uniform(), GetScreenHeight() * rand_uniform());
		so_newmov(s, so_cb_loop_down, 4, NULL);
		scene_load_object(self, s);
	}

	snprintf(path, sizeof(path), "%s/starnear.png", asset_directory);
	t = texture_man_load_or_default(&textureman, path, TEXTURE_GEN(4, 4, WHITE));
	a = anim_man_load(scene_man_get_anim_man(&manager), t, 1, 1);
	for (i = 0; i < 30; i++) {
		s = so_new(a);
		so_set_pos(s, GetScreenWidth() * rand_uniform(), GetScreenHeight() * rand_uniform());
		so_newmov(s, so_cb_loop_down, 6, NULL);
		scene_load_object(self, s);
	}
}

static void init_cb_planetfield(scene *self)
{
	char path[128];
	Texture2D *t;
	anim *a;
	so *s;

	snprintf(path, sizeof(path), "%s/planet.png", asset_directory);
	t = texture_man_load_or_default(&textureman, path, TEXTURE_GEN(35, 35, GRAY));
	a = anim_man_load(scene_man_get_anim_man(&manager), t, 1, 1);
	s = so_new(a);
	so_set_pos(s, GetScreenWidth() * rand_uniform(), GetScreenHeight() * rand_uniform());
	so_newmov(s, so_cb_loop_down, 1, NULL);
	scene_load_object(self, s);
}