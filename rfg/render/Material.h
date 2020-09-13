#pragma once
#include "RlCommon.h"
#include "RenderBlock.h"
#include "RFGR_Types/rfg/Vector.h"
#include "RFGR_Types/rfg/Containers.h"
#include "RFGR_Types/rfg/keen/render/RenderGeometry.h"

enum rl_shader_technique_type
{
    rl_shader_technique_none = 0xFFFFFFFF,
    rl_shader_technique_base = 0x0,
    rl_shader_technique_lighting = 0x1,
    rl_shader_technique_depth_only = 0x2,
    rl_shader_technique_user = 0x3,
};

struct rl_texture_desc
{
    union Data
    {
        struct DiscData
        {
            unsigned __int16 texture_stage_disk;
            unsigned __int16 texture_flags_disk;
        };
        struct DataStruct
        {
            unsigned __int32 texture_stage : 4;
            unsigned __int32 texture_flags : 4;
            unsigned __int32 sampler_state_idx : 24;
        };

        rl_texture_desc::Data::DiscData disc;
        rl_texture_desc::Data::DataStruct rt;
    };

    int texture_handle;
    unsigned int name_checksum;
    rl_texture_desc::Data data;
};

struct rl_material_const
{
    float elem[4];
};

struct rl_material_data
{
    unsigned int shader_handle;
    unsigned int name_checksum;
    unsigned int mat_flags;
    unsigned __int16 num_textures;
    char num_constants;
    char max_constants;
    et_ptr_offset<rl_texture_desc, 1> textures;
    et_ptr_offset<unsigned int, 0> constant_name_checksum;
    et_ptr_offset<rl_material_const, 0> constant_block;
};

struct rl_material_base : rl_base_object
{
    unsigned int hash_cache;
    unsigned int base_flags;
};

struct rl_material : rl_material_base
{
    int m_override_technique_index;
    rl_shader_technique_type m_override_technique_type;
    rl_material_data* m_data;
};