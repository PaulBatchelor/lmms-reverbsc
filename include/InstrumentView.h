/*
 * InstrumentView.h - definition of InstrumentView-class
 *
 * Copyright (c) 2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 *
 * This file is part of LMMS - http://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#ifndef INSTRUMENT_VIEW_H
#define INSTRUMENT_VIEW_H

#include "Instrument.h"
#include "PluginView.h"

class InstrumentTrackWindow;


class EXPORT InstrumentView : public PluginView
{
public:
	InstrumentView( Instrument * _instrument, QWidget * _parent );
	virtual ~InstrumentView();

	Instrument * model()
	{
		return( castModel<Instrument>() );
	}

	const Instrument * model() const
	{
		return( castModel<Instrument>() );
	}

	virtual void setModel( Model * _model, bool = false );

	InstrumentTrackWindow * instrumentTrackWindow();

} ;


#endif
