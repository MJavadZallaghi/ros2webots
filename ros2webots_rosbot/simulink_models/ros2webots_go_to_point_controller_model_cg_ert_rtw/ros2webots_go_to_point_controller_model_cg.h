//
// File: ros2webots_go_to_point_controller_model_cg.h
//
// Code generated for Simulink model 'ros2webots_go_to_point_controller_model_cg'.
//
// Model version                  : 1.347
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Sat Mar  2 16:57:53 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_ros2webots_go_to_point_controller_model_cg_h_
#define RTW_HEADER_ros2webots_go_to_point_controller_model_cg_h_
#include "rtwtypes.h"
#include "ros2webots_go_to_point_controller_model_cg_types.h"

extern "C"
{

#include "rtGetNaN.h"

}

extern "C"
{

#include "rt_nonfinite.h"

}

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define ros2webots_go_to_point_controller_model_cg_M (ros2webots_go_to_point_contr_M)

// Exported data declaration

// Const memory section
// Declaration for custom storage class: Const
extern const real_T laterl_PID_kd;    // Referenced by: '<S31>/Derivative Gain'

// Lateral PID controller gain: Kd
extern const real_T laterl_PID_ki;     // Referenced by: '<S34>/Integral Gain'

// Lateral PID controller gain: Ki
extern const real_T laterl_PID_kp;  // Referenced by: '<S42>/Proportional Gain'

// Lateral PID controller gain: Kp
extern const real_T longitudinal_speed_gain;// Referenced by: '<S1>/Gain'

// The gain thay manipulate main state machine velocity command

// Class declaration for model ros2webots_go_to_point_controller_model_cg
class ros2webots_go_to_point_controller_model_cg final
{
  // public data and function members
 public:
  // Block states (default storage) for system '<Root>'
  struct DW_ros2webots_go_to_point_con_T {
    real_T Integrator_DSTATE;          // '<S37>/Integrator'
    real_T Filter_DSTATE;              // '<S32>/Filter'
    uint8_T is_active_c8_ros2webots_go_to_p;// '<S1>/Chart'
    uint8_T is_c8_ros2webots_go_to_point_co;// '<S1>/Chart'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_ros2webots_go_to_point_c_T {
    real_T x_des;                      // '<Root>/x_des'
    real_T y_des;                      // '<Root>/y_des'
    real_T yaw_des;                    // '<Root>/yaw_des'
    real_T x_act;                      // '<Root>/x_act'
    real_T y_act;                      // '<Root>/y_act'
    real_T yaw_act;                    // '<Root>/yaw_act'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_ros2webots_go_to_point_c_T {
    uint8_T controller_state;          // '<Root>/controller_state'
    real_T command_velocity;           // '<Root>/command_velocity'
    real_T command_steering_angle;     // '<Root>/command_steering_angle'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_ros2webots_go_to_poi_T {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  ros2webots_go_to_point_controller_model_cg
    (ros2webots_go_to_point_controller_model_cg const&) = delete;

  // Assignment Operator
  ros2webots_go_to_point_controller_model_cg& operator=
    (ros2webots_go_to_point_controller_model_cg const&) & = delete;

  // Move Constructor
  ros2webots_go_to_point_controller_model_cg
    (ros2webots_go_to_point_controller_model_cg &&) = delete;

  // Move Assignment Operator
  ros2webots_go_to_point_controller_model_cg& operator=
    (ros2webots_go_to_point_controller_model_cg &&) = delete;

  // Real-Time Model get method
  ros2webots_go_to_point_controller_model_cg::RT_MODEL_ros2webots_go_to_poi_T
    * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_ros2webots_go_to_point_c_T
    *pExtU_ros2webots_go_to_point_c_T)
  {
    ros2webots_go_to_point_contro_U = *pExtU_ros2webots_go_to_point_c_T;
  }

  // Root outports get method
  const ExtY_ros2webots_go_to_point_c_T &getExternalOutputs() const
  {
    return ros2webots_go_to_point_contro_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  ros2webots_go_to_point_controller_model_cg();

  // Destructor
  ~ros2webots_go_to_point_controller_model_cg();

  // private data and function members
 private:
  // External inputs
  ExtU_ros2webots_go_to_point_c_T ros2webots_go_to_point_contro_U;

  // External outputs
  ExtY_ros2webots_go_to_point_c_T ros2webots_go_to_point_contro_Y;

  // Block states
  DW_ros2webots_go_to_point_con_T ros2webots_go_to_point_contr_DW;

  // Real-Time Model
  RT_MODEL_ros2webots_go_to_poi_T ros2webots_go_to_point_contr_M;
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'ros2webots_go_to_point_controller_model_cg'
//  '<S1>'   : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller'
//  '<S2>'   : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Chart'
//  '<S3>'   : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller'
//  '<S4>'   : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Error calculator'
//  '<S5>'   : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Rotation matrix: 2D, Z'
//  '<S6>'   : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Anti-windup'
//  '<S7>'   : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/D Gain'
//  '<S8>'   : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Filter'
//  '<S9>'   : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Filter ICs'
//  '<S10>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/I Gain'
//  '<S11>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Ideal P Gain'
//  '<S12>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Ideal P Gain Fdbk'
//  '<S13>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Integrator'
//  '<S14>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Integrator ICs'
//  '<S15>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/N Copy'
//  '<S16>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/N Gain'
//  '<S17>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/P Copy'
//  '<S18>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Parallel P Gain'
//  '<S19>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Reset Signal'
//  '<S20>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Saturation'
//  '<S21>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Saturation Fdbk'
//  '<S22>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Sum'
//  '<S23>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Sum Fdbk'
//  '<S24>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Tracking Mode'
//  '<S25>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Tracking Mode Sum'
//  '<S26>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Tsamp - Integral'
//  '<S27>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Tsamp - Ngain'
//  '<S28>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/postSat Signal'
//  '<S29>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/preSat Signal'
//  '<S30>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Anti-windup/Passthrough'
//  '<S31>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/D Gain/Internal Parameters'
//  '<S32>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S33>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Filter ICs/Internal IC - Filter'
//  '<S34>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/I Gain/Internal Parameters'
//  '<S35>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Ideal P Gain/Passthrough'
//  '<S36>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S37>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Integrator/Discrete'
//  '<S38>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Integrator ICs/Internal IC'
//  '<S39>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/N Copy/Disabled'
//  '<S40>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/N Gain/Internal Parameters'
//  '<S41>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/P Copy/Disabled'
//  '<S42>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Parallel P Gain/Internal Parameters'
//  '<S43>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Reset Signal/Disabled'
//  '<S44>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Saturation/Passthrough'
//  '<S45>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Saturation Fdbk/Disabled'
//  '<S46>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Sum/Sum_PID'
//  '<S47>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Sum Fdbk/Disabled'
//  '<S48>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Tracking Mode/Disabled'
//  '<S49>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Tracking Mode Sum/Passthrough'
//  '<S50>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S51>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/Tsamp - Ngain/Passthrough'
//  '<S52>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/postSat Signal/Forward_Path'
//  '<S53>'  : 'ros2webots_go_to_point_controller_model_cg/go-to-point controller/Discrete PID Controller/preSat Signal/Forward_Path'

#endif              // RTW_HEADER_ros2webots_go_to_point_controller_model_cg_h_

//
// File trailer for generated code.
//
// [EOF]
//
