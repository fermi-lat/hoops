/******************************************************************************
 *   File name: hoops_par.h                                                   *
 *                                                                            *
 * Description: Declaration for standard parameter type.                      *
 *                                                                            *
 *    Language: C++                                                           *
 *                                                                            *
 *      Author: James Peachey, for HEASARC/GSFC/NASA                          *
 *                                                                            *
 *  Change log: see CVS Change log at the end of the file.                    *
 ******************************************************************************/
#ifndef HOOPS_PAR_H
#define HOOPS_PAR_H

////////////////////////////////////////////////////////////////////////////////
// C++ header files.
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include "hoops/hoops.h"
////////////////////////////////////////////////////////////////////////////////

#ifndef EXPSYM
#ifdef WIN32
#define EXPSYM __declspec(dllexport)
#else
#define EXPSYM
#endif
#endif

namespace hoops {

  //////////////////////////////////////////////////////////////////////////////
  // Constants.
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Type declarations/definitions.
  //////////////////////////////////////////////////////////////////////////////
  class EXPSYM Par : public IPar {
    public:
      // Constructors.
      Par();
      Par(const Par & p);
      Par(const IPar & p);
      Par(const std::string & name, const std::string & type,
          const std::string & mode, const std::string & value,
          const std::string & min = "", const std::string & max = "",
          const std::string & prompt = "", const std::string & comment = "");

      // Destructor.
      virtual ~Par();

      // Assignments.
      //! Assign value only of parameter.
      // If deriving from Par, define operator = for the subclass
      // exactly the same as for Par, and override From method(s)
      // to change the assignment behavior (if necessary).
      virtual Par & operator =(const Par & p)
        { From(p); return *this; }
      virtual Par & operator =(const IPar & p)
        { From(p); return *this; }
      virtual Par & operator =(const IPrim & p)
        { From(p); return *this; }
      virtual Par & operator =(const bool & p)
        { From(p); return *this; }
      virtual Par & operator =(const char & p)
         { From(p); return *this; }
      virtual Par & operator =(const signed char & p)
         { From(p); return *this; }
      virtual Par & operator =(const short & p)
         { From(p); return *this; }
      virtual Par & operator =(const int & p)
         { From(p); return *this; }
      virtual Par & operator =(const long & p)
         { From(p); return *this; }
      virtual Par & operator =(const unsigned char & p)
        { From(p); return *this; }
      virtual Par & operator =(const unsigned short & p)
        { From(p); return *this; }
      virtual Par & operator =(const unsigned int & p)
        { From(p); return *this; }
      virtual Par & operator =(const unsigned long & p)
        { From(p); return *this; }
      virtual Par & operator =(const float & p)
        { From(p); return *this; }
      virtual Par & operator =(const double & p)
        { From(p); return *this; }
      virtual Par & operator =(const long double & p)
        { From(p); return *this; }
      virtual Par & operator =(const char * p)
        { From(p); return *this; }
      virtual Par & operator =(const std::string & p)
        { From(p); return *this; }

      virtual void From(const IPar & p);
      virtual void From(const IPrim & p);
      virtual void From(const bool & p);
      virtual void From(const char & p);
      virtual void From(const signed char & p);
      virtual void From(const short & p);
      virtual void From(const int & p);
      virtual void From(const long & p);
      virtual void From(const unsigned char & p);
      virtual void From(const unsigned short & p);
      virtual void From(const unsigned int & p);
      virtual void From(const unsigned long & p);
      virtual void From(const float & p);
      virtual void From(const double & p);
      virtual void From(const long double & p);
      virtual void From(const char * p);
      virtual void From(const std::string & p);

      // Conversions.
      virtual operator bool () const;
      virtual operator char () const;
      virtual operator signed char () const;
      virtual operator short () const;
      virtual operator int () const;
      virtual operator long () const;
      virtual operator unsigned char () const;
      virtual operator unsigned short () const;
      virtual operator unsigned int () const;
      virtual operator unsigned long () const;
      virtual operator float () const;
      virtual operator double () const;
      virtual operator long double () const;
      virtual operator const char *() const;
      virtual operator const std::string &() const;

      virtual void To(bool & p) const;
      virtual void To(char & p) const;
      virtual void To(signed char & p) const;
      virtual void To(short & p) const;
      virtual void To(int & p) const;
      virtual void To(long & p) const;
      virtual void To(unsigned char & p) const;
      virtual void To(unsigned short & p) const;
      virtual void To(unsigned int & p) const;
      virtual void To(unsigned long & p) const;
      virtual void To(float & p) const;
      virtual void To(double & p) const;
      virtual void To(long double & p) const;
      virtual void To(std::string & p) const;

      virtual Par * Clone() const
        { return new Par(*this); }

      // Member access.
      virtual const std::string & Name() const { return mName; }
      virtual const std::string & Type() const { return mType; }
      virtual const std::string & Mode() const { return mMode; }
      virtual const std::string & Value() const;
      virtual const std::string & Min() const
        { return mMin; }
      virtual const std::string & Max() const
        { return mMax; }
      virtual const std::string & Prompt() const { return mPrompt; }
      virtual const std::string & Comment() const { return mComment; }
      virtual const IPrim * PrimValue() const { return mValue; }

