// Copyright 2017 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "InputCommon/ControllerEmu/ControlGroup/Tilt.h"

#include <string>

#include "Common/Common.h"
#include "Common/MathUtil.h"

#include "InputCommon/ControlReference/ControlReference.h"
#include "InputCommon/ControllerEmu/Control/Control.h"
#include "InputCommon/ControllerEmu/Control/Input.h"
#include "InputCommon/ControllerEmu/Setting/NumericSetting.h"

namespace ControllerEmu
{
Tilt::Tilt(const std::string& name_) : ReshapableInput(name_, name_, GroupType::Tilt)
{
  controls.emplace_back(std::make_unique<Input>(Translate, _trans("Forward")));
  controls.emplace_back(std::make_unique<Input>(Translate, _trans("Backward")));
  controls.emplace_back(std::make_unique<Input>(Translate, _trans("Left")));
  controls.emplace_back(std::make_unique<Input>(Translate, _trans("Right")));

  controls.emplace_back(std::make_unique<Input>(Translate, _trans("Modifier")));

  AddSetting(&m_max_angle_setting,
             {_trans("Angle"),
              // i18n: The symbol/abbreviation for degrees (unit of angular measure).
              _trans("°"),
              // i18n: Refers to tilting an emulated Wii Remote.
              _trans("Maximum tilt angle.")},
             85, 0, 180);

  AddSetting(&m_max_rotational_velocity,
             {_trans("Velocity"),
              // i18n: The symbol/abbreviation for hertz (cycles per second).
              _trans("Hz"),
              // i18n: Refers to tilting an emulated Wii Remote.
              _trans("Peak angular velocity (measured in turns per second).")},
             7, 1, 50);
}

Tilt::ReshapeData Tilt::GetReshapableState(bool adjusted)
{
  const ControlState y = controls[0]->control_ref->State() - controls[1]->control_ref->State();
  const ControlState x = controls[3]->control_ref->State() - controls[2]->control_ref->State();

  // Return raw values. (used in UI)
  if (!adjusted)
    return {x, y};

  const ControlState modifier = controls[4]->control_ref->State();

  return Reshape(x, y, modifier);
}

Tilt::StateData Tilt::GetState()
{
  return GetReshapableState(true);
}

ControlState Tilt::GetGateRadiusAtAngle(double ang) const
{
  const ControlState max_tilt_angle = m_max_angle_setting.GetValue() / 180;
  return SquareStickGate(max_tilt_angle).GetRadiusAtAngle(ang);
}

ControlState Tilt::GetDefaultInputRadiusAtAngle(double ang) const
{
  return SquareStickGate(1.0).GetRadiusAtAngle(ang);
}

ControlState Tilt::GetMaxRotationalVelocity() const
{
  return m_max_rotational_velocity.GetValue() * MathUtil::TAU;
}

}  // namespace ControllerEmu
