/* $Id$

 (c) Copyright, Real-Time Innovations, 2013-2016. 
 All rights reserved.
 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

===================================================================== */

#ifndef RTI_TEST_ABSTRACTDOMAINTESTER_HPP_
#define RTI_TEST_ABSTRACTDOMAINTESTER_HPP_

#include <stdio.h>
#include <stdlib.h>

#include "log/log_makeheader.h"
#include <dds_c/dds_c_test.h>
#include "test/test_setting.h"
#include <rti/test/Tester.hpp>
#include <rti/core/BuiltinProfiles.hpp>

#include <dds/domain/DomainParticipant.hpp>
#include <dds/core/QosProvider.hpp>

namespace rti { namespace test {

/*
 * Provides a common way of creating a test domain participant with the right
 * ID and QoS.
 *
 * It also automatically finalizes the domain participant factory on
 * destruction.
 *
 * Testers that create domain participants should inherit from this class
 */
class AbstractDomainTester : public Tester {
public:
    static const dds::domain::qos::DomainParticipantQos& test_qos(
            bool use_low_memory_profile = true)
    {
        using namespace dds::core;
        using namespace rti::core::builtin_profiles;
        using namespace rti::core::policy;

        static dds::domain::qos::DomainParticipantQos qos;
      #if defined(RTI_ANDROID) || defined(RTI_IOS)
        bool acceptUnknownPeers = true;
      #else
        bool acceptUnknownPeers = false;
      #endif
        bool low_memory_profile =
                (RTITestSetting_isLowMemoryParticipantQosSetting() == RTI_TRUE)
                && use_low_memory_profile;

        if (low_memory_profile) {
            dds::domain::qos::DomainParticipantQos lm_qos =
                    QosProvider::Default().participant_qos(
                            qos_lib_exp::generic_minimal_memory_footprint());
            DomainParticipantResourceLimits lm_resource_limits = lm_qos
                    .policy<DomainParticipantResourceLimits>();
            lm_resource_limits.participant_property_list_max_length(32);
            lm_resource_limits.participant_property_string_max_length(1024);
            lm_resource_limits.writer_property_list_max_length(32);
            lm_resource_limits.writer_property_string_max_length(1024);
            lm_resource_limits.reader_property_list_max_length(32);
            lm_resource_limits.reader_property_string_max_length(1024);
            lm_resource_limits.max_endpoint_groups(5);
            lm_resource_limits.max_endpoint_group_cumulative_characters(500);
            lm_resource_limits.channel_seq_max_length(5);
            lm_resource_limits.channel_filter_expression_max_length(500);
            lm_resource_limits.contentfilter_property_max_length(250);
            lm_resource_limits.transport_info_list_max_length(5);
            lm_resource_limits.topic_data_max_length(32);
            lm_resource_limits.max_partitions(3);
            lm_resource_limits.max_partition_cumulative_characters(150);
            lm_qos << lm_resource_limits;
            acceptUnknownPeers = true;
            qos = lm_qos;
        } else {
            // qos object is static, hence we need to reset it to default value
            // if low_memory_profile is false for some tests checking default
            // behavior
            qos = dds::domain::DomainParticipant::default_participant_qos();
        }

        qos << rti::core::policy::Database().shutdown_cleanup_period(
            dds::core::Duration::from_millisecs(10));

        StringSeq initial_peers_list;
        initial_peers_list.push_back("1@localhost");
      #ifdef RTI_SHARED_MEMORY
        if (!low_memory_profile) {
            initial_peers_list.push_back("shmem://");
        }
      #endif

        qos << rti::core::policy::Discovery()
            .initial_peers(initial_peers_list)
            .multicast_receive_addresses(StringSeq())
            .accept_unknown_peers(acceptUnknownPeers);

        return qos;
    }

protected:
    AbstractDomainTester(
        const std::string& name,
        RTITestLevel test_level = RTI_TEST_LEVEL_UNIT,
        bool tests_require_file_system = false)
    : Tester(name, test_level, tests_require_file_system)
    {
    }

    virtual ~AbstractDomainTester() {}

    dds::domain::DomainParticipant create_participant()
    {
        return dds::domain::DomainParticipant(domain_id(), test_qos());
    }
};

} } // namespace rti::test

#endif

// --------------------------------------------------------------------

/* End $Id$ */
