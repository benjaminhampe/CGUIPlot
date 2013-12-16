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
	typedef core::stringc String;

	typedef core::array<String> ArrayOfStrings;

	enum E_ATTRIBUTES
	{
		EAOF_NONE = 0,
		EAOF_UNKNOWN = 1,
		EAOF_PUBLIC = 1<<1,
		EAOF_PROTECTED = 1<<2,
		EAOF_PRIVATE = 1<<3,
		EAOF_STATIC = 1<<4,
		EAOF_CONST = 1<<5,
		EAOF_VIRTUAL = 1<<6,
		EAOF_INLINE = 1<<7
//		EAOF_LVALUE = 1<<8
//		EAOF_REFERENCE = 1<<9
//		EAOF_POINTER = 1<<10
//		EAOF_RValue = 1<<11
//		EAOF_VARIABLE_DEF = 1<<11
//		EAOF_VARIABLE_DECL = 1<<11
//		EAOF_FUNCTION_DEF = 1<<11
//		EAOF_FUNCTION_DECL = 1<<11
//		EAOF_MACRO_DEF = 1<<11
//		EAOF_CLASS = 1<<11
//		EAOF_STRUCT = 1<<11
//		EAOF_INTERFACE = 1<<11
//		EAOF_INTERFACE = 1<<11
	};



	class SAttributes
	{
		public:
		E_ATTRIBUTES Attributes;

		//C++:
		//Bit setzen: var |= 1<<Bitnummer; /* Bitnr ab 0 */
		//Bit loeschen: var &= ~(1<<Bitnummer);

		///@brief Default constructor
		SAttributes()
		{
			Attributes = EAOF_NONE;
			Attributes |= EAOF_PUBLIC;
			Attributes |= EAOF_INLINE;
			Attributes |= EAOF_VIRTUAL;
		}

		///@brief Default constructor
		virtual ~SAttributes()
		{
		}

		///@brief Clear All Flags
		virtual SAttributes& clear()
		{
			Attributes = EAOF_NONE;
			return *this;
		}

		///@brief Set public
		virtual SAttributes& setUnknown()
		{
			Attributes |= EAOF_UNKNOWN;
			return *this;
		}

		///@brief Set public
		virtual SAttributes& setPublic()
		{
			Attributes |= EAOF_PUBLIC;
			Attributes &= ~(EAOF_PRIVATE + EAOF_PROTECTED + EAOF_STATIC );
			return *this;
		}

		///@brief Set protected
		virtual SAttributes& setProtected()
		{
			Attributes |= EAOF_PROTECTED;
			Attributes &= ~(EAOF_PUBLIC + EAOF_PRIVATE + EAOF_STATIC );
			return *this;
		}

		///@brief Set private
		virtual SAttributes& setPrivate()
		{
			Attributes |= EAOF_PRIVATE;
			Attributes &= ~(EAOF_PUBLIC + EAOF_PROTECTED + EAOF_STATIC );
			return *this;
		}

		///@brief Set static
		virtual SAttributes& setStatic()
		{
			Attributes |= (EAOF_PUBLIC + EAOF_STATIC);
			Attributes &= ~(EAOF_PROTECTED + EAOF_PRIVATE );
			return *this;
		}

		///@brief Set virtual
		virtual SAttributes& setVirtual()
		{
			Attributes |= EAOF_VIRTUAL;
			return *this;
		}

		///@brief Set inline
		virtual SAttributes& setInline()
		{
			Attributes |= EAOF_INLINE;
			Attributes &= ~(EAOF_STATIC);
			return *this;
		}

		///@brief Get value member-variable.
		virtual bool isPublic() const
		{
			if ( Attributes & EAOF_PUBLIC )
				return true;
			else
				return false;
		}

		///@brief Get value member-variable.
		virtual bool isProtected() const
		{
			if ( Attributes & EAOF_PROTECTED )
				return true;
			else
				return false;
		}

		///@brief Get value member-variable.
		virtual bool isPrivate() const
		{
			if ( Attributes & EAOF_PRIVATE )
				return true;
			else
				return false;
		}

		///@brief Get value member-variable.
		virtual bool isStatic() const
		{
			if ( Attributes & EAOF_STATIC )
				return true;
			else
				return false;
		}

		///@brief Get value member-variable.
		virtual bool isVirtual() const
		{
			if ( Attributes & EAOF_VIRTUAL )
				return true;
			else
				return false;
		}

		///@brief Get value member-variable.
		virtual bool isInline() const
		{
			if ( Attributes & EAOF_INLINE )
				return true;
			else
				return false;
		}
	};


	struct SVariable : IReferenceCounted
	{
		String Name;
		String Type;
		String InitValue;
		SAttributes Attributes;

		SVariable(
			const String& name = String("Variable_"),
			const String& type = String("u32"),
			const String& init = String("0"),
			const SAttributes& attribs = SAttributes())
		: Name(name), Type(type), InitValue(init), Attributes(attribs)
		{
		}
	};



	struct SMemberVariable : SVariable
	{
		bool HasGetter;
		bool HasSetter;
		bool HasConstGetter;

		SMemberVariable(
			const String& name = String("NumberOfSomething"),
			const String& type = String("u32"),
			const String& init = String("0"),
			const SAttributes& attribs = SAttributes().setVirtual().setInline(),
			bool hasGetter = true,
			bool hasConstGetter = true,
			bool hasSetter = true )
		: SVariable( name, type, init, attribs)
		, HasGetter(hasGetter), HasConstGetter(hasConstGetter), HasSetter(hasSetter)
		{

		}
	};

	struct SFunction : IReferenceCounted
	{

		String Name;
		String ReturnType;
		String Visibility;	// public, protected, private
		SAttributes Attributes;

		typedef core::array<SVariable> SParameterList;

		SParameterList ParamList;

		SFunction(
			const String& name = String("NumberingSomething"), // class IUnknown
			const String& returntype = String("u32"), // types: struct:"struct S", class:"class C", int[erface]:"class I"
			const SAttributes& attributes = SAttributes())
		: Name(name)
		, ReturnType(returntype)
		, Attributes(attributes)
		{

		}

		~SFunction()
		{
			ParamList.clear();
		}

		virtual void addParam(
			const String& name = String("Variable_"),
			const String& type = String("u32"),
			const String& init = String("0"),
			const SAttributes& attribs = SAttributes()	)
		{
			ParamList.push_back( SVariable(name, type, init, attribs ) );
		}
	};

	typedef SFunction SMemberFunction;

	struct SClass
	{
		String Name;
		SAttributes Attributes;

		core::array<SMemberVariable> MemberVars;
		core::array<SMemberFunction> MemberFuns;

		void addClassMember( const SMemberVariable& my_var )
		{
			MemberVars.push_back( my_var );
		}

		void addClassMember( const SMemberFunction& my_fun )
		{
			MemberFuns.push_back( my_fun );
		}
	};


	///@brief class CGUIClassBuilder
	class CGUIClassBuilder : public IGUIElement
	{
	private:
		core::array<SClass> Classes;

	public:
//		virtual String addClass(
//			const String& class_name = String("Unknown"), // class IUnknown
//			const String& class_type = String("int"), // types: struct:"struct S", class:"class C", int[erface]:"class I"
//			const String& class_visibility = String("public"), // visibility: public, protected, private
//			const String& base_list = String("public IReferenceCounted"), // visibility: public, protected, private

//		virtual String addMemberFunction(
//			const String& class = String("Unknown"), // class IUnknown
//			const String& type = String("int"), // types: struct:"struct S", class:"class C", int[erface]:"class I"
//			const String& cType = String("class"), // visibility: public, protected, private

//		virtual String addAttribute(
//			const String& attr_name = String("Atrribute_000"), // class IUnknown
//			const String& attr_type = String("u32"), // types: struct:"struct S", class:"class C", int[erface]:"class I"
//			const String& init_list = String("0"), // visibility: public, protected, private
//			const bool& create_setter = false,
//			const bool& create_setter = false,


		///@brief class constructor
		///@param smgr ISceneManager
		///@param env IGUIEnvironment
		///@param parent Parent element of this element
		///@param id Id of this element
		///@param rectangle Size of this element
		CGUIClassBuilder(
			// scene::ISceneManager* smgr,
			IGUIEnvironment* env,
			IGUIElement* parent,
			s32 id,
			const core::rect<s32>& rectangle );

		///@brief class destructor
		virtual ~CGUIClassBuilder();


		///@brief called if an event happened.
		virtual bool OnEvent(const SEvent& event);

		///@brief draws the element and its children
		virtual void draw();

/// PlotManager

		///@brief get Pointer to single class.
		///@param index Index of class-array.
		///@return Pointer to single class.
		virtual u32 getClassCount() const
		{
			return Classes.size();
		}

		///@brief get Pointer to single clas.
		///@param index Index of class-array.
		///@return Pointer to single class.
		virtual SClass& getClass( u32 index = 0 )
		{
			_IRR_DEBUG_BREAK_IF( index >= getClassCount() )
			return Classes[index];
		}

		///@brief add Class
		///@param id Unique identifier of this text-shape
		///@param name Name of the ISceneNode
		///@return true on success
		virtual bool addClass( const SClass& other)
		{
			Classes.push_back( other );
		}

/// Other

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

//		///@brief get used SceneManager
//		virtual scene::ISceneManager* getSceneManager( )
//		{
//			return SceneManager;
//		}

//		///@brief get used Camera
//		virtual scene::ICameraSceneNode* getCameraSceneNode( )
//		{
//			return Camera;
//		}

		///@brief Writes attributes of the element.
		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const;

		///@brief Reads attributes of the element
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

		// ///@brief Updates the absolute position, splits text if required
		// virtual void updateAbsolutePosition();

	protected:
	private:
		// scene::ISceneManager* SceneManager;

		///@brief Override color for the interface
		gui::IGUIFont* Font;

	};


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

} // end namespace gui
} // end namespace irr

#endif // __IRR_EXT_C_GUI_PLOT_H__
