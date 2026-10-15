/******************************************************************************
 *   File name: hoops_ballistic.h                                             *
 *                                                                            *
 * Description: Conveniece wrappers for simple parameter file access.         *
 *                                                                            *
 *    Language: C++                                                           *
 *                                                                            *
 *      Author: James Peachey, for HEASARC/GSFC/NASA                          *
 *                                                                            *
 *  Change log: see CVS Change log at the end of the file.                    *
 ******************************************************************************/
#ifndef HOOPS_BALLISTIC_H
#define HOOPS_BALLISTIC_H

////////////////////////////////////////////////////////////////////////////////
// C++ header files.
////////////////////////////////////////////////////////////////////////////////
#include "hoops/hoops.h"
#include "hoops/hoops_ape_factory.h"
#include "hoops/hoops_group.h"
#include "hoops/hoops_prompt_group.h"
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
  ParPromptGroup::ParPromptGroup(int argc, char * argv[],
    const std::string & comp_name): IParGroup(), mFile(0),
    mPrompter(0) {
    // Use comp_name if one was supplied to find the parameter file, otherwise
    // use argv[0].
    if (comp_name.empty()) mFile = HoopsApeFileFactory().NewIParFile(argv[0]);
    else mFile = HoopsApeFileFactory().NewIParFile(comp_name);

    // Create a new prompter object:
    mPrompter = HoopsApePromptFactory().NewIParPrompt(argc, argv, comp_name);

    // Get a reference to the prompter's group:
    mGroup = &mPrompter->Group();
  }

  ParPromptGroup::ParPromptGroup(const ParPromptGroup & group): IParGroup(),
    mFile(0), mPrompter(0) {
    mFile = group.mFile->Clone();
    mPrompter = group.mPrompter->Clone();
    mGroup = &mPrompter->Group();
  }

  ParPromptGroup::~ParPromptGroup() {
    // DON'T delete mGroup! It is owned by mPrompter!
    delete mPrompter;
    delete mFile;
  }

  auto ParPromptGroup::operator =(const ParPromptGroup & g) -> IParGroup & {
    *mGroup = *g.mGroup;
    return *this;
  }

  auto ParPromptGroup::operator =(const IParGroup & g) -> IParGroup & {
    *mGroup = g;
    return *this;
  }

  auto ParPromptGroup::operator [](const std::string & pname) const -> IPar & {
    return mGroup->operator [](pname);
  }

  auto ParPromptGroup::Find(const std::string & pname) const -> IPar & {
    return mGroup->Find(pname);
  }

  auto ParPromptGroup::Clear() -> IParGroup & {
    mGroup->Clear();
    return *this;
  }

  auto ParPromptGroup::Add(IPar * p) -> IParGroup & {
    throw Hexception(PAR_UNSUPPORTED,
      "Editing Ape-based prompt group not supported", __FILE__, __LINE__);
    mGroup->Add(p);
    return *this;
  }

  auto ParPromptGroup::Remove(IPar * p) -> IParGroup & {
    throw Hexception(PAR_UNSUPPORTED,
      "Editing Ape-based prompt group not supported", __FILE__, __LINE__);
    mGroup->Remove(p);
    return *this;
  }

  auto ParPromptGroup::Remove(const std::string & pname) -> IParGroup & {
    throw Hexception(PAR_UNSUPPORTED,
      "Editing Ape-based prompt group not supported", __FILE__, __LINE__);
    mGroup->Remove(pname);
    return *this;
  }

  auto ParPromptGroup::begin() -> GenParItor {
    return mGroup->begin();
  }

  auto ParPromptGroup::begin() const -> ConstGenParItor {
    return (const_cast<const IParGroup *>(mGroup))->begin();
  }

  auto ParPromptGroup::end() -> GenParItor {
    return mGroup->end();
  }

  auto ParPromptGroup::end() const -> ConstGenParItor {
    return (const_cast<const IParGroup *>(mGroup))->end();
  }

  auto ParPromptGroup::Clone() const -> IParGroup * { return new ParPromptGroup(*this); }

  auto ParPromptGroup::Prompt() -> ParPromptGroup & {
    mPrompter->Prompt();
    return *this;
  }

  auto ParPromptGroup::Prompt(const std::string & pname) -> ParPromptGroup & {
    mPrompter->Prompt(pname);
    return *this;
  }

  void ParPromptGroup::Load() {
    mFile->Load();
    mPrompter->Group() = mFile->Group();
  }

  void ParPromptGroup::Save() const {
    mFile->Group() = mPrompter->Group();
    mFile->Save();
  }
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
 * Revision 1.6  2007/02/15 21:46:21  peachey
 * Changes to use Ape implementation instead of PIL.
 *
 * Revision 1.5  2004/09/21 16:48:06  peachey
 * Shorten line lengths to conform to package convention.
 *
 * Revision 1.4  2004/03/30 21:14:46  peachey
 * Allow PILParPrompt and ParPromptGroup constructors to accept optional
 * component name which is then used in lieu of argv[0]
 *
 * Revision 1.3  2004/03/26 22:31:54  peachey
 * Prevent client from shooting self in the foot: don't allow
 * them to add/remove parameters, because PIL can't handle that. What's more,
 * don't call Save() from the destructor: Save() can throw!
 *
 * Revision 1.2  2004/03/16 20:50:57  peachey
 * Explicitly invoke constructors for base classes to shut up compiler
 * warnings in the SLAC build.
 *
 * Revision 1.1  2004/03/15 15:00:52  peachey
 * New wrapper class which handles simplest use case for getting parameters.
 *
 ******************************************************************************/
