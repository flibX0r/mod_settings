#pragma once

#include "RED4ext/RTTITypes.hpp"
#include <RED4ext/RED4ext.hpp>

struct ScriptProperty;

enum class EDefinitionType : char {
  Type = 0x0,
  Class = 0x1,
  Constant = 0x2,
  Enum = 0x3,
  Bitfield = 0x4,
  Function = 0x5,
  Parameter = 0x6,
  LocalVar = 0x7,
  Property = 0x8,
  SourceFile = 0x9,
};

enum class EScriptType : long {
  Simple = 0x0,
  Cls = 0x1,
  Handle = 0x2,
  WeakHandle = 0x3,
  Array = 0x4,
  NativeArray = 0x5
};

enum class EVisibility : char {
  Public = 0x0,
  Protected = 0x1,
  Private = 0x2,
};

struct ScriptClass;

struct ScriptDefinition {
  virtual RED4ext::Memory::IAllocator *dstr() = 0;
  virtual void sub_08() = 0;
  virtual EDefinitionType GetDefinitionType() = 0;
  virtual EVisibility GetVisibility() = 0;
  virtual ScriptClass GetParent() = 0;
  virtual void sub_28() = 0;
  virtual bool IsNative() = 0;

  RED4ext::CName name;
  uint64_t unk10;
};

struct ScriptType : ScriptDefinition {
  RED4ext::CBaseRTTIType *rttiType;
  ScriptClass *innerType;
  uint32_t unk28;
  EScriptType type;
};

struct ScriptClassFlags {
  uint32_t isNative : 1;
  uint32_t isAbstract : 1;
  uint32_t isFinal : 1;
  uint32_t isStruct : 1;
  uint32_t hasFunctions : 1;
  uint32_t hasFields : 1;
  uint32_t isImportOnly : 1;
  uint32_t isTestOnly : 1;
  uint32_t hasOverrides : 1;
  uint32_t unk200 : 1;
  uint32_t unk400 : 1;
};

struct ScriptClass : ScriptDefinition {
  RED4ext::CClass *rttiType;
  ScriptClass *parent;
  RED4ext::DynArray<ScriptProperty *> properties;
  RED4ext::DynArray<void *> overrides;
  RED4ext::DynArray<void *> functions;
  __unaligned __declspec(align(1)) RED4ext::HashMap<RED4ext::CName, RED4ext::CString> unk58;
  uint8_t visibility;
  uint8_t unk89;
  uint8_t unk8A;
  uint8_t unk8B;
  ScriptClassFlags flags;
};
RED4EXT_ASSERT_SIZE(ScriptClass, 0x90);
// char (*__kaboom)[offsetof(ScriptClass, rttiType)] = 1;