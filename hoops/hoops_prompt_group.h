/******************************************************************************
 *   File name: hoops_prompt_group.h                                          *
 *                                                                            *
 * Description: Conveniece prompter for simple parameter file needs.          *
 *                                                                            *
 *    Language: C++                                                           *
 *                                                                            *
 *      Author: James Peachey, for HEASARC/GSFC/NASA                          *
 *                                                                            *
 *  Change log: see CVS Change log at the end of the file.                    *
 ******************************************************************************/
#ifndef HOOPS_PROMPT_GROUP_H
#define HOOPS_PROMPT_GROUP_H

////////////////////////////////////////////////////////////////////////////////
// C++ header files.
////////////////////////////////////////////////////////////////////////////////
#include "hoops/hoops.h"
#include "hoops/hoops_group.h"
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
  class EXPSYM ParPromptGroup : public IParGroup {
    public:
      ParPromptGroup(int argc, char * argv[]);
      ParPromptGroup(const ParPromptGroup & group);

      virtual ~ParPromptGroup();

      virtual IParGroup & operator =(const ParPromptGroup & g);
      virtual IParGroup & operator =(const IParGroup & g);

      virtual IPar & operator [](const std::string & pname) const;

      virtual IPar & Find(const std::string & pname) const;
      virtual IParGroup & Clear();
      virtual IParGroup & Add(IPar * p);
      virtual IParGroup & Remove(IPar * p);
      virtual IParGroup & Remove(const std::string & pname);

      virtual GenParItor begin();
      virtual ConstGenParItor begin() const;
      virtual GenParItor end();
      virtual ConstGenParItor end() const;

      virtual IParGroup * Clone() const;

      // File-like methods:
      void Load();
      void Save() const;

      // Prompt-like methods:
      ParPromptGroup & Prompt();
      ParPromptGroup & Prompt(const std::string & pname);

    private:
      IParFile * mFile;
      IParPrompt * mPrompter;
      IParGroup * mGroup;
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
 * Revision 1.1  2004/03/15 15:00:52  peachey
 * New wrapper class which handles simplest use case for getting parameters.
 *
 ******************************************************************************/