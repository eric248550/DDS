/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_TRANSF_DETAIL_TRANSFORMATION_FORWARDER_HPP_
#define RTI_ROUTING_TRANSF_DETAIL_TRANSFORMATION_FORWARDER_HPP_

#include <rti/core/Exception.hpp>

#include <dds/core/xtypes/DynamicData.hpp>
#include <dds/sub/SampleInfo.hpp>
#include <rti/routing/transf/Transformation.hpp>
#include <rti/routing/TypeInfo.hpp>
#include <rti/routing/detail/UpdatableEntityForwarder.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>


namespace rti { namespace routing { namespace transf { namespace detail {


class TransformationForwarder{
public:
    static RTI_RoutingServiceTransformation create_native(
            TransformationPlugin *plugin,
            const struct RTI_RoutingServiceTypeInfo *native_input_type_info,
            const struct RTI_RoutingServiceTypeInfo *native_output_type_info,
            const struct RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment *environment)
    {
        try {
            TypeInfo input_type_info(*native_input_type_info);
            TypeInfo output_type_info(*native_output_type_info);

            std::map<std::string, std::string> properties;
            rti::routing::PropertyAdapter::add_properties_from_native(
                    properties,
                    native_properties);

            TransformationForwarder *forwarder = new TransformationForwarder();
            ScopedForwarder<TransformationPlugin, TransformationForwarder> scoped(
                    plugin,
                    forwarder,
                    environment);
            forwarder->transformation_ = plugin->create_transformation(
                    input_type_info,
                    output_type_info,
                    properties);
            RTI_ROUTING_THROW_ON_NULL(forwarder->transformation_);

            scoped.release();
            return forwarder->native();
        } catch(const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment, 
                    "%s",
                    ex.what());
            return NULL;
        } catch (...) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "unexpected exception");
            return NULL;
        }    
        
    }
    
    static void delete_native(
            TransformationPlugin *plugin,
            RTI_RoutingServiceTransformation native_transformation,
            RTI_RoutingServiceEnvironment *environment)
    {       
        TransformationForwarder *forwarder = 
                static_cast<TransformationForwarder*>(native_transformation);        
        try {
            if (forwarder->transformation_ != NULL) {
                plugin->delete_transformation(
                        forwarder->transformation_);
                forwarder->transformation_ = NULL;
            }
        } catch(const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment, 
                    "%s",
                    ex.what());            
        } catch (...) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "unexpected exception");
        } 
               
        delete forwarder;
    }   
    
    static void transform(
            RTI_RoutingServiceTransformation native_transformation,
            RTI_RoutingServiceSample **out_sample_lst,
            RTI_RoutingServiceSampleInfo **out_info_lst,
            int *out_count,
            RTI_RoutingServiceSample *in_sample_lst,
            RTI_RoutingServiceSampleInfo *in_info_lst,
            int in_count,
            RTI_RoutingServiceEnvironment *environment)
    {        
        TransformationForwarder *forwarder =
                static_cast<TransformationForwarder*> (native_transformation);                
        if (forwarder->transformation_ == NULL) {
            return;
        }

        *out_count = 0;
        try {
            // get native samples
            forwarder->in_sample_seq_.resize(in_count);
            forwarder->in_info_seq_.resize(in_count);
            for (int i = 0; i < in_count; i++) {
                forwarder->in_sample_seq_[i] = in_sample_lst[i];
                if (in_info_lst != NULL) {
                    forwarder->in_info_seq_[i] = in_info_lst[i];
                }
            }
           
            forwarder->transformation_->transform(
                    forwarder->out_sample_seq_,
                    forwarder->out_info_seq_,
                    forwarder->in_sample_seq_,
                    forwarder->in_info_seq_);
            if (!forwarder->out_info_seq_.empty()
                    && (forwarder->out_info_seq_.size() 
                            != forwarder->out_sample_seq_.size())) {
                throw dds::core::PreconditionNotMetError(
                        "sample and info sequences length mismatch");
            }
        } catch (const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    ex.what());
            return;
        } catch (...) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "unexpected exception");
            return;
        }

        // direct mapping         
        *out_count = forwarder->out_sample_seq_.size();
        if (*out_count > 0) {
            *out_sample_lst = &forwarder->out_sample_seq_[0];
            *out_info_lst = &forwarder->out_info_seq_[0];
        }
    }
    
    static void return_loan(
        RTI_RoutingServiceTransformation native_transformation,
        RTI_RoutingServiceSample *,
        RTI_RoutingServiceSampleInfo *,
        int,
        RTI_RoutingServiceEnvironment *environment)
    {
        TransformationForwarder *forwarder =
                static_cast<TransformationForwarder*>(native_transformation);                
        if (forwarder->transformation_ == NULL) {
            return;
        }
        
        try {
            forwarder->transformation_->return_loan(
                    forwarder->out_sample_seq_,
                    forwarder->out_info_seq_);
        } catch (const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    ex.what());
        } catch (...) {
        }

        forwarder->out_sample_seq_.clear();
        forwarder->out_info_seq_.clear();
        
    }
    
    static void update(
            RTI_RoutingServiceTransformation native_stream_reader,
            const struct RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment *environment)
    {

        TransformationForwarder *stream_reader_forwarder =
                static_cast<TransformationForwarder*> (native_stream_reader);

        rti::routing::detail::UpdatableEntityForwarder::update(
                stream_reader_forwarder->transformation_,
                native_properties,
                environment);        
    }

    RTI_RoutingServiceTransformation native()
    {
        return this;
    }
     

private:   
          
    TransformationForwarder()      
        : transformation_(NULL)
    {
               
    }

    ~TransformationForwarder()
    {
    }
        

private:
            
    Transformation *transformation_;
    std::vector<Transformation::SamplePtr> out_sample_seq_;
    std::vector<Transformation::InfoPtr> out_info_seq_;
    std::vector<Transformation::SamplePtr> in_sample_seq_;
    std::vector<Transformation::InfoPtr> in_info_seq_;
};

}}}}

#endif // RTI_ROUTING_TRANSF_DETAIL_TRANSFORMATION_FORWARDER_HPP_
