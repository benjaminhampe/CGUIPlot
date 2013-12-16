// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CGUIClassBuilder.h"

namespace irr
{
namespace gui
{

//! constructor
CGUIClassBuilder::CGUIClassBuilder(
	IGUIEnvironment* env,
	IGUIElement* parent,
	s32 id,
	const core::rect<s32>& rectangle)
: IGUIElement( EGUIET_ELEMENT, env, parent, id, rectangle)
{
#ifdef _DEBUG
	setDebugName("CGUIClassBuilder");
#endif

	setTabStop(false);
	setTabOrder(-1);

	Font = Environment->getFont("../../media/fonts/courier10.png");

	s32 w = AbsoluteRect.getWidth(); // in pixels
	s32 h = AbsoluteRect.getHeight(); // in pixels

	s32 btn_width = core::abs_<s32>( core::s32_min( w, h ) - 4 );
	s32 btn_height = btn_width;
	s32 sb_size = 16; // in pixels

	Environment->setFocus(this);
}



//! destructor
CGUIClassBuilder::~CGUIClassBuilder()
{
}

//! draws the element and its children
void CGUIClassBuilder::draw()
{
	if (!IsVisible)
		return;

//	const bool focus = Environment->hasFocus(this);

//	IGUISkin* skin = Environment->getSkin();
//	if (!skin)
//		return;

	/// set Text of Parent ( WindowCaption )
	//	core::stringw t = L"CGUIClassBuilder | Shapes = "; t += Shapes.size();
	//	t += L" | Texts = "; t += Texts.size();
	//	t += L" | ZoomRect = { ";
	//	t += ZoomRect.UpperLeftCorner.X; t += L", ";
	//	t += ZoomRect.UpperLeftCorner.Y; t += L", ";
	//	t += ZoomRect.LowerRightCorner.X; t += L", ";
	//	t += ZoomRect.LowerRightCorner.Y; t += L" }";
	//	t += L" | AbsoluteRect = { x="; t += AbsoluteRect.UpperLeftCorner.X;
	//	t += L", y="; t += AbsoluteRect.UpperLeftCorner.Y;
	//	t += L", w="; t += AbsoluteRect.getWidth();
	//	t += L", h="; t += AbsoluteRect.getHeight();
	//	t += L"}";
	//	setText( Parent, t );

	video::IVideoDriver* driver = Environment->getVideoDriver();
	//	if (!driver)
	//		return;

	/// deactivate all other SceneNodes than my own Root

	//	_IRR_DEBUG_BREAK_IF( !SceneManager )
	_IRR_DEBUG_BREAK_IF( !driver )

	//	if (IsMouseOver)
	//	{
	//		driver->draw2DRectangleOutline( AbsoluteRect, video::SColor(255,255,0,0) );
	//	}

	// draw children
	IGUIElement::draw();
}

//! called if an event happened.
bool CGUIClassBuilder::OnEvent(const SEvent& event)
{
	if (IsEnabled)
	{
		switch(event.EventType)
		{
			// MOUSE_EVENTS;

			case EET_MOUSE_INPUT_EVENT:
			{
				const SEvent::SMouseInput& e = event.MouseInput;

				const core::position2di mouse_pos(e.X,e.Y);

				switch(e.Event)
				{
					/// MouseMove
					case EMIE_MOUSE_MOVED:
					{
//						IsMouseOver = isOver( mouse_pos, AbsoluteRect );
						return false;
					}
					break;

					/// MouseWheel
					case EMIE_MOUSE_WHEEL:
					{
//
//						if (e.Wheel > 0.0f )
//						{
//							ZoomRect.UpperLeftCorner.X *= 0.9f;
//							ZoomRect.UpperLeftCorner.Y *= 0.9f;
//							ZoomRect.LowerRightCorner.X *= 0.9f;
//							ZoomRect.LowerRightCorner.Y *= 0.9f;
//						}
//						else
//						{
//							ZoomRect.UpperLeftCorner.X *= 1.1f;
//							ZoomRect.UpperLeftCorner.Y *= 1.1f;
//							ZoomRect.LowerRightCorner.X *= 1.1f;
//							ZoomRect.LowerRightCorner.Y *= 1.1f;
//						}
						return false;
					}
					break;

					//	case EMIE_LMOUSE_LEFT_UP:
					//		if (Environment->hasFocus(this))
					//		{
					//			if (!InMenu) {
					//				if (!DoubleClicked) {
					//					CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
					//					if (MouseMarking)
					//					{
					//						setTextMarkers( MarkBegin, CursorPos );
					//					}
					//
					//					//Scrollbar->setPos(getLineFromPos(CursorPos));
					//					calculateScrollPos();
					//
					//				}
					//				MouseMarking = false;
					//				DoubleClicked = false;
					//			}
					//			return true;
					//		}
					//		break;


					//	case EMIE_RMOUSE_LEFT_UP:
					//		{
					//			if (Environment->hasFocus(this))
					//			{
					//			}
					//			return true;
					//			break;
					//		}
					//	case EMIE_LMOUSE_DOUBLE_CLICK:
					//		{
					//			return true;
					//			break;
					//		}
					//	case EMIE_LMOUSE_TRIPLE_CLICK:
					//		{
					//			break;
					//		}
					//	case EMIE_LMOUSE_PRESSED_DOWN:
					//		{
					//			if (!Environment->hasFocus(this))
					//			{
					//				return true;
					//			}
					//		}
					//		return true;
					//	case EMIE_RMOUSE_PRESSED_DOWN:
					//		{
					//			if (!Environment->hasFocus(this))
					//			{
					//			}
					//		}
					//		return true;
					default:
						break;
				}
			}
			break;
			//
			//		case EET_KEY_INPUT_EVENT:
			//			if (processKey(event))
			//				return true;
			//			break;
			//

		default:
			break;
		}
	}

	return IGUIElement::OnEvent(event);
}

//! Writes attributes of the element.
void CGUIClassBuilder::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
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
void CGUIClassBuilder::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
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
