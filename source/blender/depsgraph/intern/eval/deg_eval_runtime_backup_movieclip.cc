/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2019 Blender Foundation.
 * All rights reserved.
 */

/** \file
 * \ingroup depsgraph
 */

#include "intern/eval/deg_eval_runtime_backup_movieclip.h"

#include "DNA_movieclip_types.h"

#include "BLI_utildefines.h"

namespace DEG {

MovieClipBackup::MovieClipBackup(const Depsgraph * /*depsgraph*/)
{
  reset();
}

void MovieClipBackup::reset()
{
  anim = NULL;
  cache = NULL;
}

void MovieClipBackup::init_from_movieclip(MovieClip *movieclip)
{
  anim = movieclip->anim;
  cache = movieclip->cache;
  /* Clear pointers stored in the movie clip, so they are not freed when copied-on-written
   * datablock is freed for re-allocation. */
  movieclip->anim = NULL;
  movieclip->cache = NULL;
}

void MovieClipBackup::restore_to_movieclip(MovieClip *movieclip)
{
  movieclip->anim = anim;
  movieclip->cache = cache;

  reset();
}

}  // namespace DEG
