// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_C_GUI_PLOT_H__
#define __IRR_EXT_C_GUI_PLOT_H__

#include <irrlicht.h>

#include <functional>

namespace irr
{
namespace gui
{
	///@brief class CGUIPlot
	class CGUIPlot : public IGUIElement
	{
	public:
		///@brief checks if the given coords are over ( on border or inside ) given rectangle
		static bool isOver( const core::position2di& pos, const core::recti& target_rect );

		///@brief set Parent Element Text ( i.e. the caption of a parent's window title )
		static bool setText( gui::IGUIElement* element, const core::stringw& text );

		///@brief setVisible(false) to all SceneNodes
		static bool hideAll( scene::ISceneManager* smgr );

		///@brief setVisible(true) to all SceneNodes
		static bool showAll( scene::ISceneManager* smgr );

		///@brief buildProjectionMatrixOrthoLH with 6 params, not 4 as irrlicht only does
		static core::matrix4 buildProjectionMatrixOrthoLH( f32 left, f32 right, f32 bottom, f32 top, f32 zNear = 0.1f, f32 zFar = 1000.0f );

		///@brief create a recti from position2di and dimension2du
		inline core::recti makeRect( s32 x, s32 y, u32 w, u32 h)
		{
			return core::recti( core::position2di(x,y), core::dimension2du(w,h) );
		}

		///@brief struct Shape ( holds a pointer to SceneNode and a name as UTF-8 string )
		struct Shape
		{
			///@brief unique Identifier
			core::stringc ID;

			///@brief pointer to ISceneNode
			scene::ISceneNode* Node;

			///@brief struct constructor
			Shape() : ID(""), Node(0)
			{
				// empty
			}

			///@brief struct constructor
			Shape( const core::stringc& id, scene::ISceneNode* node ) : ID(id), Node(node)
			{
				// empty
			}

			///@brief struct destructor
			~Shape()
			{
				// empty
			}
		};

		///@brief struct SText2d ( holds a pointer to SceneNode and a name as UTF-8 string )
		class SText
		{
			public:

			///@brief unique Identifier
			core::stringc ID;

			///@brief UTF-16 text data
			core::stringw Text;

			///@brief Parent of this text ( mostly an instance of CGUIPlot to get AbsoluteRect, TextColor )
			CGUIPlot* Parent;

			///@brief Font of this text
			gui::IGUIFont* Font;

			///@brief Position of this text in 2D screen-space
			core::position2di ScreenPos;

			///@brief Size of this text
			core::dimension2du Size;

			///@brief Color of this text
			video::SColor Color;

			///@brief Horizontal align of this text ( -1=left, 0=center, 1=right )
			s32 HAlign;

			///@brief Vertical align of this text ( -1=top, 0=middle, 1=bottom )
			s32 VAlign;

			///@brief true if the 3d world-position should be projected to screen ( needs SceneManager ),
			/// false if already 2d text and not using world-space coords ( needs only GUIEnvironment )
			bool Is3DText;

			///@brief SceneManager/VideoDriver to render this text when its 3d
			scene::ISceneManager* SceneManager;

			///@brief Position of this text in 3D world-space
			core::vector3df WorldPos;

			private:
			///@brief forbidden default constructor
			SText()
			{
				// empty
			}

			public:

			///@brief construct a 2d text
			SText( CGUIPlot* parent, const core::stringc& id, const core::stringw& text,
				const core::position2di& screen_pos, s32 hAlign = -1, s32 vAlign = -1,
				const video::SColor& color = video::SColor(0,0,0,0), gui::IGUIFont* font = 0 )
			: ID(id), Text(text), Parent(parent), Font(font), ScreenPos(screen_pos)
			, Size(0,0), Color(color), HAlign(hAlign), VAlign(vAlign)
			, Is3DText(false), SceneManager(0), WorldPos(0,0,0)
			{
				if (!Font && Parent)
					Font = Parent->getTextFont();

				if (Font && Text.size()>0)
					Size = Font->getDimension( Text.c_str() );

				if (Color.getAlpha() == 0)
					Color = Parent->getTextColor();
			}

			///@brief construct a 3d text
			SText( CGUIPlot* parent, const core::stringc& id, const core::stringw& text,
				scene::ISceneManager* smgr, const core::vector3df& world_pos,	s32 hAlign = -1, s32 vAlign = -1,
				const video::SColor& color = video::SColor(0,0,0,0), gui::IGUIFont* font = 0 )
			: ID(id), Text(text), Parent(parent), Font(font), ScreenPos(0,0)
			, Size(0,0), Color(color), HAlign(hAlign), VAlign(vAlign)
			, Is3DText(true), SceneManager(smgr), WorldPos(world_pos)
			{
				if (!Font && Parent)
					Font = Parent->getTextFont();

				if (Font && Text.size()>0)
					Size = Font->getDimension( Text.c_str() );

				if (Color.getAlpha() == 0)
					Color = Parent->getTextColor();
			}

			///@brief struct destructor
			~SText()
			{
				// empty
			}
		};