      virtual Par & SetName(const std::string & s)
        { mName = s; return *this; }
      virtual Par & SetType(const std::string & s)
        { mType = s; return *this; }
      virtual Par & SetMode(const std::string & s)
        { mMode = s; return *this; }
      virtual Par & SetValue(const std::string & s)
        { From(s); return *this; }
      virtual Par & SetMin(const std::string & s)
        { mMin = s; return *this; }
      virtual Par & SetMax(const std::string & s)
        { mMax = s; return *this; }
      virtual Par & SetPrompt(const std::string & s)
        { mPrompt = s; return *this; }
      virtual Par & SetComment(const std::string & s)
        { mComment = s; return *this; }

    protected:
      template <typename T>
      static void ConvertFrom(T p, IPrim *& dest, const std::string & type) {
        PrimFactory Factory;
        if (dest) dest->From(p);
        // In general is find the best thing to be using here???
        else if (std::string::npos != type.find("b")) {
          dest = Factory.NewIPrim(bool()); dest->From(p);
        } else if (std::string::npos != type.find("i")) {
          dest = Factory.NewIPrim(long()); dest->From(p);
        // Important to check for type "f" before "r", because "fr" is
        // file readable. If we check first for "r", such a parameter
        // is misclassified as a float (double) value.
        } else if (std::string::npos != type.find("f") ||
          std::string::npos != type.find("s")) {
          dest = Factory.NewIPrim(std::string()); dest->From(p);
        } else if (std::string::npos != type.find("r")) {
          dest = Factory.NewIPrim(double()); dest->From(p);
        } else throw Hexception(PAR_INVALID_TYPE, "", __FILE__, __LINE__);
      }

      template <typename T>
      static void ConvertTo (IPrim * const src, T & p)
        { if (src) src->To(p); else p = T(); }

    private:
      std::string mName;
      std::string mType;
      std::string mMode;
      IPrim * mValue;
      std::string mMin;
      std::string mMax;
      std::string mPrompt;
      std::string mComment;
      mutable std::string mValString;
  };

  class EXPSYM ParFactory : public IParFactory {
    public:
      virtual ~ParFactory() {}

      virtual Par * NewIPar() { return new Par(); }
      virtual Par * NewIPar(const IPar & p)
        { return new Par(p); }
      virtual Par * NewIPar(const std::string & name, const std::string & type,
        const std::string & mode, const std::string & value,
        const std::string & min = std::string(),
        const std::string & max = std::string(),
        const std::string & prompt = std::string(),
        const std::string & comment = std::string())
        { return new Par(name, type, mode, value, min, max, prompt, comment); }
  };
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Global variable forward declarations.
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Function declarations.
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
}
#endif

/******************************************************************************
 * Revision 1.12  2004/03/12 15:40:42  peachey
 * When throwing exceptions, include the file name and
 * line number where the exception was thrown.
 *
 * Revision 1.11  2004/03/11 17:35:11  peachey
 * Remove an unneccessary error condition.
 *
 * Revision 1.10  2004/03/10 19:35:19  peachey
 * Remove throw specifications.
 *
 * Revision 1.9  2004/01/15 15:21:30  peachey
 * Bug fix: a parameter of type "fr" was being classified as a real
 * (float/double) value. This led to unexpected exceptions eventually
 * triggering abort in most programs.
 *
 * Revision 1.8  2003/11/26 18:50:03  peachey
 * Merging changes made to SLAC repository into Goddard repository.
 *
 * Revision 1.7  2003/11/13 19:29:29  peachey
 * Add preprocessor macro needed on Windows to export symbols.
 *
 * Revision 1.6  2003/11/10 18:19:45  peachey
 * Moved header files into hoops subdirectory.
 *
 * Revision 1.5  2003/06/18 18:17:30  peachey
 * Remove method to return char * because IPrim no longer supports
 * char * as a specializable type.
 *
 * Revision 1.1.1.1  2003/11/04 01:48:30  jchiang
 * First import
 *
 * Revision 1.4  2003/06/06 13:25:37  peachey
 * Restructure the header files. The files hoops_exception.h, hoops.h,
 * hoops_itor.h, hoops_pil_factory.h, and hoops_prim.h are now the
 * only public (installed) files.
 *
 * Revision 1.3  2003/05/14 15:17:06  peachey
 * Further encapsulate Prim class by hiding the templates in hoops_prim.cxx
 * and using a factory class.
 *
 * Revision 1.2  2003/04/23 17:43:49  peachey
 * Removing unneeded include statement.
 *
 * Revision 1.1  2003/04/11 19:20:38  peachey
 * New component HOOPS, an object oriented parameter interface. Low
 * level access currently uses PIL, but this can be changed.
 *
 ******************************************************************************/
