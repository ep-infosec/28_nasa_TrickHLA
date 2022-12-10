/*!
@file DIS/ExecutionConfiguration.hh
@ingroup DIS
@brief Definition of the TrickHLA DIS Execution Configuration Object (ExCO).

@copyright Copyright 2020 United States Government as represented by the
Administrator of the National Aeronautics and Space Administration.
No copyright is claimed in the United States under Title 17, U.S. Code.
All Other Rights Reserved.

\par<b>Responsible Organization</b>
Simulation and Graphics Branch, Mail Code ER7\n
Software, Robotics & Simulation Division\n
NASA, Johnson Space Center\n
2101 NASA Parkway, Houston, TX  77058

@trick_parse{everything}

@python_module{DIS}

@tldh
@trick_link_dependency{../../source/TrickHLA/Packing.cpp}
@trick_link_dependency{../../source/TrickHLA/ExecutionConfigurationBase.cpp}
@trick_link_dependency{../../source/DIS/ExecutionConfiguration.cpp}
@trick_link_dependency{../../source/DIS/Types.cpp}

@revs_title
@revs_begin
@rev_entry{Dan Dexter, NASA ER7, TrickHLA, June 2016, --, SISO DIS Initialization.}
@rev_entry{Edwin Z. Crues, NASA ER7, TrickHLA, January 2019, --, DIS support and testing.}
@rev_entry{Edwin Z. Crues, NASA ER7, TrickHLA, June 2019, --, Version 3 rewrite.}
@revs_end

*/

#ifndef _DIS_EXECUTION_CONFIGURATION_HH_
#define _DIS_EXECUTION_CONFIGURATION_HH_

// System include files.

// TrickHLA include files.
#include "TrickHLA/ExecutionConfigurationBase.hh"
#include "TrickHLA/Packing.hh"

// DIS include files.
#include "DIS/Types.hh"

namespace DIS
{

class ExecutionConfiguration : public TrickHLA::ExecutionConfigurationBase
{

   // Let the Trick input processor access protected and private data.
   // InputProcessor is really just a marker class (does not really
   // exists - at least yet). This friend statement just tells Trick
   // to go ahead and process the protected and private data as well
   // as the usual public data.
   friend class InputProcessor;
   // IMPORTANT Note: you must have the following line too.
   // Syntax: friend void init_attr<namespace>__<class name>();
   friend void init_attrDIS__ExecutionConfiguration();

  public:
   // The members below are part of the FOM data ExCO exchange.
   char *root_frame_name; /**<  @trick_units{--}
      Specifies the name of the root coordinate frame in the federation
      execution's reference frame tree. This frame shall remain fixed
      throughout the federation execution. */

   double scenario_time_epoch; /**<  @trick_units{s}
      Federation execution scenario time epoch. This is the beginning epoch
      expressed in Terrestrial Time (TT) that corresponds to HLA logical time 0.
      All joining federates shall use this time to coordinate the offset between
      their local simulation scenario times, their local simulation execution
      times and the HLA logical time. */

   double next_mode_scenario_time; /**<  @trick_units{s}
      The time for the next federation execution mode change expressed as a
      federation scenario time reference. Note: this is value is only
      meaningful for going into freeze; exiting freeze is coordinated through
      a sync point mechanism. */

   double next_mode_cte_time; /**<  @trick_units{s}
      The time for the next federation execution mode change expressed as a
      Central Timing Equipment (CTE) time reference. The standard for this
      reference shall be defined in the federation agreement when CTE is used. */

   short current_execution_mode; /**< @trick_units{--}
      Defines the current running state of the federation execution in terms
      of a finite set of states expressed in the RunMode enumeration.*/

   short next_execution_mode; /**< @trick_units{--}
      Defines the next running state of the federation execution in terms of
      a finite set of states expressed in the RunMode enumeration. This is
      used in conjunction with the cte_mode_time, sim_mode_time and
      associated sync point mechanisms to coordinate federation execution
      mode transitions.*/

