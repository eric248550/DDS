/* $Id$

(c) Copyright, Real-Time Innovations, 2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

============================================================================= */

#ifndef RTI_XCDR_INTERPRETER_HPP_
#define RTI_XCDR_INTERPRETER_HPP_

#include "xcdr/xcdr_interpreter.h"


namespace rti { namespace xcdr {

/*i
 * Provides the type code of a type.
 *
 * This struct is to be specialized in generated code for each TopicType.
 * Specializations must define a static member function:
 * RTIXCdrTypeCode * get()
 */
template <typename TopicType>
struct type_code;

namespace detail {

template <typename TopicType>
bool has_cpp_friendly_cdr_layout_impl()
{
    RTIXCdrUnsignedLongLong size;
    RTIXCdrAlignment alignment;
    return RTIXCdrTypeCode_hasCFriendlyCdrLayout(
            type_code<TopicType>::get(),
            &size,
            &alignment,
            1,
            RTI_XCDR_TRUE);
}

}

template <typename TopicType>
bool has_cpp_friendly_cdr_layout()
{
    static bool result = detail::has_cpp_friendly_cdr_layout_impl<TopicType>();
    return result;
}

struct NoOpPropertyConfigurator {
    static void configure(RTIXCdrInterpreterProgramsGenProperty&)
    {
        // In general (trad. and micro C++), no additional properties.
        //
        // dds_cpp.2.0 defines a custom Configurator
        //
    }
};

/*i
 * @brief Programs singleton for the to/from cdr functions
 *
 * The combination of the ProgramSingleton template parameters builds a single
 * instance for the given type, program kinds and options.
 * This will typically be instantiated in IDL-generated code.
 *
 * @tparam TopicType The topic-type these programs operate with
 * @tparam ProgramKind A mask of the different programs to be generated
 * @tparam ResolveAlias Value for RTIXCdrInterpreterProgramsGenProperty::resolveAlias
 *         when creating the programs
 * @tparam InlineStruct Value for RTIXCdrInterpreterProgramsGenProperty::inlineStruct
 *         when creating the programs
 * @tparam OptimizeEnum Value for RTIXCdrInterpreterProgramsGenProperty::optimizeEnum
 *         when creating the programs
 * @tparam KeysOnly (default false) Whether to generate programs only for key fields
 * @tparam PropertyConfigurator (default no-op) A functor that configures
 *         additional RTIXCdrInterpreterProgramsGenProperty to generate the
 *         programs.
 *
 * get_instance() creates the singleton the first time it's called. The singleton
 * is automatically deleted by the destructor of a static local variable.
 */
template <
    typename TopicType,
    int ProgramKind,
    bool ResolveAlias,
    bool InlineStruct,
    bool OptimizeEnum,
    bool KeysOnly = false,
    typename PropertyConfigurator = NoOpPropertyConfigurator>
struct ProgramsSingleton {
private:
    ProgramsSingleton()
    {
        RTIXCdrInterpreterProgramsGenProperty property =
                RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

        property.generateWithAllFields =
                KeysOnly ? RTI_XCDR_FALSE : RTI_XCDR_TRUE;
        property.resolveAlias = ResolveAlias ? RTI_XCDR_TRUE : RTI_XCDR_FALSE;
        property.inlineStruct = InlineStruct ? RTI_XCDR_TRUE : RTI_XCDR_FALSE;
        property.optimizeEnum = OptimizeEnum ? RTI_XCDR_TRUE : RTI_XCDR_FALSE;
        PropertyConfigurator::configure(property);

        programs_ = RTIXCdrInterpreterPrograms_new(
                type_code<TopicType>::get(),
                &property,
                ProgramKind);
    }

    ~ProgramsSingleton()
    {
        if (programs_ != NULL) {
            RTIXCdrInterpreterPrograms_delete(programs_);
        }
    }

    RTIXCdrInterpreterPrograms *programs_;

public:
    // Returns the singleton instance. It can be NULL if the program creation
    // failed.
    static RTIXCdrInterpreterPrograms * get_instance()
    {
        static ProgramsSingleton<
                TopicType,
                ProgramKind,
                ResolveAlias,
                InlineStruct,
                OptimizeEnum,
                KeysOnly,
                PropertyConfigurator> instance;
        return instance.programs_;
    }

};

// Returns a ProgramsSingleton with the programs that the generated
// to/from cdr functions need
template <
    typename TopicType,
    bool ResolveAlias,
    bool InlineStruct,
    bool OptimizeEnum,
    typename PropertyConfigurator>
RTIXCdrInterpreterPrograms * get_cdr_serialization_programs_w_property_configurator()
{
    return ProgramsSingleton<
            TopicType,
            RTI_XCDR_SER_PROGRAM
                | RTI_XCDR_DESER_PROGRAM
                | RTI_XCDR_GET_SER_SIZE_PROGRAM
                | RTI_XCDR_GET_MAX_SER_SIZE_PROGRAM,
            ResolveAlias,
            InlineStruct,
            OptimizeEnum,
            false,
            PropertyConfigurator>::get_instance();
}

template <
    typename TopicType,
    bool ResolveAlias,
    bool InlineStruct,
    bool OptimizeEnum>
RTIXCdrInterpreterPrograms * get_cdr_serialization_programs()
{
    return ProgramsSingleton<
            TopicType,
            RTI_XCDR_SER_PROGRAM
                | RTI_XCDR_DESER_PROGRAM
                | RTI_XCDR_GET_SER_SIZE_PROGRAM
                | RTI_XCDR_GET_MAX_SER_SIZE_PROGRAM,
            ResolveAlias,
            InlineStruct,
            OptimizeEnum,
            false,
            NoOpPropertyConfigurator>::get_instance();
}

/*i
 * Provides the interpreter programs for a type. (Currently it only provides
 * the initialize_sample program used to initialize FlatData samples)
 *
 * This struct is to be specialized in generated code for each TopicType.
 * Specializations must define a static member function:
 * RTIXCdrInterpreterPrograms * get(), which will call
 * get_cdr_initialization_programs() with the options (ResolveAlias, etc.) used
 * to generate code for this type.
 */
template <typename SampleType>
struct type_programs;

} } // namespace rti::xcdr

#endif // RTI_XCDR_INTERPRETER_HPP_