		///@brief class constructor
		///@param smgr ISceneManager
		///@param env IGUIEnvironment
		///@param parent Parent element of this element
		///@param id Id of this element
		///@param rectangle Size of this element
		CGUIPlot(
			scene::ISceneManager* smgr,
			IGUIEnvironment* env,
			IGUIElement* parent,
			s32 id,
			const core::rect<s32>& rectangle );

		///@brief class destructor
		virtual ~CGUIPlot();

		///@brief called if an event happened.
		virtual bool OnEvent(const SEvent& event);

		///@brief draws the element and its children
		virtual void draw();

		///@brief quick transform from world-coords into screen coords for texts, etc.
		///@param pos Position given in world-space
		///@return Position in screen/viewport-space
		virtual core::position2di projectToScreen( const core::vector3df& pos );

		///@brief add SceneNode to plot
		///@param id Unique identifier of this shape
		///@param node ISceneNode to be added
		///@return true on success
		virtual bool addShape( const core::stringc& id, scene::ISceneNode* node );

		///@brief add 2d text
		///@param id Unique identifier of this text-shape
		///@param name Name of the ISceneNode
		///@return true on success
		virtual bool addText(
			const core::stringc& id,
			const core::stringw& text,
			const core::position2di& pos,
			s32 hAlign = -1,
			s32 vAlign = -1,
			const video::SColor& color = video::SColor(0,0,0,0),
			gui::IGUIFont* font = 0 );

		///@brief add 3d text
		///@param id Unique identifier of this text-shape
		///@param name Name of the ISceneNode
		///@return true on success
		virtual bool addText(
			const core::stringc& id,
			const core::stringw& text,
			const core::vector3df& pos,
			s32 hAlign = -1,
			s32 vAlign = -1,
			const video::SColor& color = video::SColor(0,0,0,0),
			gui::IGUIFont* font = 0 );

		///@brief get used GUIEnvironment
		virtual gui::IGUIEnvironment* getGUIEnvironment( )
		{
			return Environment;
		}

		///@brief get used SceneManager
		virtual scene::ISceneManager* getSceneManager( )
		{
			return SceneManager;
		}

		///@brief get used Camera
		virtual scene::ICameraSceneNode* getCameraSceneNode( )
		{
			return Camera;
		}

		///@brief set ZoomRect
		virtual void setZoomRect( const core::rectf& zoomRect )
		{
			ZoomRect = zoomRect;
		}

		///@brief get ZoomRect
		virtual core::rectf getZoomRect( ) const
		{
			return ZoomRect;
		}

		///@brief enable/disable ClearColor
		virtual void setDrawBackground( const bool& value )
		{
			IsDrawBackground = value;
		}

		///@brief set ClearColor
		virtual void setBackgroundColor( const video::SColor& color )
		{
			BackgroundColor = color;
		}

		///@brief get ClearColor
		virtual video::SColor getBackgroundColor() const
		{
			return BackgroundColor;
		}

		///@brief get TextColor
		virtual video::SColor getTextColor() const
		{
			return TextColor;
		}

		///@brief get TextFont
		virtual gui::IGUIFont* getTextFont() const
		{
			return TextFont;
		}

		// ///@brief Updates the absolute position, splits text if required
		// virtual void updateAbsolutePosition();

		///@brief Writes attributes of the element.
		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const;

		///@brief Reads attributes of the element
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

	protected:

		///@brief send some gui event to parent
		void sendGuiEvent(EGUI_EVENT_TYPE type);

		///@brief handle keyboard events
		bool OnKey(const SEvent& event);

		///@brief handle mouse events
		bool OnMouse(const SEvent& event);


	private:
//		IGUIElement* ContentPane;
//		IGUIScrollBar* ScrollbarV;
//		IGUIScrollBar* ScrollbarH;
//		IGUIButton* ButtonZoomReset;
//		IGUIButton* ButtonZoomWindow;
//		IGUIStaticText* LabelZoomRectXMin;
//		IGUIStaticText* LabelZoomRectYMin;
//		IGUIStaticText* LabelZoomRectXMax;
//		IGUIStaticText* LabelZoomRectYMax;
//		IGUIEditBox* EditZoomRectXMin;
//		IGUIEditBox* EditZoomRectYMin;
//		IGUIEditBox* EditZoomRectXMax;
//		IGUIEditBox* EditZoomRectYMax;

		scene::ISceneManager* SceneManager;
		scene::ISceneNode* Root;
		scene::ICameraSceneNode* Camera;

		core::rect<f32> ZoomRect;

		///@brief Override color for the interface
		bool IsDrawBackground;
		video::SColor BackgroundColor;

		video::SColor TextColor;
		gui::IGUIFont* TextFont;

		bool IsDrawGrid;
		video::SColor GridColor;
		video::SColor SubGridColor;

		core::array<Shape> Shapes;
		core::array<SText*> Texts;

		bool IsMouseOver;

	};


} // end namespace gui
} // end namespace irr

#endif // __IRR_EXT_C_GUI_PLOT_H__
