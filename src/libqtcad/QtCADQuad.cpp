/*                      Q T C A D Q U A D . C P P
 * BRL-CAD
 *
 * Copyright (c) 2021 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file QtCADQuad.cpp
 *
 */

#include "common.h"

#include <QGridLayout>
#include "qtcad/QtCADQuad.h"

QtCADQuad::QtCADQuad(QWidget *parent, int type)
    : QWidget(parent)
{
    // Create the four view widgets
    ur = new QtCADView(this, type);
    ul = new QtCADView(this, type);
    ll = new QtCADView(this, type);
    lr = new QtCADView(this, type);

    // Define the spacers
    QSpacerItem *s_top = new QSpacerItem(3, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSpacerItem *s_bottom = new QSpacerItem(3, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSpacerItem *s_left = new QSpacerItem(0, 3, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *s_right = new QSpacerItem(0, 3, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *s_center = new QSpacerItem(3, 3, QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Default to selecting quadrant 1
    c = ur;

    // Lay out the widgets and spacers in a Quad View arrangement
    QGridLayout *gl = new QGridLayout(this);
    gl->setSpacing(0);
    gl->setContentsMargins(0, 0, 0, 0);
    gl->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->setLayout(gl);
    gl->addWidget(ul,     0, 0);
    gl->addItem(s_top,    0, 1);
    gl->addWidget(ur,     0, 2);
    gl->addItem(s_left,   1, 0);
    gl->addItem(s_center, 1, 1);
    gl->addItem(s_right,  1, 2);
    gl->addWidget(ll,     2, 0);
    gl->addItem(s_bottom, 2, 1);
    gl->addWidget(lr,     2, 2);
}

QtCADQuad::~QtCADQuad()
{
    delete ur;
    delete ul;
    delete ll;
    delete lr;
}

QtCADView *
QtCADQuad::get(int quadrant_id)
{
    switch (quadrant_id) {
	case 1:
	    return ur;
	case 2:
	    return ul;
	case 3:
	    return ll;
	case 4:
	    return lr;
	default:
	    return c;
    }
}

void
QtCADQuad::select(int quadrant_id)
{
    switch (quadrant_id) {
	case 1:
	    c = ur;
	    break;
	case 2:
	    c = ul;
	    break;
	case 3:
	    c = ll;
	    break;
	case 4:
	    c = lr;
	    break;
	default:
	    return;
    }

    // TODO - update coloring of bg to
    // indicate active quadrant

}

void
QtCADQuad::select(const char *quadrant_id)
{
    if (BU_STR_EQUIV(quadrant_id, "ur")) {
	select(1);
	return;
    }
    if (BU_STR_EQUIV(quadrant_id, "ul")) {
	select(2);
	return;
    }
    if (BU_STR_EQUIV(quadrant_id, "ll")) {
	select(3);
	return;
    }
    if (BU_STR_EQUIV(quadrant_id, "lr")) {
	select(4);
	return;
    }
}

void
QtCADQuad::need_update()
{
    ur->update();
    ul->update();
    ll->update();
    lr->update();
}

// TODO - need to enable mouse selection
// of a quadrant as current

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
