// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CGUIPlotManager.h"

//#include "../core/CMath.h"

#include <GL/gl.h>
#include <GL/glu.h>


namespace irr
{
namespace gui
{

bool CGUIPlotManager::isOver( const core::position2di& pos, const core::recti& target_rect )
{
	bool result(false);
	if (pos.X >= target_rect.UpperLeftCorner.X)
		if (pos.X <= target_rect.LowerRightCorner.X)
			if (pos.Y >= target_rect.UpperLeftCorner.Y)
				if (pos.Y <= target_rect.LowerRightCorner.Y)
					result = true;
	return result;
}

//! set Parent Element Text ( i.e. the caption of a parent's window title )
bool CGUIPlotManager::setText( gui::IGUIElement* element, const core::stringw& text )
{
	if (!element)
		return false;

	element->setText( text.c_str() );

	return true;
}

//! constructor
CGUIPlotManager::CGUIPlotManager(
	IGUIEnvironment* env,
	IGUIElement* parent,
	s32 id,
	const core::rect<s32>& rectangle)
: IGUIElement( EGUIET_ELEMENT, env, parent, id, rectangle)
, Font(0)
, TabControl(0)
{

#ifdef _DEBUG
	setDebugName("CGUIPlotManager");
#endif

	setTabStop(false);
	setTabOrder(-1);

	// Font = Environment->getFont("../../media/fonts/courier10.png");
	s32 w = AbsoluteRect.getWidth(); // in pixels
	s32 h = AbsoluteRect.getHeight(); // in pixels

	s32 bar_height = 88;
	s32 tab_height = 24;
	s32 btn_width = 64;
	s32 btn_height = 32;

	TabControl = Environment->addTabControl( core::recti( 0, 0, w, bar_height), this, true, true, -1 );
	TabControl->setTabHeight( tab_height );

	gui::IGUITab* TabStart = TabControl->addTab(L"Start", -1);
	gui::IGUITab* TabVars = TabControl->addTab(L"Variables", -1);
	gui::IGUITab* TabFuns = TabControl->addTab(L"Functions", -1);
	gui::IGUITab* TabClasses = TabControl->addTab(L"Classes", -1);
	gui::IGUITab* TabStats = TabControl->addTab(L"Statistics", -1);
	gui::IGUITab* TabMacros = TabControl->addTab(L"Macros", -1);
	gui::IGUITab* TabHelp = TabControl->addTab(L"Help", -1);

	s32 x = 0;
	s32 y = 0;
	Environment->addButton( core::recti(x,y,x+btn_width-1, y+btn_height-1), TabStart, -1, L"New", L"New"); x+=btn_width;
	Environment->addButton( core::recti(x,y,x+btn_width-1, y+btn_height-1), TabStart, -1, L"Load", L"Load"); x+=btn_width;
	Environment->addButton( core::recti(x,y,x+btn_width-1, y+btn_height-1), TabStart, -1, L"Save", L"Save"); x+=btn_width;
	Environment->addButton( core::recti(x,y,x+btn_width-1, y+btn_height-1), TabStart, -1, L"SaveAs", L"SaveAs"); x+=btn_width;
	y+=btn_height;

	x=0;
	Environment->addButton( core::recti(x,y,x+btn_width-1, y+btn_height-1), TabStart, -1, L"New", L"New"); x+=btn_width;
	Environment->addButton( core::recti(x,y,x+btn_width-1, y+btn_height-1), TabStart, -1, L"Load", L"Load"); x+=btn_width;
	Environment->addButton( core::recti(x,y,x+btn_width-1, y+btn_height-1), TabStart, -1, L"Save", L"Save"); x+=btn_width;
	Environment->addButton( core::recti(x,y,x+btn_width-1, y+btn_height-1), TabStart, -1, L"SaveAs", L"SaveAs"); x+=btn_width;
	y+=btn_height;

	Environment->setFocus(this);
}



//! destructor
CGUIPlotManager::~CGUIPlotManager()
{
}

//! draws the element and its children
void CGUIPlotManager::draw()
{
	if (!IsVisible)
		return;

//	const bool focus = Environment->hasFocus(this);

//	if (IsMouseOver)
//	{
//		driver->draw2DRectangleOutline( AbsoluteRect, video::SColor(255,255,255,0) );
//	}

	// draw children
	IGUIElement::draw();
}

//! called if an event happened.
bool CGUIPlotManager::OnEvent(const SEvent& event)
{
	if (IsEnabled)
	{
		// OnMouse(event);

		switch(event.EventType)
		{
			case EET_MOUSE_INPUT_EVENT:
			{
				const SEvent::SMouseInput& e = event.MouseInput;

				const core::position2di mouse_pos(e.X,e.Y);

				switch(e.Event)
				{
					/// MouseMove
					case EMIE_MOUSE_MOVED:
						break;

					/// MouseWheel
					case EMIE_MOUSE_WHEEL:
						break;

					default:
						break;
				}
			}
				break;

			default:
				break;
		}
	}

	return IGUIElement::OnEvent(event);
}

//! Writes attributes of the element.
void CGUIPlotManager::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
{
	// IGUIEditBox::serializeAttributes(out,options);
//	out->addBool  ("OverrideColorEnabled",OverrideColorEnabled );
//	out->addColor ("OverrideColor",       OverrideColor);
//	// out->addFont("OverrideFont",OverrideFont);
//	out->addInt   ("MaxChars",            Max);
//	out->addBool  ("WordWrap",            WordWrap);
//	out->addBool  ("MultiLine",           MultiLine);
//	out->addBool  ("AutoScroll",          AutoScroll);
//	out->addBool  ("PasswordBox",         PasswordBox);
//	core::stringw ch = L" ";
//	ch[0] = PasswordChar;
//	out->addString("PasswordChar",        ch.c_str());
//	out->addEnum  ("HTextAlign",          HAlign, GUIAlignmentNames);
//	out->addEnum  ("VTextAlign",          VAlign, GUIAlignmentNames);
//
	IGUIElement::serializeAttributes(out,options);
}

//! Reads attributes of the element
void CGUIPlotManager::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
{
	IGUIElement::deserializeAttributes(in,options);

//	setOverrideColor(in->getAttributeAsColor("OverrideColor"));
//	enableOverrideColor(in->getAttributeAsBool("OverrideColorEnabled"));
//	setMax(in->getAttributeAsInt("MaxChars"));
//	setWordWrap(in->getAttributeAsBool("WordWrap"));
//	setMultiLine(in->getAttributeAsBool("MultiLine"));
//	setAutoScroll(in->getAttributeAsBool("AutoScroll"));
//	core::stringw ch = in->getAttributeAsStringW("PasswordChar");
//
//	if (!ch.size())
//		setPasswordBox(in->getAttributeAsBool("PasswordBox"));
//	else
//		setPasswordBox(in->getAttributeAsBool("PasswordBox"), ch[0]);
//
//	setTextAlignment( (EGUI_ALIGNMENT) in->getAttributeAsEnumeration("HTextAlign", GUIAlignmentNames),
//		(EGUI_ALIGNMENT) in->getAttributeAsEnumeration("VTextAlign", GUIAlignmentNames));

	// setOverrideFont(in->getAttributeAsFont("OverrideFont"));
}

} // end namespace gui
} // end namespace irr
