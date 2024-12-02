/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>
#include <plugin-support.h>
#include <obs.h>
#include <obs-frontend-api.h>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

#define PLUGIN_NAME "TextSourcePlugin"
#define PLUGIN_VERSION "1.0"

// This will be the text shown on the text source
#define TEXT_SOURCE_NAME "Patreon Scroller"
#define TEXT_CONTENT "Thank you to our amazing patrons!"

// Function to add the text source to the scene
void add_text_source_to_scene(void)
{
	// Get the current active scene source
	obs_source_t *current_scene_source = obs_frontend_get_current_scene();

	if (!current_scene_source) {
		obs_log(LOG_WARNING, "Failed to get the active scene source.");
		return;
	}

	// Get the scene from the current scene source
	obs_scene_t *scene = obs_scene_from_source(current_scene_source);

	if (!scene) {
		obs_log(LOG_WARNING,
			"Failed to get the scene from the current scene source.");
		return;
	}

	// Define the text source settings
	obs_data_t *settings = obs_data_create();
	obs_data_set_string(settings, "text",
			    TEXT_CONTENT); // Set the content of the text source

	// Create the text source
	obs_source_t *text_source = obs_source_create(
		"text_gdiplus", TEXT_SOURCE_NAME, settings, NULL);

	if (text_source) {
		// Add the text source to the current scene
		obs_scene_add(scene, text_source);
		obs_log(LOG_INFO, "Text source '%s' added to scene.",
			TEXT_SOURCE_NAME);
	} else {
		obs_log(LOG_WARNING, "Failed to create text source '%s'.",
			TEXT_SOURCE_NAME);
	}

	// Clean up settings
	obs_data_release(settings);
}

bool obs_module_load(void)
{
	obs_log(LOG_INFO, "plugin loaded successfully (version %s)",
		PLUGIN_VERSION);

	// Add the text source to the active scene when the plugin is loaded
	add_text_source_to_scene();

	return true;
}

void obs_module_unload(void)
{
	obs_log(LOG_INFO, "plugin unloaded");
}
