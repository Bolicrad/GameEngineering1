#pragma once
#include <assert.h>
#include "GLib.h"
namespace Helper {
	void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);

	GLib::Sprite* CreateSprite(const char* i_pFilename);
}