   int64_t least_common_time_step; /**< @trick_units{--}
      A 64 bit integer time that represents microseconds for the least common
      value of all the time step values in the federation execution (LCTS).
      This value is set by the Master Federate and does not change during the
      federation execution. This is used in the computation to find the next
      HLA Logical Time Boundary (HLTB) available to all federates in the
      federation execution. The basic equation is
            HLTB = ( floor(GALT/LCTS) + 1 ) * LCTS,
      where GALT is the greatest available logical time. This is used to
      synchronize the federates in a federation execution to be on a common
      logical time boundary. */

  public:
   // Public constructors and destructors.
   /*! @brief Default constructor for the DIS ExecutionConfiguration class. */
   ExecutionConfiguration();
   /*! @brief Pure virtual destructor for the DIS ExecutionConfiguration class. */
   virtual ~ExecutionConfiguration();

   // Default data.
   /*! @brief Sets up the attributes for the ExCO using default values.
    *  These can be overridden in the input file.
    *  @param exco_name S_define level Trick name for ExCO. */
   virtual void configure_attributes( char const *exco_name );

   // From the TrickHLA::Packing class.
   virtual void pack();
   virtual void unpack();

   // FOM data public accessor interface.
   /*! @brief Set the root reference frame name.
    *  @param name Root reference frame name. */
   virtual void set_root_frame_name( char const *name );
   /*! @brief Get the root reference frame name.
    *  @return Root Reference Frame name as a constant string. */
   virtual char const *get_root_frame_name()
   {
      return root_frame_name;
   }

   /*! @brief Set the scenario time line epoch.
    *  @param scenario_time Scenario time line epoch. */
   virtual void set_scenario_time_epoch( double scenario_time );
   /*! @brief Get the scenario time line epoch.
    *  @return The scenario time line epoch. */
   virtual double get_scenario_time_epoch()
   {
      return scenario_time_epoch;
   }

   /*! @brief Set the scenario time for the next mode transition.
    *  @param next_mode_time Scenario time for next mode transition. */
   virtual void set_next_mode_scenario_time( double next_mode_time );
   /*! @brief Get the next mode scenario time.
    *  @return The next mode scenario time. */
   virtual double get_next_mode_scenario_time()
   {
      return next_mode_scenario_time;
   }

   /*! @brief Set the next mode CTE time.
    *  @param cte_time CTE time for next mode transition. */
   virtual void set_next_mode_cte_time( double cte_time );
   /*! @brief Get the next mode CTE time.
    *  @return The next mode CTE time. */
   virtual double get_next_mode_cte_time()
   {
      return next_mode_cte_time;
   }

   /*! @brief Sets the current ExCO run mode.
    *  @param mode Current Execution configuration run mode integer value. */
   virtual void set_current_execution_mode( short mode );
   /*! @brief Sets the current ExCO run mode.
    * @param mode Current Execution configuration run mode enumeration value. */
   virtual void set_current_execution_mode( DIS::ExecutionModeEnum mode );
   /*! @brief Get the current execution mode.
    *  @return The current execution mode as an integer. */
   virtual short get_current_execution_mode()
   {
      return current_execution_mode;
   }

   /*! @brief Sets the next ExCO execution mode.
    *  @param mode Next Execution configuration execution mode from an integer. */
   virtual void set_next_execution_mode( short mode );
   /*! @brief Sets the next ExCO execution mode.
    *  @param mode Next Execution configuration execution mode from an enumeration value. */
   virtual void set_next_execution_mode( DIS::ExecutionModeEnum mode );
   /*! @brief Get the next execution mode.
    *  @return The next execution mode as an integer. */
   virtual short get_next_execution_mode()
   {
      return this->next_execution_mode;
   }

   // ExecutionConfiguration specific functions.
   /*! @brief Setup the Trick Ref Attributes for the ExCO object.
    *  @param packing_obj Associated packing object. */
   virtual void setup_ref_attributes( Packing *packing_obj );
   /*! @brief Print the current ExCO state to the console. */
   virtual void print_execution_configuration();

   /*! @brief Wait on an ExCO update.
    *  @return True for successful wait. */
   virtual bool wait_for_update();

  private:
   // Do not allow the copy constructor or assignment operator.
   ExecutionConfiguration( ExecutionConfiguration const &rhs );
   ExecutionConfiguration &operator=( ExecutionConfiguration const &rhs );
};

} // namespace DIS

#endif // _DIS_EXECUTION_CONFIGURATION_HH_: Do NOT put anything after this line!
