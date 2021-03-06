// Copyright 2017 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include "DolphinQt/Config/Mapping/MappingWidget.h"

class QComboBox;
class WiimoteEmuExtension;

class PrimeHackEmuGeneral final : public MappingWidget
{
public:
  explicit PrimeHackEmuGeneral(MappingWindow* window);

  InputConfig* GetConfig() override;

private:
  void LoadSettings() override;
  void SaveSettings() override;

  void CreateMainLayout();
  void Connect(MappingWindow* window);
  void OnAttachmentChanged(int index);
  void ConfigChanged();

  WiimoteEmuExtension* m_extension_widget;
};
