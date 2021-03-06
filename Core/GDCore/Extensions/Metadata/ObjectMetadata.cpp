/*
 * GDevelop Core
 * Copyright 2008-2016 Florian Rival (Florian.Rival@gmail.com). All rights
 * reserved. This project is released under the MIT License.
 */
#include "ObjectMetadata.h"
#include <algorithm>
#include <iostream>
#include "GDCore/Extensions/Metadata/ExpressionMetadata.h"
#include "GDCore/Extensions/Metadata/InstructionMetadata.h"
#include "GDCore/Project/Object.h"

namespace gd {

ObjectMetadata::ObjectMetadata(const gd::String& extensionNamespace_,
                               const gd::String& name_,
                               const gd::String& fullname_,
                               const gd::String& description_,
                               const gd::String& icon24x24,
                               std::shared_ptr<gd::Object> blueprintObject_)
    : extensionNamespace(extensionNamespace_),
      blueprintObject(blueprintObject_) {
  name = name_;
#if defined(GD_IDE_ONLY)
  SetFullName(gd::String(fullname_));
  SetDescription(gd::String(description_));
  iconFilename = icon24x24;
#endif
  createFunPtr =
      [blueprintObject_](gd::String name) -> std::unique_ptr<gd::Object> {
    if (blueprintObject_ == std::shared_ptr<gd::Object>()) {
      std::cout
          << "Error: Unable to create object. Have you declared an extension "
             "(or ObjectMetadata) without specifying an object as blueprint?"
          << std::endl;
      return nullptr;
    }

    std::unique_ptr<gd::Object> newObject = blueprintObject_->Clone();
    newObject->SetName(name);
    return newObject;
  };
}

ObjectMetadata::ObjectMetadata(const gd::String& extensionNamespace_,
                               const gd::String& name_,
                               const gd::String& fullname_,
                               const gd::String& description_,
                               const gd::String& icon24x24,
                               CreateFunPtr createFunPtrP)
    : extensionNamespace(extensionNamespace_) {
  name = name_;
#if defined(GD_IDE_ONLY)
  SetFullName(gd::String(fullname_));
  SetDescription(gd::String(description_));
  iconFilename = icon24x24;
#endif
  createFunPtr = createFunPtrP;
}

gd::InstructionMetadata& ObjectMetadata::AddCondition(
    const gd::String& name,
    const gd::String& fullname,
    const gd::String& description,
    const gd::String& sentence,
    const gd::String& group,
    const gd::String& icon,
    const gd::String& smallicon) {
#if defined(GD_IDE_ONLY)
  gd::String nameWithNamespace =
      extensionNamespace.empty() ? name : extensionNamespace + name;
  conditionsInfos[nameWithNamespace] = InstructionMetadata(extensionNamespace,
                                                           nameWithNamespace,
                                                           fullname,
                                                           description,
                                                           sentence,
                                                           group,
                                                           icon,
                                                           smallicon)
                                           .SetHelpPath(GetHelpPath())
                                           .SetIsObjectInstruction();
  return conditionsInfos[nameWithNamespace];
#endif
}

gd::InstructionMetadata& ObjectMetadata::AddAction(
    const gd::String& name,
    const gd::String& fullname,
    const gd::String& description,
    const gd::String& sentence,
    const gd::String& group,
    const gd::String& icon,
    const gd::String& smallicon) {
#if defined(GD_IDE_ONLY)
  gd::String nameWithNamespace =
      extensionNamespace.empty() ? name : extensionNamespace + name;
  actionsInfos[nameWithNamespace] = InstructionMetadata(extensionNamespace,
                                                        nameWithNamespace,
                                                        fullname,
                                                        description,
                                                        sentence,
                                                        group,
                                                        icon,
                                                        smallicon)
                                        .SetHelpPath(GetHelpPath())
                                        .SetIsObjectInstruction();
  return actionsInfos[nameWithNamespace];
#endif
}

gd::ExpressionMetadata& ObjectMetadata::AddExpression(
    const gd::String& name,
    const gd::String& fullname,
    const gd::String& description,
    const gd::String& group,
    const gd::String& smallicon) {
#if defined(GD_IDE_ONLY)
  // Be careful, objects expression do not have namespace ( not necessary as
  // objects inherits from only one derived object )
  expressionsInfos[name] =
      ExpressionMetadata(
          extensionNamespace, name, fullname, description, group, smallicon)
          .SetHelpPath(GetHelpPath());

  return expressionsInfos[name];
#endif
}

gd::ExpressionMetadata& ObjectMetadata::AddStrExpression(
    const gd::String& name,
    const gd::String& fullname,
    const gd::String& description,
    const gd::String& group,
    const gd::String& smallicon) {
#if defined(GD_IDE_ONLY)
  // Be careful, objects expression do not have namespace ( not necessary as
  // objects inherits from only one derived object )
  strExpressionsInfos[name] =
      ExpressionMetadata(
          extensionNamespace, name, fullname, description, group, smallicon)
          .SetHelpPath(GetHelpPath());

  return strExpressionsInfos[name];
#endif
}

ObjectMetadata& ObjectMetadata::SetFullName(const gd::String& fullname_) {
#if defined(GD_IDE_ONLY)
  fullname = fullname_;
#endif
  return *this;
}

ObjectMetadata& ObjectMetadata::SetHelpUrl(const gd::String& helpUrl_) {
#if defined(GD_IDE_ONLY)
  helpUrl = helpUrl_;
#endif
  return *this;
}

ObjectMetadata& ObjectMetadata::SetDescription(const gd::String& description_) {
#if defined(GD_IDE_ONLY)
  description = description_;
#endif
  return *this;
}

ObjectMetadata& ObjectMetadata::SetIncludeFile(const gd::String& includeFile) {
#if defined(GD_IDE_ONLY)
  includeFiles.clear();
  includeFiles.push_back(includeFile);
#endif
  return *this;
}
ObjectMetadata& ObjectMetadata::AddIncludeFile(const gd::String& includeFile) {
#if defined(GD_IDE_ONLY)
  if (std::find(includeFiles.begin(), includeFiles.end(), includeFile) ==
      includeFiles.end())
    includeFiles.push_back(includeFile);
#endif
  return *this;
}

}  // namespace gd
