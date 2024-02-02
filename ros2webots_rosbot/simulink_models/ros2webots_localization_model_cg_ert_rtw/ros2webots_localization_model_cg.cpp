//
// File: ros2webots_localization_model_cg.cpp
//
// Code generated for Simulink model 'ros2webots_localization_model_cg'.
//
// Model version                  : 1.236
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Fri Feb  2 16:44:59 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "ros2webots_localization_model_cg.h"
#include "rtwtypes.h"
#include <cmath>
#include "ros2webots_localization_model_cg_private.h"
#include "rt_defines.h"

extern "C"
{

#include "rt_nonfinite.h"

}

// Exported data definition

// Const memory section
// Definition for custom storage class: Const
const real_T wheel_based_localization_x_initial_coord{ 0.0 };// Referenced by: '<S9>/Delay' 

// Initial x coordinate of localization using only wheel pose data
const real_T wheel_based_localization_y_initial_coord{ 0.0 };// Referenced by: '<S9>/Delay1' 

// Initial y coordinate of localization using only wheel pose data

//
// Output and update for action system:
//    '<S11>/If Action Subsystem'
//    '<S14>/If Action Subsystem'
//    '<S17>/If Action Subsystem'
//    '<S20>/If Action Subsystem'
//
void ros2webots_localization_model_cg::ros2webots_lo_IfActionSubsystem(real_T
  rtu_In1, real_T rtu_dt_data_change, real_T *rty_Out1)
{
  // Product: '<S12>/Divide'
  *rty_Out1 = rtu_In1 / rtu_dt_data_change;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = std::atan2(static_cast<real_T>(tmp), static_cast<real_T>(tmp_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }

  return y;
}

// Model step function
void ros2webots_localization_model_cg::step()
{
  real_T rtb_Gain;
  real_T rtb_Gain_i;
  real_T rtb_Multiply;
  real_T rtb_Product1_a;
  real_T rtb_Product2;
  real_T rtb_fcn5;

  // SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
  //   Delay: '<S9>/Delay'
  //   Outport: '<Root>/odometry_vector'

  ros2webots_localization_model_Y.odometry_vector[0] =
    ros2webots_localization_mode_DW.Delay_DSTATE;

  // If: '<S11>/If' incorporates:
  //   Delay: '<S11>/Delay'
  //   Inport: '<Root>/fl_wheel_pose'
  //   Inport: '<Root>/fl_wheel_pose_update_dt'
  //   Sum: '<S11>/Sum'

  if (ros2webots_localization_model_U.fl_wheel_pose_update_dt >= 0.001) {
    // Outputs for IfAction SubSystem: '<S11>/If Action Subsystem' incorporates:
    //   ActionPort: '<S12>/Action Port'

    ros2webots_lo_IfActionSubsystem
      (ros2webots_localization_model_U.fl_wheel_pose -
       ros2webots_localization_mode_DW.Delay_DSTATE_g,
       ros2webots_localization_model_U.fl_wheel_pose_update_dt, &rtb_Multiply);

    // End of Outputs for SubSystem: '<S11>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<S11>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S13>/Action Port'

    // SignalConversion generated from: '<S13>/In1' incorporates:
    //   Delay: '<S11>/Delay'
    //   Inport: '<Root>/fl_wheel_pose'
    //   Sum: '<S11>/Sum'

    rtb_Multiply = ros2webots_localization_model_U.fl_wheel_pose -
      ros2webots_localization_mode_DW.Delay_DSTATE_g;

    // End of Outputs for SubSystem: '<S11>/If Action Subsystem1'
  }

  // End of If: '<S11>/If'

  // If: '<S17>/If' incorporates:
  //   Delay: '<S17>/Delay'
  //   Inport: '<Root>/rl_wheel_pose'
  //   Inport: '<Root>/rl_wheel_pose_update_dt'
  //   Sum: '<S17>/Sum'

  if (ros2webots_localization_model_U.rl_wheel_pose_update_dt >= 0.001) {
    // Outputs for IfAction SubSystem: '<S17>/If Action Subsystem' incorporates:
    //   ActionPort: '<S18>/Action Port'

    ros2webots_lo_IfActionSubsystem
      (ros2webots_localization_model_U.rl_wheel_pose -
       ros2webots_localization_mode_DW.Delay_DSTATE_j,
       ros2webots_localization_model_U.rl_wheel_pose_update_dt, &rtb_Gain_i);

    // End of Outputs for SubSystem: '<S17>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<S17>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S19>/Action Port'

    // SignalConversion generated from: '<S19>/In1' incorporates:
    //   Delay: '<S17>/Delay'
    //   Inport: '<Root>/rl_wheel_pose'
    //   Sum: '<S17>/Sum'

    rtb_Gain_i = ros2webots_localization_model_U.rl_wheel_pose -
      ros2webots_localization_mode_DW.Delay_DSTATE_j;

    // End of Outputs for SubSystem: '<S17>/If Action Subsystem1'
  }

  // End of If: '<S17>/If'

  // Gain: '<S4>/Gain' incorporates:
  //   Sum: '<S4>/Sum'

  rtb_Gain = (rtb_Multiply + rtb_Gain_i) * 0.5;

  // If: '<S14>/If' incorporates:
  //   Delay: '<S14>/Delay'
  //   Inport: '<Root>/fr_wheel_pose'
  //   Inport: '<Root>/fr_wheel_pose_update_dt'
  //   Sum: '<S14>/Sum'

  if (ros2webots_localization_model_U.fr_wheel_pose_update_dt >= 0.001) {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem' incorporates:
    //   ActionPort: '<S15>/Action Port'

    ros2webots_lo_IfActionSubsystem
      (ros2webots_localization_model_U.fr_wheel_pose -
       ros2webots_localization_mode_DW.Delay_DSTATE_o,
       ros2webots_localization_model_U.fr_wheel_pose_update_dt, &rtb_Gain_i);

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S16>/Action Port'

    // SignalConversion generated from: '<S16>/In1' incorporates:
    //   Delay: '<S14>/Delay'
    //   Inport: '<Root>/fr_wheel_pose'
    //   Sum: '<S14>/Sum'

    rtb_Gain_i = ros2webots_localization_model_U.fr_wheel_pose -
      ros2webots_localization_mode_DW.Delay_DSTATE_o;

    // End of Outputs for SubSystem: '<S14>/If Action Subsystem1'
  }

  // End of If: '<S14>/If'

  // If: '<S20>/If' incorporates:
  //   Delay: '<S20>/Delay'
  //   Inport: '<Root>/rr_wheel_pose'
  //   Inport: '<Root>/rr_wheel_pose_update_dt'
  //   Sum: '<S20>/Sum'

  if (ros2webots_localization_model_U.rr_wheel_pose_update_dt >= 0.001) {
    // Outputs for IfAction SubSystem: '<S20>/If Action Subsystem' incorporates:
    //   ActionPort: '<S21>/Action Port'

    ros2webots_lo_IfActionSubsystem
      (ros2webots_localization_model_U.rr_wheel_pose -
       ros2webots_localization_mode_DW.Delay_DSTATE_i,
       ros2webots_localization_model_U.rr_wheel_pose_update_dt, &rtb_Multiply);

    // End of Outputs for SubSystem: '<S20>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<S20>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S22>/Action Port'

    // SignalConversion generated from: '<S22>/In1' incorporates:
    //   Delay: '<S20>/Delay'
    //   Inport: '<Root>/rr_wheel_pose'
    //   Sum: '<S20>/Sum'

    rtb_Multiply = ros2webots_localization_model_U.rr_wheel_pose -
      ros2webots_localization_mode_DW.Delay_DSTATE_i;

    // End of Outputs for SubSystem: '<S20>/If Action Subsystem1'
  }

  // End of If: '<S20>/If'

  // Gain: '<S5>/Gain' incorporates:
  //   Gain: '<S8>/Gain'
  //   Sum: '<S5>/Sum'
  //   Sum: '<S8>/Sum'

  rtb_Gain_i = ((rtb_Gain_i + rtb_Multiply) * 0.5 + rtb_Gain) * 0.5;

  // Gain: '<S1>/Multiply' incorporates:
  //   Inport: '<Root>/fl_wheel_pose_update_dt'
  //   Inport: '<Root>/fr_wheel_pose_update_dt'
  //   Inport: '<Root>/rl_wheel_pose_update_dt'
  //   Inport: '<Root>/rr_wheel_pose_update_dt'
  //   Sum: '<S1>/Sum2'

  rtb_Multiply = (((ros2webots_localization_model_U.fl_wheel_pose_update_dt +
                    ros2webots_localization_model_U.fr_wheel_pose_update_dt) +
                   ros2webots_localization_model_U.rl_wheel_pose_update_dt) +
                  ros2webots_localization_model_U.rr_wheel_pose_update_dt) *
    0.25;

  // Sqrt: '<S30>/sqrt' incorporates:
  //   Inport: '<Root>/imu_orientation_vector'
  //   Product: '<S31>/Product'
  //   Product: '<S31>/Product1'
  //   Product: '<S31>/Product2'
  //   Product: '<S31>/Product3'
  //   SignalConversion generated from: '<S10>/Vector Concatenate'
  //   Sum: '<S31>/Sum'
  //
  rtb_Gain = std::sqrt(((ros2webots_localization_model_U.imu_orientation_vector
    [0] * ros2webots_localization_model_U.imu_orientation_vector[0] +
    ros2webots_localization_model_U.imu_orientation_vector[1] *
    ros2webots_localization_model_U.imu_orientation_vector[1]) +
                        ros2webots_localization_model_U.imu_orientation_vector[2]
                        * ros2webots_localization_model_U.imu_orientation_vector[
                        2]) +
                       ros2webots_localization_model_U.imu_orientation_vector[3]
                       * ros2webots_localization_model_U.imu_orientation_vector
                       [3]);

  // Product: '<S25>/Product' incorporates:
  //   Inport: '<Root>/imu_orientation_vector'
  //   SignalConversion generated from: '<S10>/Vector Concatenate'

  rtb_fcn5 = ros2webots_localization_model_U.imu_orientation_vector[0] /
    rtb_Gain;

  // Product: '<S25>/Product1' incorporates:
  //   Inport: '<Root>/imu_orientation_vector'
  //   SignalConversion generated from: '<S10>/Vector Concatenate'

  rtb_Product1_a = ros2webots_localization_model_U.imu_orientation_vector[1] /
    rtb_Gain;

  // Product: '<S25>/Product2' incorporates:
  //   Inport: '<Root>/imu_orientation_vector'
  //   SignalConversion generated from: '<S10>/Vector Concatenate'

  rtb_Product2 = ros2webots_localization_model_U.imu_orientation_vector[2] /
    rtb_Gain;

  // Product: '<S25>/Product3' incorporates:
  //   Inport: '<Root>/imu_orientation_vector'
  //   SignalConversion generated from: '<S10>/Vector Concatenate'

  rtb_Gain = ros2webots_localization_model_U.imu_orientation_vector[3] /
    rtb_Gain;

  // Trigonometry: '<S24>/Trigonometric Function3' incorporates:
  //   Fcn: '<S23>/fcn4'
  //   Fcn: '<S23>/fcn5'

  rtb_Gain = rt_atan2d_snf((rtb_Product2 * rtb_Gain + rtb_fcn5 * rtb_Product1_a)
    * 2.0, ((rtb_fcn5 * rtb_fcn5 - rtb_Product1_a * rtb_Product1_a) -
            rtb_Product2 * rtb_Product2) + rtb_Gain * rtb_Gain);

  // Sum: '<S9>/Sum' incorporates:
  //   Delay: '<S9>/Delay'
  //   Product: '<S9>/Product'
  //   Trigonometry: '<S9>/Cos'

  ros2webots_localization_mode_DW.Delay_DSTATE += std::cos(rtb_Gain) *
    rtb_Gain_i * rtb_Multiply;

  // SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
  //   Delay: '<S9>/Delay1'
  //   Outport: '<Root>/odometry_vector'

  ros2webots_localization_model_Y.odometry_vector[1] =
    ros2webots_localization_mode_DW.Delay1_DSTATE;

  // Sum: '<S9>/Sum1' incorporates:
  //   Delay: '<S9>/Delay1'
  //   Product: '<S9>/Product1'
  //   Trigonometry: '<S9>/Sin'

  ros2webots_localization_mode_DW.Delay1_DSTATE += rtb_Gain_i * rtb_Multiply *
    std::sin(rtb_Gain);

  // Update for Delay: '<S11>/Delay' incorporates:
  //   Inport: '<Root>/fl_wheel_pose'

  ros2webots_localization_mode_DW.Delay_DSTATE_g =
    ros2webots_localization_model_U.fl_wheel_pose;

  // Update for Delay: '<S17>/Delay' incorporates:
  //   Inport: '<Root>/rl_wheel_pose'

  ros2webots_localization_mode_DW.Delay_DSTATE_j =
    ros2webots_localization_model_U.rl_wheel_pose;

  // Update for Delay: '<S14>/Delay' incorporates:
  //   Inport: '<Root>/fr_wheel_pose'

  ros2webots_localization_mode_DW.Delay_DSTATE_o =
    ros2webots_localization_model_U.fr_wheel_pose;

  // Update for Delay: '<S20>/Delay' incorporates:
  //   Inport: '<Root>/rr_wheel_pose'

  ros2webots_localization_mode_DW.Delay_DSTATE_i =
    ros2webots_localization_model_U.rr_wheel_pose;
}

// Model initialize function
void ros2webots_localization_model_cg::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // InitializeConditions for Delay: '<S9>/Delay'
  ros2webots_localization_mode_DW.Delay_DSTATE =
    wheel_based_localization_x_initial_coord;

  // InitializeConditions for Delay: '<S9>/Delay1'
  ros2webots_localization_mode_DW.Delay1_DSTATE =
    wheel_based_localization_y_initial_coord;
}

// Model terminate function
void ros2webots_localization_model_cg::terminate()
{
  // (no terminate code required)
}

// Constructor
ros2webots_localization_model_cg::ros2webots_localization_model_cg() :
  ros2webots_localization_model_U(),
  ros2webots_localization_model_Y(),
  ros2webots_localization_mode_DW(),
  ros2webots_localization_mode_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
ros2webots_localization_model_cg::~ros2webots_localization_model_cg() = default;

// Real-Time Model get method
ros2webots_localization_model_cg::RT_MODEL_ros2webots_localizat_T
  * ros2webots_localization_model_cg::getRTM()
{
  return (&ros2webots_localization_mode_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
