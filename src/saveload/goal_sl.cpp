/* $Id$ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file goal_sl.cpp Code handling saving and loading of goals */

#include "../stdafx.h"
#include "../goal_base.h"

#include "saveload_buffer.h"

static const SaveLoad _goals_desc[] = {
	SLE_VAR(Goal, company,   SLE_UINT16),
	SLE_VAR(Goal, type,      SLE_UINT16),
	SLE_VAR(Goal, dst,       SLE_UINT32),
	SLE_STR(Goal, text,      SLS_STR | SLS_ALLOW_CONTROL, 0),
	SLE_STR(Goal, progress,  SLS_STR | SLS_ALLOW_CONTROL, 0, 0, , 182, ),
	SLE_VAR(Goal, completed, SLE_BOOL, 0, , 182, ),
	SLE_END()
};

static void Save_GOAL(SaveDumper *dumper)
{
	Goal *s;
	FOR_ALL_GOALS(s) {
		dumper->WriteElement(s->index, s, _goals_desc);
	}
}

static void Load_GOAL(LoadBuffer *reader)
{
	int index;
	while ((index = reader->IterateChunk()) != -1) {
		Goal *s = new (index) Goal();
		reader->ReadObject(s, _goals_desc);
	}
}

extern const ChunkHandler _goal_chunk_handlers[] = {
	{ 'GOAL', Save_GOAL, Load_GOAL, NULL, NULL, CH_ARRAY | CH_LAST},
};
