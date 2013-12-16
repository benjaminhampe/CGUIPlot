// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_C_GUI_PLOT_MANAGER_H__
#define __IRR_EXT_C_GUI_PLOT_MANAGER_H__

#include <irrlicht.h>

#include "CGUIPlot.h"

namespace irr
{
namespace gui
{

	///@brief class CGUIPlotManager
	class CGUIPlotManager : public IGUIElement
	{
	public:
		///@brief checks if the given coords are over ( on border or inside ) given rectangle
		static bool isOver( const core::position2di& pos, const core::recti& target_rect );

		///@brief set Parent Element Text ( i.e. the caption of a parent's window title )
		static bool setText( gui::IGUIElement* element, const core::stringw& text );

	protected:
	private:

		///@brief Internal managed plots
		core::array<CGUIPlot*> Plots;

		gui::IGUIFont* Font;

		gui::IGUITabControl* TabControl;

	public:
		///@brief default class constructor
		///@param smgr ISceneManager
		///@param env IGUIEnvironment
		///@param parent Parent element of this element
		///@param id Id of this element
		///@param rectangle Size of this element
		explicit CGUIPlotManager(
			IGUIEnvironment* env,
			IGUIElement* parent,
			s32 id,
			const core::rect<s32>& rectangle );

		///@brief class destructor
		virtual ~CGUIPlotManager();

		///@brief called if an event happened.
		virtual bool OnEvent(const SEvent& event);

		///@brief draws the element and its children
		virtual void draw();

		virtual core::recti getClientRect() const
		{
			const s32 w = AbsoluteRect.getWidth();
			const s32 h = AbsoluteRect.getHeight();

			if (!TabControl)
				return core::recti(0,0,w-1,h-1);

			return core::recti(0,TabControl->getAbsolutePosition().getHeight(),w-1,h-1);
		}

		///@brief get Pointer to single plot.
		///@param index Index of plot-array.
		///@return Pointer to single plot.
		virtual u32 getPlotCount() const
		{
			return Plots.size();
		}

		///@brief get Pointer to single plot.
		///@param index Index of plot-array.
		///@return Pointer to single plot.
		virtual CGUIPlot* getPlot( u32 index = 0 )
		{
			_IRR_DEBUG_BREAK_IF( index >= getPlotCount() )
			return Plots[index];
		}

		///@brief add Plot
		///@param id Unique identifier of this text-shape
		///@param name Name of the ISceneNode
		///@return true on success
		virtual gui::CGUIPlot* addPlot( CGUIPlot* plot )
		{
			if (!plot)
				return 0;

			for (u32 i=0; i<getPlotCount(); i++)
			{
				CGUIPlot* p = Plots[i];
				if (p == plot)
					return plot;
			}

			Plots.push_back( plot );

			return plot;
		}


		///@brief get used GUIEnvironment
		virtual gui::IGUIEnvironment* getGUIEnvironment( )
		{
			return Environment;
		}

		///@brief get TextFont
		virtual gui::IGUIFont* getFont() const
		{
			return Font;
		}

		// ///@brief Updates the absolute position, splits text if required
		// virtual void updateAbsolutePosition();

		///@brief Writes attributes of the element.
		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const;

		///@brief Reads attributes of the element
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

	};

/*
	// Makro: FunctorType "f32 (f32)" this app uses
	//	#define CLASS_ADD_ATTRIBUTE(attrib_name, visiblity, ret_type, ...) \
	//		virtual ret_type set attrib_name ( const video::SColor& color ) \
	//		{\
	//			 = color;\
	//		}\
	//		\
	//		\
	//		virtual video::SColor getBackgroundColor() const \
	//		{ \
	//			return BackgroundColor; \
	//		} \

	//__LINE__
	//die Zeilennummer der aktuellen Zeile in der Programmdatei
	//__FILE__
	//der Name der Programmdatei
	//__DATE__
	//das Übersetzungsdatum der Programmdatei
	//__TIME__
	//die Übersetzungszeit der Programmdatei
	//__STDC__
	//das Erkennungsmerkmal eines ANSI-C-Compilers. Ist die ganzzahlige Konstante auf den Wert 1 gesetzt, handelt es sich um einen ANSI-C-konformen Compiler.
	//__cplusplus
	//C++-Code
*/

} // end namespace gui
} // end namespace irr

#endif // __IRR_EXT_C_GUI_PLOT_H__
